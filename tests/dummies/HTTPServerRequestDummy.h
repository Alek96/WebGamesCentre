#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/NullStream.h"

#include "HTTPServerResponseDummy.h"

class HTTPServerRequestDummy : public Poco::Net::HTTPServerRequest
{
public:
	HTTPServerRequestDummy() : istreamDummy_(), socketAddr_(), serverParams_(new Poco::Net::HTTPServerParams) {}
	~HTTPServerRequestDummy() {}

	virtual std::istream & stream() override
	{
		return istreamDummy_;
	}
	virtual bool expectContinue() const override
	{
		return false;
	}
	virtual const Poco::Net::SocketAddress & clientAddress() const override
	{
		return socketAddr_;
	}
	virtual const Poco::Net::SocketAddress & serverAddress() const override
	{
		return socketAddr_;
	}
	virtual const Poco::Net::HTTPServerParams & serverParams() const override
	{
		return *serverParams_;
	}
	virtual Poco::Net::HTTPServerResponse & response() const override
	{
		return const_cast<HTTPServerResponseDummy&>(responseDummy_);
	}

protected:
	HTTPServerResponseDummy responseDummy_;
	Poco::NullInputStream istreamDummy_;
	Poco::Net::SocketAddress socketAddr_;			// default
	// (smart)pointer because HTTPServerParams has protected dstr and manages destruction itself
	Poco::Net::HTTPServerParams::Ptr serverParams_;	// default
};