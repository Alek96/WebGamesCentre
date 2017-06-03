
#include "Connection.h"
#include "Poco/Util/Application.h"

using Poco::Net::WebSocket;

Poco::Logger &Connection::logger_ = Poco::Util::Application::instance().logger(); //TEMP

std::string Connection::readFromSocket(Poco::Net::WebSocket &webSocket) {

    //poco_information(logger_, "WebSocket connection established.");
    //Timespan timeout = ws.getReceiveTimeout();
    //poco_information(logger_, Poco::format("WebSocket revc timeout: %ds.", timeout.totalSeconds()));

    char buffer[MAX_WS_FRAME_LENGTH];
    int flags = 0;
    int n = 0;

    n = webSocket.receiveFrame(buffer, sizeof(buffer)-1, flags);
    poco_information(logger_, Poco::format("Frame received (length=%d, flags=0x%x).", n, unsigned(flags)));

    // Client-to-Server communication frames are masked
    // https://tools.ietf.org/html/rfc6455#section-5.3
    if ((flags & WebSocket::FRAME_OP_BITMASK) == WebSocket::FRAME_OP_PING)
    {
        /*// Ping frame MAY include "Application data"

        // https://tools.ietf.org/html/rfc6455#section-5.5.2
        poco_information(logger_, "Got PING frame. Sending back PONG frame.");
        // with same payload ("Application data")!
        flags &= 0xF0; // reset the PING frame opcode
        flags |= WebSocket::FRAME_OP_PONG;
        webSocket.sendFrame(buffer, n, flags);
        poco_information(logger_, Poco::format("Sent PONG. Length=%d, flags=0x%x.\n", n, unsigned(flags)));

        flags = 0;
        continue;*/
        poco_information(logger_, "Connection::read : Got PING frame!\n");
    }
    else if ((flags & WebSocket::FRAME_OP_BITMASK) == WebSocket::FRAME_OP_PONG)
    {
        /*// TODO match to a previously sent Ping frame (by the Server), if any
        //		Upon receipt of a Ping frame, an endpoint MUST send a Pong frame in
        //		response, unless it already received a Close frame.

        // TODO check payload equality to the corresponding Ping frame ?

        // no response needed
        buffer[n] = '\0';
        poco_information(logger_, Poco::format("Got Pong frame. Payload=\"%s\".\n", std::string(buffer)));
        continue;*/
        poco_information(logger_, "Connection::read : Got PONG frame!\n");
    }
    else if ((flags & WebSocket::FRAME_OP_BITMASK) == WebSocket::FRAME_OP_CLOSE)
    {
        /*// https://tools.ietf.org/html/rfc6455#section-5.5.1
        // Only if the Server did not previously send a Close frame!
        webSocket.sendFrame(buffer, n, flags);

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

        break;*/
        poco_information(logger_, "Connection::read : Got CLOSE frame!\n");
    }
    else if (n == 0)
    {
        poco_information(logger_, "Got 0 bytes of payload, and not Ping / Pong / Close frame.\n");
        /*// send Close frame?
        break;*/
    }

    buffer[n] = '\0';

    return std::string(buffer);

    // TODO handle WS(Net) Timeout exception
    /*catch (Poco::Net::WebSocketException &ex)
    {
        logger_.log(ex);
    }
    catch (Poco::TimeoutException &ex)
    {
        logger_.log(ex);
        poco_error(logger_, "WebSocket timeout.");
    }
    catch (Poco::Net::NetException &ex) {
        logger_.log(ex);
        poco_error(logger_, "WebSocket Net error.");
    }
    catch (Poco::Exception &ex)
    {
        logger_.log(ex);
        poco_error(logger_, "Some other exception.");
    }*/
}
