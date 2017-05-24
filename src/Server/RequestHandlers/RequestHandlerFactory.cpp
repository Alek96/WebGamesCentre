#include "RequestHandlerFactory.h"
#include "PageRequestHandler.h"
#include "WebSocketRequestHandler.h"

#include "Poco/Util/Application.h"

#include "Poco/Net/HTTPServerRequest.h"

#include <string>


Poco::Net::HTTPRequestHandler * RequestHandlerFactory::createRequestHandler(const Poco::Net::HTTPServerRequest &request)
{
	poco_information(logger_, "Request from "
		+ request.clientAddress().toString()
		+ ": "
		+ request.getMethod()
		+ " "
		+ request.getURI()
		+ " "
		+ request.getVersion()
	);

	/*for (auto it = request.begin(); it != request.end(); ++it)
	{
		poco_information(logger_, it->first + ": " + it->second);
	}*/

	if (request.find("Upgrade") != request.end() && Poco::icompare(request["Upgrade"], "websocket") == 0)
		return new WebSocketRequestHandler(logger_);

	std::string uri = request.getURI();

	std::string extension = uri.substr(uri.rfind(".")+1);
	//default: empty MIMEtype => response with 404 (Not Found) status code should be sent
	std::string MIMEtype = "";
		
	if (extension == "css")
		MIMEtype = "text/css";
	else if (extension == "js")
		MIMEtype = "text/javascript";
	else if (extension == "html" || extension == "htm" || uri == "/")
		MIMEtype = "text/html";
	else if (extension == "png")
		MIMEtype = "image/png";
	else if (extension == "map")
		MIMEtype = "application/json";

	return new PageRequestHandler(MIMEtype, webFilesRoot_, uri, logger_);
}
