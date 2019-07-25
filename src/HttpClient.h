#ifndef HttpClient_h
#define HttpClient_h

#include <string>

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>

class HttpClient
{
  private:
	/** io service */
	boost::asio::io_context _service;

	/** socket */
	boost::asio::ip::tcp::socket _socket;

	/** Name resolution */
	boost::asio::ip::tcp::resolver _resolver;

	/** HTTP host */
	std::string _host; 

	/** HTTP port*/
	std::string _port;

  public:
	/* Default Constructor */
	HttpClient();

	/* Destructor */
	~HttpClient();

	/* Return contents of the body for HTTP GET */
	std::string getBody(std::string); 

  private:
	/** Connect to GeoIP */
	void connect();

	/* Post a request */
	void request(std::string &);

	/* Get a response*/
	void response(std::string &);
};

#endif
