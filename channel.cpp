#include "channel.hpp"

Channel::Channel(std::string& name, client_const_it& it) : _name(name) {
	_clients.push_back(&(*it));
}

void Channel::add_in_channel(client_const_it& it) {
	_clients.push_back(&(*it));
}