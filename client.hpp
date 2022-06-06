#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>

class Client {
	int			_socket;
	bool		_login;
	std::string	_name;
	std::string	_user;
public:
	Client(int socket) : _socket(socket), _login(0), _name(std::string()), _user(std::string()) {}
	int get_socket() const { return _socket; }
	bool get_login() const { return _login; }
};

#endif