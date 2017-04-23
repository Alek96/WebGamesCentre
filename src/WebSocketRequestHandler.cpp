/** ...file comment
*
*
*/

#include "WGC/Server/RequestHandlers/WebSocketRequestHandler.h"

#include "Poco/Net/WebSocket.h"
#include "Poco/Net/NetException.h"
#include "Poco/Net/HTTPServerResponse.h"

using Poco::Net::WebSocket;

void WebSocketRequestHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
	try
	{
		WebSocket ws(request, response);
		poco_information(logger_, "WebSocket connection established.");

		// @rzastey [TODO] Poco::Buffer
		char buffer[1024];
		int flags;
		int n;
		do
		{
			n = ws.receiveFrame(buffer, sizeof(buffer), flags);
			poco_information(logger_, Poco::format("Frame received (length=%d, flags=0x%x).", n, unsigned(flags)));
			ws.sendFrame(buffer, n, flags);
		} while (n > 0 && (flags & WebSocket::FRAME_OP_BITMASK) != WebSocket::FRAME_OP_CLOSE);

		poco_information(logger_, "WebSocket connection closed.");
	}
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
}
