/** ...file comment
*
*
*/

#ifndef WEBGAMESCENTRE_PAGE_REQUEST_HANDLER_H
#define WEBGAMESCENTRE_PAGE_REQUEST_HANDLER_H
//or: #pragma once

#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Util/Application.h"
#include "Poco/Logger.h"
#include <string>

/** Serves the requested page's resource. */
class PageRequestHandler : public Poco::Net::HTTPRequestHandler
{
public:
	PageRequestHandler(const std::string &contentType, const std::string &resourceRootDir, const std::string &resourceName, Poco::Logger &logger = Poco::Util::Application::instance().logger())
		: contentType_(contentType), resourceRootDir_(resourceRootDir), resourceName_(resourceName), logger_(logger) {}

	virtual void handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) override;

	// getter for testing
	const std::string& getContentType() const
	{
		return contentType_;
	}

protected:
	std::string contentType_;
	std::string resourceRootDir_;
	std::string resourceName_;

private:
	Poco::Logger& logger_;
};

#endif //WEBGAMESCENTRE_PAGE_REQUEST_HANDLER_H