
#include "Lobby.h"
#include "LobbyEventHandler.h"
#include "Poco/NObserver.h"
#include "Poco/Net/SocketNotification.h"

void Lobby::addPlayerToThisStage(Client player) {
    if(playersInThisStage_ == 0)
    {
        std::lock_guard<std::mutex> lock(reactorRunMutex_);
        if(playersInThisStage_ == 0)
            reactor_.run();
    }

    ++playersInThisStage_;

    reactor_.addEventHandler(
            player.getWebSocket(),
            Poco::NObserver<LobbyEventHandler, Poco::Net::ReadableNotification>(eventHandler_, &LobbyEventHandler::handleEvent)
    );
}

void Lobby::removePlayerFromThisStage(Client player) {
    reactor_.removeEventHandler(
            player.getWebSocket(),
            Poco::NObserver<LobbyEventHandler, Poco::Net::ReadableNotification>(eventHandler_, &LobbyEventHandler::handleEvent)
    );

    --playersInThisStage_;

    if(playersInThisStage_ == 0)
    {
        std::lock_guard<std::mutex> lock(reactorRunMutex_);
        if(playersInThisStage_ == 0)
            reactor_.stop();
    }
}

Lobby &Lobby::getInstance() {
    static Lobby instance;
    return instance;
}
