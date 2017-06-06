
#ifndef WEBGAMESCENTRE_CONNECTIONHEARTBEATPINGEXCEPTION_H
#define WEBGAMESCENTRE_CONNECTIONHEARTBEATPINGEXCEPTION_H


#include <exception>

class ConnectionHeartbeatPingException : public std::exception
{
public:
    const char *what() const override
    {
        return "WebSocket PING frame sent by client. Must send back PONG frame.";
    }
};


#endif //WEBGAMESCENTRE_CONNECTIONHEARTBEATPINGEXCEPTION_H
