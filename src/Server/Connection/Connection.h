
#ifndef WEBGAMESCENTRE_CONNECTION_H
#define WEBGAMESCENTRE_CONNECTION_H

#include "Poco/Net/WebSocket.h"

#include <string>
#include "Poco/Logger.h"

class Connection {
public:
    static std::string readFromSocket(Poco::Net::WebSocket &webSocket);
    static std::string writeToSocket(Poco::Net::WebSocket &webSocket);
    //static void sendPing(Poco::Net::WebSocket &webSocket);
    static void performHeartbeat(Poco::Net::WebSocket &webSocket);

    static const std::size_t MAX_WS_FRAME_LENGTH = 1024;

private:
    static Poco::Logger &logger_;
};


#endif //WEBGAMESCENTRE_CONNECTION_H
