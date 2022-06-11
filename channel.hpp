#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "client.hpp"
#include <vector>

class Channel {
public:
	typedef std::vector<Client>::const_iterator client_const_it;
	typedef std::vector<const Client*>::const_iterator client_const_point_it;
private:
	std::string					_name;
	std::string					_topic;
	std::vector<const Client*> 	_clients;
public:
	Channel(std::string& name, client_const_it& it);
	void add_in_channel(client_const_it& it);
	const std::string get_names_users() const;
	const std::string& get_topic() const;
	
	const std::string& get_name_channel() const;

	const std::string get_topic_message() const;
	const std::string get_names_message() const;
};

#endif