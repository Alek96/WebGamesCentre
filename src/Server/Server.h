/**
 * WebGamesCentre Server
*/

#ifndef WEBGAMESCENTRE_SERVER_H
#define WEBGAMESCENTRE_SERVER_H

#include "Poco/Util/ServerApplication.h"

class Server : public Poco::Util::ServerApplication
{
public:
	Server() : logger_(Poco::Util::Application::instance().logger()) {}
	~Server() {}

protected:
	void initialize(Application& self)
	{
		//Load default configuration files, if present. The config file(s) name shall be
		//the same as the executable's name.
		loadConfiguration();
		Poco::Util::ServerApplication::initialize(self);
	}

	void uninitialize()
	{
		Poco::Util::ServerApplication::uninitialize();
	}

	int main(const std::vector<std::string>& args);

private:
	Poco::Logger& logger_;
};

#endif //WEBGAMESCENTRE_SERVER_H