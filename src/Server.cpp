/**
 * WebGamesCentre Server's source
*/

#include "WGC/Server/Server.h"
#include "WGC/Server/RequestHandlers/RequestHandlerFactory.h"
 
#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/ServerSocket.h"

#include <iostream>

int Server::main(const std::vector<std::string>& args)
{
	// get parameters from configuration file
	unsigned short port = (unsigned short)config().getInt("server.port", 8080);

	// @rzastey [TODO] Check also command-line options. Write port to config file if found in option?
	std::string webFilesRoot = config().getString("client.root", "");
	if (webFilesRoot == "")
	{
		poco_fatal(logger_, "Web files root dir not specified. Exiting application.");
		return Application::EXIT_CONFIG;
		//or EXIT_USAGE ?
	}

	Poco::Net::ServerSocket svs(port);
	Poco::Net::HTTPServer srv(new RequestHandlerFactory(webFilesRoot), svs, new Poco::Net::HTTPServerParams);

	srv.start();
	poco_information(logger_, "Server started.");

	// wait for CTRL-C or kill
	waitForTerminationRequest();

	srv.stop();
	poco_information(logger_, "Server stopped.");

	//underlying sockets of all client connections are shut down, causing all requests to abort
	//server.stopAll(true);

	return Application::EXIT_OK;
}

POCO_SERVER_MAIN(Server)
