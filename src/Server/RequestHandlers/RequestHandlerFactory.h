/** ...file comment
*
*
*/

#ifndef WEBGAMESCENTRE_REQUEST_HANDLER_FACTORY_H
#define WEBGAMESCENTRE_REQUEST_HANDLER_FACTORY_H

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

#endif //WEBGAMESCENTRE_REQUEST_HANDLER_FACTORY_H