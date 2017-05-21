/** ...file comment
*
*
*/

#include "WebSocketRequestHandler.h"

#include "Poco/Net/WebSocket.h"
#include "Poco/Net/NetException.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Timespan.h"

#include "Poco/JSON/Parser.h"
#include "Poco/JSON/Object.h"
#include "Poco/JSON/JSONException.h"

#include "Poco/TextConverter.h"
#include "Poco/TextEncoding.h"
#include "Poco/UTF8Encoding.h"

#include "Poco/JSON/Template.h"
#include <cassert>

using Poco::Net::WebSocket;
using Poco::JSON::Parser;
using Poco::JSON::Object;
using Poco::Dynamic::Var;
using Poco::TextEncoding;
using Poco::TextConverter;
using Poco::Timespan;

/** IMPORTANT NOTE: For now it's only implementation stub. Not tested. 
 *	!mayfail 
*/
void WebSocketRequestHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
	try
	{
		WebSocket ws(request, response);
		poco_information(logger_, "WebSocket connection established.");

		Timespan timeout = ws.getReceiveTimeout();
		poco_information(logger_, Poco::format("WebSocket revc timeout: %ds.", timeout.totalSeconds()));

		Parser jsonParser;
		Var message = nullptr;
		Object::Ptr msgObj = nullptr;
		Object::Ptr innerObj = nullptr;

		TextEncoding& textEncoding = TextEncoding::global();
		poco_information(logger_, Poco::format("Global text encoding is %s.\n", std::string(textEncoding.canonicalName())));


		// MAYBE Poco::Buffer
		char buffer[1024]; // MAYBE init with zero values?
		int flags = 0;
		int n = 0;
		
		while (true)
		{
			n = ws.receiveFrame(buffer, sizeof(buffer)-1, flags);
			poco_information(logger_, Poco::format("Frame received (length=%d, flags=0x%x).", n, unsigned(flags)));

			// Client-to-Server communication frames are masked
			// https://tools.ietf.org/html/rfc6455#section-5.3
			if ((flags & WebSocket::FRAME_OP_BITMASK) == WebSocket::FRAME_OP_PING)
			{
				// Ping frame MAY include "Application data"

				// https://tools.ietf.org/html/rfc6455#section-5.5.2
				poco_information(logger_, "Got PING frame. Sending back PONG frame.");
				// with same payload ("Application data")!
				flags &= 0xF0; // reset the PING frame opcode
				flags |= WebSocket::FRAME_OP_PONG;
				ws.sendFrame(buffer, n, flags);
				poco_information(logger_, Poco::format("Sent PONG. Length=%d, flags=0x%x.\n", n, unsigned(flags)));

				flags = 0;
				continue;
			}
			else if ((flags & WebSocket::FRAME_OP_BITMASK) == WebSocket::FRAME_OP_PONG)
			{
				// TODO match to a previously sent Ping frame (by the Server), if any
				//		Upon receipt of a Ping frame, an endpoint MUST send a Pong frame in
  				//		response, unless it already received a Close frame.

				// TODO check payload equality to the corresponding Ping frame ?

				// no response needed
				buffer[n] = '\0';
				poco_information(logger_, Poco::format("Got Pong frame. Payload=\"%s\".\n", std::string(buffer)));
				continue;
			}
			else if ((flags & WebSocket::FRAME_OP_BITMASK) == WebSocket::FRAME_OP_CLOSE)
			{
				// https://tools.ietf.org/html/rfc6455#section-5.5.1
				// Only if the Server did not previously send a Close frame!
				ws.sendFrame(buffer, n, flags);

				buffer[n] = '\0';

				// The Close frame MAY contain a body
				// RFC "MAY" key word: https://tools.ietf.org/html/rfc2119#section-5
				if (n >= 2) 
				{
					// status code is in network byte order --> needed conversion? CHECK

					//Poco::UInt16 statusCode = reinterpret_cast<unsigned short>(buffer);
					Poco::UInt16 statusCode = buffer[0] << 8 | buffer[1];	// BROKEN, TODO repair
					std::cerr << "statusCode=" << statusCode << '.' << std::endl;
					std::string reason(static_cast<char*>(buffer+2));
					poco_information(logger_, Poco::format("Got and send back CLOSE frame. Code=%hu, reason=\"%s\", "
														"length=%d, flags=0x%x.\n", statusCode, reason, n, unsigned(flags)));
				}
				else
					poco_information(logger_, Poco::format("Got and send back CLOSE frame."
														"Length=%d, flags=0x%x.\n", n, unsigned(flags)));		

				break;
			}
			else if (n == 0)
			{
				poco_information(logger_, "Got 0 bytes of payload, and not Ping / Pong / Close frame.\n");
				// send Close frame?
				break;
			}


			buffer[n] = '\0';
			//poco_information(logger_, Poco::format("Got: ###%s###", std::string(buffer)));

			message = jsonParser.parse(std::string(buffer));
			//poco_information(logger_, "After parsing.");

			msgObj = message.extract<Object::Ptr>(); // throws BadCastException and InvalidAccessException
			innerObj = msgObj->getObject("player");
			std::/*w*/string name = innerObj->getValue<std::/*w*/string>("name");
			innerObj = msgObj->getObject("msg");
			std::/*w*/string msgText = innerObj->getValue<std::/*w*/string>("text");

			std::/*w*/string response = /*L*/"{\"name\":\"" + name + /*L*/"\",\"text\":\"" + msgText + /*L*/"\"}";
			//std::string response = "{\"name\":\"nick\",\"text\":\"Hello world\"}";

			message.empty();
			jsonParser.reset();

			//poco_information(logger_, Poco::format("Will send: ###%s###", response)); // %ls
			//std::/*w*/cout << "Cout sent: ###" << response.data() << "###\n";

			assert(response.length() == strlen(response.data()));

			n = ws.sendFrame(static_cast<const void*>(response.data()), response.length(), flags); // without the ending '\0'
			poco_information(logger_, Poco::format("Sent %d bytes of payload, flags=0x%x.", n, unsigned(flags)));

			// send PING frame (for test)
			//  All control frames MUST have a payload length of 125 bytes or less and MUST NOT be fragmented (FIN flag set).
			flags = 0x80; // FIN frame flag
			flags |= WebSocket::FRAME_OP_PING;
			response = "yadayada";
			n = ws.sendFrame((const char*)"yadayada", 8, flags);
			poco_information(logger_, Poco::format("TEST: send Ping frame. Length=%d, flags=0x%x, payload=\"%s\".\n",
													n, unsigned(flags), response));
		}

		// if near connection timeout -> send a PING frame ?
		// or the client must send the PING frame then, otherwise, the connection will be terminated by the server
		//		maybe send a protocol frame just after the handshake completion, with important connection info (e.g. server socket timeout)
		// or send unsolicited PONG's from the Server to keep the connection alive (unidirectional heartbeat)?
		//		https://tools.ietf.org/html/rfc6455#section-5.5.3 

		poco_information(logger_, "WebSocket connection closed.");
	}
	// TODO handle WS(Net) Timeout exception
	catch (Poco::Net::WebSocketException &ex)
	{
		logger_.log(ex);
		switch (ex.code())
		{
			case WebSocket::WS_ERR_HANDSHAKE_UNSUPPORTED_VERSION:
				response.set("Sec-WebSocket-Version", WebSocket::WEBSOCKET_VERSION);
				// fallthrough
			case WebSocket::WS_ERR_NO_HANDSHAKE:
			case WebSocket::WS_ERR_HANDSHAKE_NO_VERSION:
			case WebSocket::WS_ERR_HANDSHAKE_NO_KEY:
				response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
				response.setContentLength(0);
				response.send();
				break;
		}
	}
	catch (Poco::BadCastException &ex)
	{
		logger_.log(ex);
		poco_error(logger_, "Clinet <id> sent wrong formatted message.");
		// TODO send error msg to client & close WS connection (send frame with CLOSE opcode and proper status code)
	}
	catch (Poco::RangeException &ex)
	{
		logger_.log(ex);
		poco_error(logger_, "Client <id> passed out-of-range value in message.");
		// TODO send error msg to client & close WS connection
	}
	catch (Poco::NotImplementedException &ex)
	{
		logger_.log(ex);
		poco_error(logger_, "Client <id> passed wrong value type in message.");
		// TODO send error msg to client & close WS connection
	}
	catch (Poco::InvalidAccessException &ex)
	{
		logger_.log(ex);
		poco_error(logger_, "Client <id> sent empty message.");
		// TODO send error msg to client & close WS connection
	}
	catch (Poco::JSON::JSONException &ex)
	{
		logger_.log(ex);
		poco_error(logger_, "Client <id> sent not a JSON-formatted message.");
	}
	catch (Poco::SyntaxException &ex)
	{
		logger_.log(ex);
		poco_error(logger_, "Client <id>: syntax error.");
	}
	catch (Poco::TimeoutException &ex) 
	{
		logger_.log(ex);
		poco_error(logger_, "WebSocket timeout.");
	}
	catch (Poco::Net::NetException &ex)
	{
		logger_.log(ex);
		poco_error(logger_, "WebSocket Net error.");
	}
	/*catch (Poco::JSON::JSONTemplateException &ex)
	{
		logger_.log(ex);
		poco_error(logger_, "Got JSONTemplateException.");
	}
	catch (Poco::LogicException &ex)
	{
		logger_.log(ex);
		poco_error(logger_, "Got Poco::LogicException.");
	}*/
	catch (Poco::Exception &ex)
	{
		logger_.log(ex);
		poco_error(logger_, "Some other exception.");
	}
}
