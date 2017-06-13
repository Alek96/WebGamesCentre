/** ...file comment
*
*
*/

#ifndef WEBGAMESCENTRE_WEBSOCKET_REQUEST_HANDLER_H
#define WEBGAMESCENTRE_WEBSOCKET_REQUEST_HANDLER_H

#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Util/Application.h"
#include "Poco/Logger.h"

/** Accepts connection via WebSocket protocol. */
class WebSocketRequestHandler : public Poco::Net::HTTPRequestHandler
{
public:
	WebSocketRequestHandler(Poco::Logger &logger = Poco::Util::Application::instance().logger())
		: logger_(logger) {}

	virtual void handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) override;

private:
	Poco::Logger& logger_;
};

#endif //WEBGAMESCENTRE_WEBSOCKET_REQUEST_HANDLER_H
