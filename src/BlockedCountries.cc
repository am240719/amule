#include <iostream>
#include <fstream>
#include <algorithm>

#include <boost/algorithm/string.hpp>

#include "BlockedCountries.h"
#include "HttpClient.h"

/**
 * Constructor
 */
BlockedCountries::BlockedCountries(std::string Input)
 : _input(Input)
{
	getList();
}

/**
 * Read Countries from file
 */
void
BlockedCountries::getList()
{
	std::ifstream file(_input.c_str());

	if (file.fail()) {
		std::cerr << "Perror: " << _input.c_str() << '\n';
	}

	std::string line;
	while (std::getline(file, line)) 
		_read_vector.push_back(line);

	file.close();
}

/**
 * IP address to block or not? 
 */
bool
BlockedCountries::toBlock(std::string ip)
{

	std::string s = getCountry(ip);

	for (auto t: _read_vector) {
		// case insensitive comparision
		if (boost::iequals(s, t))
			return true;
	}

	return false;
}

/**
 * returns country name for ip address
 */
std::string
BlockedCountries::getCountry(std::string ip)
{
	HttpClient _client;
	
	std::string str(_client.getBody(ip));

	unsigned first = str.find(":") + 2;
	unsigned last = str.find("}") - 1;

	std::string substr(str.substr(first, last-first));

	return substr;	
}
