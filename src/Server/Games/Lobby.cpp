
#include "Lobby.h"
#include "LobbyEventHandler.h"
#include "Poco/NObserver.h"
#include "Poco/Net/SocketNotification.h"
#include "Poco/ThreadPool.h"

void Lobby::addPlayerToThisStage(Client player)
{
    if(playersInThisStage_ == 0)
    {
        poco_information(Poco::Util::Application::instance().logger(), "First player in lobby.");
        std::lock_guard<std::mutex> lock(reactorRunMutex_);
        poco_information(Poco::Util::Application::instance().logger(), "First player in lobby after mutex.");
        if(playersInThisStage_ == 0) {
            poco_information(Poco::Util::Application::instance().logger(), "Reactor will be run.");
            Poco::ThreadPool::defaultPool().start(reactor_, "Lobby");
            //reactor_.run();
            poco_information(Poco::Util::Application::instance().logger(), "Reactor run in separate thread.");
        }
    }

    ++playersInThisStage_;
    poco_information(Poco::Util::Application::instance().logger(), "Players in lobby incremented.");
    reactor_.addEventHandler(
            player.getWebSocket(),
            Poco::NObserver<LobbyEventHandler, Poco::Net::ReadableNotification>(eventHandler_, &LobbyEventHandler::handleSocketReadableEvent)
    );
    poco_information(Poco::Util::Application::instance().logger(), "Registered lobby event handler for new socket.");
}

void Lobby::removePlayerFromThisStage(Client player)
{
    poco_information(Poco::Util::Application::instance().logger(), "Will remove lobby event handler.");
    reactor_.removeEventHandler(
            player.getWebSocket(),
            Poco::NObserver<LobbyEventHandler, Poco::Net::ReadableNotification>(eventHandler_, &LobbyEventHandler::handleSocketReadableEvent)
    );

    --playersInThisStage_;

    if(playersInThisStage_ == 0)
    {
        std::lock_guard<std::mutex> lock(reactorRunMutex_);
        if(playersInThisStage_ == 0)
            reactor_.stop();
        poco_information(Poco::Util::Application::instance().logger(), "Lobby reactor stopped.");
    }
}

void Lobby::removePlayerFromThisStage(Poco::Net::WebSocket &webSocket)
{
    poco_information(Poco::Util::Application::instance().logger(), "Will remove lobby event handler.");
    reactor_.removeEventHandler(
            webSocket,
            Poco::NObserver<LobbyEventHandler, Poco::Net::ReadableNotification>(eventHandler_, &LobbyEventHandler::handleSocketReadableEvent)
    );

    --playersInThisStage_;

    if(playersInThisStage_ == 0)
    {
        std::lock_guard<std::mutex> lock(reactorRunMutex_);
        if(playersInThisStage_ == 0)
            reactor_.stop();
        poco_information(Poco::Util::Application::instance().logger(), "Lobby reactor stopped.");
    }
}

Lobby &Lobby::getInstance()
{
    poco_information(Poco::Util::Application::instance().logger(), "Got lobby instance.");
    static Lobby instance;
    return instance;
}
