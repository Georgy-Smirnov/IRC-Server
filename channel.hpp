#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "client.hpp"
#include <vector>

class Channel {
public:
	typedef std::vector<Client>::const_iterator client_const_it;
private:
	std::string					_name;
	std::vector<const Client*> 	_clients;
public:
	Channel(std::string& name, client_const_it& it);
	void add_in_channel(client_const_it& it);
};

#endif