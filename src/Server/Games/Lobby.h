
#ifndef WEBGAMESCENTRE_LOBBY_H
#define WEBGAMESCENTRE_LOBBY_H

#include "../Player/Client.h" //"../Player/Client.h"
#include "LobbyEventHandler.h"

#include "Poco/Net/SocketReactor.h"
//#include "Poco/Net/WebSocket.h"
#include <mutex>

//class Poco::Net::WebSocket;

class Lobby
{
public:
    static Lobby& getInstance();

    void addPlayerToThisStage(Client player);
    void removePlayerFromThisStage(Client player);
    void removePlayerFromThisStage(Poco::Net::WebSocket &webSocket);

private:
    Lobby() : eventHandler_(*this), reactor_(/*select_timeout*/) {}
    Lobby(const Lobby&) = delete;
    Lobby& operator=(const Lobby&) = delete;

    Poco::Net::SocketReactor reactor_;
    LobbyEventHandler eventHandler_;
    std::size_t playersInThisStage_ = 0;
    mutable std::mutex reactorRunMutex_;
};


#endif //WEBGAMESCENTRE_LOBBY_H
