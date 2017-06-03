/** ...file comment
*
*
*/

#include "WebSocketRequestHandler.h"
#include "../Player/Clients.h"
#include "../Player/Client.h"
#include "../Games/Lobby.h"

#include "Poco/Net/WebSocket.h"
#include "Poco/Net/NetException.h"
#include "Poco/Net/HTTPServerResponse.h"

using Poco::Net::WebSocket;

void WebSocketRequestHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
	try
	{
		Poco::SharedPtr<WebSocket> wsPtr(new WebSocket(request, response));
		poco_information(logger_, "WebSocket connection established.");
        //Clients::getInstance().addClient("player1", wsPtr);   // TODO player name
        // Clients - vector/set/map of Client structures ?
        Client newPlayer("player1", wsPtr);
        Lobby::getInstance().addPlayerToThisStage(newPlayer);
	}
	catch (Poco::Net::WebSocketException &ex)
	{
		logger_.log(ex);
		switch (ex.code())
		{
			case WebSocket::WS_ERR_HANDSHAKE_UNSUPPORTED_VERSION:
				response.set("Sec-WebSocket-Version", WebSocket::WEBSOCKET_VERSION);
				// fallthrough
			case WebSocket::WS_ERR_NO_HANDSHAKE:
			case WebSocket::WS_ERR_HANDSHAKE_NO_VERSION:
			case WebSocket::WS_ERR_HANDSHAKE_NO_KEY:
				response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
				response.setContentLength(0);
				response.send();
				break;
		}
	}
	catch (Poco::Exception &ex)
	{
		logger_.log(ex);
		poco_error(logger_, "Some other exception.");
	}
}
