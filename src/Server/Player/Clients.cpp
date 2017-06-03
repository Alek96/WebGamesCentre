#include "Clients.h"

void Clients::addClient(const std::string &playerName, const Poco::SharedPtr<Poco::Net::WebSocket> &webSocketPtr)
{
    std::lock_guard<std::mutex> lock(mutex_);
    clientsWebSocketMap_.emplace(std::make_pair(playerName, webSocketPtr));
}

Poco::SharedPtr<Poco::Net::WebSocket> Clients::getWebSocket(const std::string &playerName)
{
    std::lock_guard<std::mutex> lock(mutex_);
    auto iter = clientsWebSocketMap_.find(playerName);
    if(iter != clientsWebSocketMap_.end())
    {
        return iter->second;
    }
    return nullptr;
}

void Clients::removeClient(const std::string &playerName)
{
    std::lock_guard<std::mutex> lock(mutex_);
    clientsWebSocketMap_.erase(playerName);
}

Clients& Clients::getInstance()
{
    static Clients instance;
    return instance;
}
