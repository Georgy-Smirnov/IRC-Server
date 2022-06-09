#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "client.hpp"
#include <vector>

class Channel {
	std::string				_name;
	std::vector<Client&> 	_clients;
public:
	Channel();
	void add_in_channel();
};

#endif