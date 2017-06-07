
#ifndef WEBGAMESCENTRE_CONNECTIONHEARTBEATPINGEXCEPTION_H
#define WEBGAMESCENTRE_CONNECTIONHEARTBEATPINGEXCEPTION_H


#include <exception>

class ConnectionHeartbeatPingException : public std::exception
{
public:
    virtual const char *what() const noexcept override
    {
        return "WebSocket PING frame sent by client. Must send back PONG frame.";
    }
};


#endif //WEBGAMESCENTRE_CONNECTIONHEARTBEATPINGEXCEPTION_H
