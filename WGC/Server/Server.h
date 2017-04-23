/**
 * WebGamesCentre Server
*/

#ifndef SERVER__
#define SERVER__

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
		ServerApplication::initialize(self);
	}

	void uninitialize()
	{
		ServerApplication::uninitialize();
	}

	int main(const std::vector<std::string>& args);

private:
	Poco::Logger& logger_;
};

#endif //SERVER__