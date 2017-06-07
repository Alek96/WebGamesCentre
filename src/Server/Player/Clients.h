#ifndef WEBGAMESCENTRE_CLIENTS_H
#define WEBGAMESCENTRE_CLIENTS_H

#include "Poco/Net/WebSocket.h"
#include <mutex>

class Clients {
public:
    static Clients& getInstance();

    Poco::SharedPtr<Poco::Net::WebSocket> getWebSocket(const std::string &playerName);

    void addClient(const std::string &playerName, const Poco::SharedPtr<Poco::Net::WebSocket> &webSocketPtr);
    void removeClient(const std::string &playerName);

private:
    Clients() : clientsWebSocketMap_() {}
    Clients(const Clients&) = delete;
    Clients& operator=(const Clients&) = delete;

    std::map<std::string, Poco::SharedPtr<Poco::Net::WebSocket> > clientsWebSocketMap_;
    mutable /*static*/ std::mutex mutex_;
};


#endif //WEBGAMESCENTRE_CLIENTS_H
