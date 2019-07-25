#include <iostream>

#include "HttpClient.h"

#define KEY "2547c6cbc71ea22d56d658152216bf54"

namespace http = boost::beast::http;

/**
 * Default Constructor
 */
HttpClient::HttpClient()
 : _socket(_service), _resolver(_service), _host("api.ipstack.com"), _port("80")
{
}

/**
 * Destructor
 */
HttpClient::~HttpClient()
{
	boost::system::error_code ec;
	_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
}

/** 
 * Get Body of the response message 
 */
std::string
HttpClient::getBody(std::string ip)
{
	std::string temp;

	connect();

	request(ip);

	response(temp);
	
	return temp;
}

/**
 * Connect to Geo IP
 */
void
HttpClient::connect()
{
	boost::asio::ip::tcp::resolver::query query(_host, "http");

	boost::asio::connect(_socket, _resolver.resolve(query));
}

/**
 * Http Request message
 */
void
HttpClient::request(std::string & ip)
{
	std::string target("/");
	target += ip + "?access_key=" + KEY + "&fields=country_name";

	http::request<http::string_body> req{http::verb::get, target, 10};

	req.set(http::field::host, _host);
	req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

	http::write(_socket, req);
}

/**
 * Http Response
 */
void
HttpClient::response(std::string &temp)
{
	boost::beast::flat_buffer buffer;
	http::response<http::dynamic_body> res;
	
	http::read(_socket, buffer, res);

	temp = boost::beast::buffers_to_string(res.body().data());
}
