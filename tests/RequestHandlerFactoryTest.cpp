#include "catch-framework/catch.hpp"
#include "dummies/HTTPServerRequestDummy.h"

#include "WGC/Server/RequestHandlers/RequestHandlerFactory.h"
#include "WGC/Server/RequestHandlers/PageRequestHandler.h"
#include "Poco/SharedPtr.h"
#include "Poco/AutoPtr.h"
#include "Poco/Logger.h"
#include "Poco/NullChannel.h"

using namespace Poco::Net;
using namespace Catch;

SCENARIO("RequestHandlerFactory returns appropriate RequestHandler", "[RequestHandlers]") {

	GIVEN("A RequestHandlerFactory") {
		Poco::AutoPtr<Poco::NullChannel> channelDummyPtr = new Poco::NullChannel;
		Poco::Logger& loggerDummy = Poco::Logger::create("dummy", channelDummyPtr);
		RequestHandlerFactory requestFactory("dummy", loggerDummy);
		HTTPServerRequestDummy request;

		WHEN("requested URI ends with '.css'") {
			request.setURI("moredummies.css");

			THEN("createRequestHandler method returns a PageRequestHandler method with ContentType == 'text/css'") {
				Poco::SharedPtr<PageRequestHandler> requestHandlerPtr = dynamic_cast<PageRequestHandler*>(requestFactory.createRequestHandler(request));
				REQUIRE(requestHandlerPtr.get() != nullptr);
				REQUIRE_THAT(requestHandlerPtr->getContentType(), Equals("text/css"));
			}
		}
		
	}
}