
#ifndef WEBGAMESCENTRE_LOBBYEVENTHANDLER_H
#define WEBGAMESCENTRE_LOBBYEVENTHANDLER_H

#include "Poco/AutoPtr.h"
#include "Poco/Net/SocketNotification.h"
#include "Poco/Logger.h"
#include "Poco/Util/Application.h"

class Lobby;

class LobbyEventHandler {
public:
    typedef Poco::AutoPtr<Poco::Net::ReadableNotification> ReadableNotificationPtr;

    //LobbyEventHandler(/*Lobby &lobby*/) : logger_(Poco::Util::Application::instance().logger()) {} //TEMP  /*lobby_(lobby), */

    LobbyEventHandler(Lobby &lobby) : lobby_(lobby), logger_(Poco::Util::Application::instance().logger()) {} //TEMP

    void handleSocketReadableEvent(const ReadableNotificationPtr &notification);
    void sendMessageToClient(); //TODO

private:
    Poco::Logger &logger_;
    Lobby &lobby_;
};


#endif //WEBGAMESCENTRE_LOBBYEVENTHANDLER_H
