/** ...file comment
*
*
*/

#ifndef WEBSOCKET_REQUEST_HANDLER__
#define WEBSOCKET_REQUEST_HANDLER__

#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Util/Application.h"
#include "Poco/Logger.h"

/** Serves the requested page's resource. */
class WebSocketRequestHandler : public Poco::Net::HTTPRequestHandler
{
public:
	WebSocketRequestHandler(Poco::Logger &logger = Poco::Util::Application::instance().logger())
		: logger_(logger) {}

	virtual void handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) override;

private:
	Poco::Logger& logger_;
};

#endif //WEBSOCKET_REQUEST_HANDLER__
