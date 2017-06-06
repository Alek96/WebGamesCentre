
#ifndef WEBGAMESCENTRE_CONNECTIONHEARTBEATPONGEXCEPTION_H
#define WEBGAMESCENTRE_CONNECTIONHEARTBEATPONGEXCEPTION_H


#include <exception>

class ConnectionHeartbeatPongException : public std::exception
{
public:
    const char *what() const override
    {
        return "WebSocket PONG frame sent by client. No response is anticipated.";
    }
};


#endif //WEBGAMESCENTRE_CONNECTIONHEARTBEATPONGEXCEPTION_H
