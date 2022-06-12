#include "channel.hpp"
#include "message.hpp"

Channel::Channel(std::string& name, client_const_it& it) : _name(name), _topic(std::string()), _mode(std::string()) {
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

void Channel::put_in_topic(std::string& t, client_const_it it) {
	_topic = t;
}

short Channel::put_in_mode(std::string& m, client_const_it it) {
	std::string flags = "opsitnmlbvk";
	if (&(*it) != _clients[0])
		return 1;
	if (m[0] == '+') {
		for (size_t i = 1; i < m.length(); ++i) {
			if (flags.find(m[i]) == std::string::npos)
				return 3;
			if (_mode.find(m[i]) != std::string::npos)
				return 2;
			_mode.push_back(m[i]);
			send_in_channels(":" + it->str_for_irc() + " MODE " + _name + " +" + m[i] + "\r\n", it);
		}
	}
	else if (m[0] == '-') {
		for (size_t i = 1; i < m.length(); ++i) {
			if (flags.find(m[i]) == std::string::npos)
				return 3;
			if (_mode.find(m[i]) == std::string::npos)
				return 2;
			send_in_channels(":" + it->str_for_irc() + " MODE " + _name + " +" + m[i] + "\r\n", it);
			_mode.erase(_mode.find(m[i]));
		}
	}
	else
		return 3;
	return 0;
}

short Channel::kick_from_channel(std::string& m, client_const_it it) {
	if (&(*it) != _clients[0])
		return 1;
	for (client_const_point_it i = _clients.begin(); i < _clients.end(); ++i) {
		if ((*i)->get_nick() == m) {
			send_in_channels(":" + it->str_for_irc() + " KICK " + _name + " " + (*i)->get_nick() + " :" + it->get_nick() + "\r\n", it);
			_clients.erase(i);
			return 0;
		}
	}
	return 2;
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

