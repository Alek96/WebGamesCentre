
#ifndef WEBGAMESCENTRE_LOBBY_H
#define WEBGAMESCENTRE_LOBBY_H

#include "../Player/Client.h"
#include "LobbyEventHandler.h"

#include "Poco/Net/SocketReactor.h"
#include <mutex>

using Poco::Net::SocketReactor;

class Lobby {
public:
    static Lobby& getInstance();

    void addPlayerToThisStage(Client player);
    void removePlayerFromThisStage(Client player);

private:
    Lobby() : reactor_(/*select_timeout*/) {}
    Lobby(const Lobby&) = delete;
    Lobby& operator=(const Lobby&) = delete;

    SocketReactor reactor_;
    LobbyEventHandler eventHandler_;
    std::size_t playersInThisStage_ = 0;
    std::mutex reactorRunMutex_;
};


#endif //WEBGAMESCENTRE_LOBBY_H
