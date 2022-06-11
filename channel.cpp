#include "channel.hpp"
#include "message.hpp"

Channel::Channel(std::string& name, client_const_it& it) : _name(name) {
	_clients.push_back(&(*it));
}

void Channel::add_in_channel(client_const_it& it) {
	_clients.push_back(&(*it));
}

void Channel::send_in_channels(std::string str, client_const_it it) {
	for (client_const_point_it i = _clients.begin(); i < _clients.end(); ++i) {
		if (&(*it) != *i) 
			send((*i)->get_socket(), (const void *)(str.c_str()), str.length(), 0);
	}
}

void Channel::put_in_topic(std::string& t) {
	_topic = t;
}

const std::string Channel::get_names_users() const {
	std::string rezult = ":@";
	for (client_const_point_it i = _clients.begin(); i < _clients.end(); ++i) {
		rezult += (*i)->get_nick() + " ";
	}
	return rezult;
}

const std::string& Channel::get_name_channel() const {
	return _name;
}

const std::string Channel::get_topic_message(client_const_it it) const {
	if (_topic.size() == 0)
		return " 331 " + it->get_nick() + " " + _name + RPL_NOTOPIC;
	return " 332 " + it->get_nick() + " " + _name + " :" + _topic + "\r\n";
}

const std::string Channel::get_names_message(client_const_it it) const {
	return " 353 " + it->get_nick() + " = " + _name + " " + get_names_users() + "\r\n";
}
