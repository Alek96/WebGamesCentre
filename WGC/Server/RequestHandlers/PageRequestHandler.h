/** ...file comment
*
*
*/

#ifndef PAGE_REQUEST_HANDLER__
#define PAGE_REQUEST_HANDLER__
//or: #pragma once

#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Util/Application.h"
#include "Poco/Logger.h"
#include <string>

/** Serves the requested page's resource. */
class PageRequestHandler : public Poco::Net::HTTPRequestHandler
{
public:
	PageRequestHandler(const std::string &contentType, const std::string &resourceRootDir, const std::string &resourceName)
		: contentType_(contentType), resourceRootDir_(resourceRootDir), resourceName_(resourceName), logger_(Poco::Util::Application::instance().logger()) {}

	virtual void handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) override;

protected:
	std::string contentType_;
	std::string resourceRootDir_;
	std::string resourceName_;

private:
	Poco::Logger& logger_;
};

#endif //PAGE_REQUEST_HANDLER__