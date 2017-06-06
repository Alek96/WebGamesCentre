
#ifndef WEBGAMESCENTRE_CONNECTIONCLOSEEXCEPTION_H
#define WEBGAMESCENTRE_CONNECTIONCLOSEEXCEPTION_H

#include <exception>

class ConnectionCloseException : public std::exception
{
public:
    const char *what() const override
    {
        return "WebSocket connection closed by client.";
    }
};


#endif //WEBGAMESCENTRE_CONNECTIONCLOSEEXCEPTION_H
