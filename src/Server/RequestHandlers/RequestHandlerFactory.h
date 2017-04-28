/** ...file comment
*
*
*/

#ifndef REQUEST_HANDLER_FACTORY__
#define REQUEST_HANDLER_FACTORY__

#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Util/Application.h"
#include "Poco/Logger.h"

/*
	@rzastey [TODO] Add namespaces reflexing file structure?
*/

class RequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory
{
public:
	RequestHandlerFactory(const std::string &webFilesRoot, Poco::Logger &logger = Poco::Util::Application::instance().logger())
		: webFilesRoot_(webFilesRoot), logger_(logger) {}

	virtual Poco::Net::HTTPRequestHandler * createRequestHandler(const Poco::Net::HTTPServerRequest &request) override;

protected:
	std::string webFilesRoot_;

private:
	Poco::Logger& logger_;
};

#endif //REQUEST_HANDLER_FACTORY__