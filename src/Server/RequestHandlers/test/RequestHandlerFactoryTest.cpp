#include "3rd-party/catch.hpp"
#include "dummies/HTTPServerRequestDummy.h"

#include "../RequestHandlerFactory.h"
#include "../PageRequestHandler.h"
#include "Poco/SharedPtr.h"
#include "Poco/AutoPtr.h"
#include "Poco/Logger.h"
#include "Poco/NullChannel.h"

using namespace Poco::Net;
using namespace Catch;

SCENARIO("RequestHandlerFactory returns appropriate RequestHandler", "[RequestHandlers]")
{
	// neccessary setup (dummies)
	Poco::AutoPtr<Poco::NullChannel> channelDummyPtr = new Poco::NullChannel;
	Poco::Logger& loggerDummy = Poco::Logger::get("dummy");
	loggerDummy.setChannel(channelDummyPtr);

	GIVEN("A RequestHandlerFactory object")
	{
		RequestHandlerFactory requestFactory("dummy", loggerDummy);
		HTTPServerRequestDummy request;

		WHEN("Requested URI ends with '.css'") 
		{
			request.setURI("moredummies.css");
			Poco::SharedPtr<PageRequestHandler> requestHandlerPtr = dynamic_cast<PageRequestHandler*>(requestFactory.createRequestHandler(request));

			THEN("createRequestHandler method returns a PageRequestHandler object")
			{				
				REQUIRE(requestHandlerPtr.get() != nullptr);
			}
			THEN("PageRequestHandler object returned by createRequestHandler method has ContentType == 'text/css'")
			{
				REQUIRE_THAT(requestHandlerPtr->getContentType(), Equals("text/css"));
			}
		}

		WHEN("Requested URI ends with '.js'")
		{
			request.setURI("moredummies.js");
			Poco::SharedPtr<PageRequestHandler> requestHandlerPtr = dynamic_cast<PageRequestHandler*>(requestFactory.createRequestHandler(request));

			THEN("createRequestHandler method returns a PageRequestHandler object")
			{
				REQUIRE(requestHandlerPtr.get() != nullptr);
			}
			THEN("PageRequestHandler object returned by createRequestHandler method has ContentType == 'text/javascript'")
			{
				REQUIRE_THAT(requestHandlerPtr->getContentType(), Equals("text/javascript"));
			}
		}

		WHEN("Requested URI ends with '.html'")
		{
			request.setURI("moredummies.html");
			Poco::SharedPtr<PageRequestHandler> requestHandlerPtr = dynamic_cast<PageRequestHandler*>(requestFactory.createRequestHandler(request));

			THEN("createRequestHandler method returns a PageRequestHandler object")
			{
				REQUIRE(requestHandlerPtr.get() != nullptr);
			}
			THEN("PageRequestHandler object returned by createRequestHandler method has ContentType == 'text/html'")
			{
				REQUIRE_THAT(requestHandlerPtr->getContentType(), Equals("text/html"));
			}
		}

		WHEN("Requested URI ends with '.htm'")
		{
			request.setURI("moredummies.htm");
			Poco::SharedPtr<PageRequestHandler> requestHandlerPtr = dynamic_cast<PageRequestHandler*>(requestFactory.createRequestHandler(request));

			THEN("createRequestHandler method returns a PageRequestHandler object")
			{
				REQUIRE(requestHandlerPtr.get() != nullptr);
			}
			THEN("PageRequestHandler object returned by createRequestHandler method has ContentType == 'text/html'")
			{
				REQUIRE_THAT(requestHandlerPtr->getContentType(), Equals("text/html"));
			}
		}

		WHEN("Requested URI is '/'")
		{
			request.setURI("/");
			Poco::SharedPtr<PageRequestHandler> requestHandlerPtr = dynamic_cast<PageRequestHandler*>(requestFactory.createRequestHandler(request));

			THEN("createRequestHandler method returns a PageRequestHandler object")
			{
				REQUIRE(requestHandlerPtr.get() != nullptr);
			}
			THEN("PageRequestHandler object returned by createRequestHandler method has ContentType == 'text/html'")
			{
				REQUIRE_THAT(requestHandlerPtr->getContentType(), Equals("text/html"));
			}
		}

		WHEN("Requested URI ends with none of: '.html', '.htm', '.css', '.js'; and is not: '/'. For example ends with '.x'")
		{
			request.setURI("moredummies.x");
			Poco::SharedPtr<PageRequestHandler> requestHandlerPtr = dynamic_cast<PageRequestHandler*>(requestFactory.createRequestHandler(request));

			THEN("createRequestHandler method returns a PageRequestHandler object")
			{
				REQUIRE(requestHandlerPtr.get() != nullptr);
			}
			THEN("PageRequestHandler object returned by createRequestHandler method has ContentType == ''")
			{
				REQUIRE_THAT(requestHandlerPtr->getContentType(), Equals(""));
			}
		}
		
	}
}