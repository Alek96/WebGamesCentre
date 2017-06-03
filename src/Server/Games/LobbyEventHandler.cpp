
#include "LobbyEventHandler.h"
#include "../Connection/Connection.h"
#include "Poco/Net/WebSocket.h"

using Poco::Net::ReadableNotification;
using Poco::Net::WebSocket;

void LobbyEventHandler::handleEvent(const LobbyEventHandler::ReadableNotificationPtr &notification) {
    //if(dynamic_cast<ReadableNotification*>(notification.get()))
    //{
        // can now read from the socket without blocking
        WebSocket ws = notification->socket();
        Connection::readFromSocket(ws);

    //}
}
