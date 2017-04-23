/** ...file comment
 *
 *
*/

#include "WGC/Server/RequestHandlers/PageRequestHandler.h"

//#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/HTTPServerResponse.h"

void PageRequestHandler::handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response)
{
	//response.setChunkedTransferEncoding(true);
	//response.setContentType(contentType_);

	if (contentType_ == "")
	{ 
		response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
		resourceName_ = "/html/not-found.html";
		contentType_ = "text/html";
	}
	else if (resourceName_ == "/")
		resourceName_ = "/html/index.html";

	std::string resource = resourceRootDir_ + resourceName_;
	
	try
	{
		response.sendFile(resource, contentType_);
	}
	catch (Poco::FileNotFoundException &)
	{
		/*
			@rzastey [TODO] Ensure that not-found.html is found!!
		*/
		response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
		std::string pageNotFound = resourceRootDir_ + "/html/not-found.html";
		response.sendFile(pageNotFound, "text/html");
	}
	catch (Poco::Exception &ex)
	{
		logger_.log(ex);
		response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
		std::string pageNotFound = resourceRootDir_ + "/html/not-found.html";
		response.sendFile(pageNotFound, "text/html");
	}

	// @rzastey [TODO] Second logger for debugging (poco_debug).
	poco_information(logger_, Poco::format(
		"Response: %u %s.",
		static_cast<unsigned>(response.getStatus()),
		response.getReason()/*,
		response.getDate().raw()*/
	));
}

/*
	@rzastey [TODO] Add contentType validation [?]
		Maybe some map with enum - string mappings?
*/
