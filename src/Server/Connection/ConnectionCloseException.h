
#ifndef WEBGAMESCENTRE_CONNECTIONCLOSEEXCEPTION_H
#define WEBGAMESCENTRE_CONNECTIONCLOSEEXCEPTION_H

#include <exception>

class ConnectionCloseException : public std::exception
{
public:
    virtual const char *what() const noexcept override
    {
        return "WebSocket connection closed by client.";
    }
};


#endif //WEBGAMESCENTRE_CONNECTIONCLOSEEXCEPTION_H
