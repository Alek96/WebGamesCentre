
#ifndef WEBGAMESCENTRE_LOBBYEVENTHANDLER_H
#define WEBGAMESCENTRE_LOBBYEVENTHANDLER_H

#include "Poco/AutoPtr.h"
#include "Poco/Net/SocketNotification.h"
#include "Poco/Logger.h"
#include "Poco/Util/Application.h"

class LobbyEventHandler {
public:
    typedef Poco::AutoPtr<Poco::Net::ReadableNotification> ReadableNotificationPtr;

    LobbyEventHandler() : logger_(Poco::Util::Application::instance().logger()) {} //TEMP

    void handleEvent(const ReadableNotificationPtr &notification);
    void sendMessageToClient(); //TODO

private:
    Poco::Logger &logger_;
};


#endif //WEBGAMESCENTRE_LOBBYEVENTHANDLER_H
