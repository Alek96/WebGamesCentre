
#include "LobbyEventHandler.h"
#include "../Connection/Connection.h" //"../Connection/Connection.h"
#include "../Connection/ConnectionCloseException.h"
#include "../Connection/ConnectionHeartbeatPingException.h"
#include "../Connection/ConnectionHeartbeatPongException.h"
#include "Lobby.h"
#include "Poco/Net/WebSocket.h"

using Poco::Net::ReadableNotification;
using Poco::Net::WebSocket;

void LobbyEventHandler::handleSocketReadableEvent(const LobbyEventHandler::ReadableNotificationPtr &notification) {
    //if(dynamic_cast<ReadableNotification*>(notification.get()))
    //{
        // can now read from the socket without blocking
    poco_information(Poco::Util::Application::instance().logger(), "LobbyHandler handleReadableEvent.");
    WebSocket ws = notification->socket();
    try
    {
        Connection::readFromSocket(ws);
    }
    catch(ConnectionCloseException &)
    {
        Connection::close(ws);
        lobby_.removePlayerFromThisStage(ws);
        //if flag CLOSE or (0-length-payload)(?) -> client disconnected
        //TODO remove from clients collection
        //unregister all eventHandlers for this socket
    }


    //}
}
