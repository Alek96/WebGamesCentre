#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/NullStream.h"

class HTTPServerResponseDummy : public Poco::Net::HTTPServerResponse
{
public:
	HTTPServerResponseDummy() : ostreamDummy_() {}
	~HTTPServerResponseDummy() {}

	virtual void sendContinue() override {}
	virtual std::ostream & send() override
	{
		return ostreamDummy_;
	}
	virtual void sendFile(const std::string & path, const std::string & mediaType) override {}
	virtual void sendBuffer(const void * pBuffer, std::size_t length) override {}
	virtual void redirect(const std::string & uri, HTTPStatus status = HTTP_FOUND) override {}
	virtual void requireAuthentication(const std::string & realm) override {}
	virtual bool sent() const override
	{
		return false;
	}

protected:
	Poco::NullOutputStream ostreamDummy_;
};