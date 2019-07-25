#ifndef BlockedCountries_h 
#define BlockedCountries_h 

#include <stdint.h>
#include <string>
#include <vector>

/**
 * Class that takes file name as input and returns blocked countries list
 */
class BlockedCountries
{
  private:
	/* file to read */
	std::string _input;

	/* container to store data */
	std::vector<std::string> _read_vector;

  public:
	/* Constructor */
	BlockedCountries(std::string);

	/** Destructor */
	~BlockedCountries() {};

	/** No Copy */
	BlockedCountries(const BlockedCountries &) = delete;

        /** No Copy assignment */
        BlockedCountries & operator=(const BlockedCountries&) = delete;
	
	/* IP address to block or not? */
	bool toBlock(std::string);

  private:
	/* returns blocked countries */
	void getList();

	/* returns country name for ip address */
	std::string getCountry(std::string);
};

#endif
