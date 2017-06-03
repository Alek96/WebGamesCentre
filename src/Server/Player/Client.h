
#ifndef WEBGAMESCENTRE_CLIENT_H
#define WEBGAMESCENTRE_CLIENT_H

#include "Poco/Net/WebSocket.h"
#include "Poco/SharedPtr.h"

#include <string>


struct Client {
    Client(const std::string &playerName, const Poco::SharedPtr<Poco::Net::WebSocket> &playerWebSocket)
            : name_(playerName), webSocket_(playerWebSocket) {}

    std::string getPlayerName() { return name_; }
    Poco::Net::WebSocket& getWebSocket() { return *(webSocket_.get()); }
    Poco::SharedPtr<Poco::Net::WebSocket> getWebSocketPtr() { return webSocket_; }

private:
    std::string name_;
    Poco::SharedPtr<Poco::Net::WebSocket> webSocket_;
    //enum state
};


#endif //WEBGAMESCENTRE_CLIENT_H
