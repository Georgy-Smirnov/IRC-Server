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
public:
	typedef struct sockaddr*	pointer_addrinfo;
	typedef struct sockaddr_in	addrinfov4;
private:
	int			_socket;
	addrinfov4	_addrinfo;
	bool		_login;
	std::string	_name;
	std::string	_user;
public:
	Client(int socket, addrinfov4 c) : _socket(socket), _addrinfo(c), _login(0), _name(std::string()), _user(std::string()) {}
	int get_socket() const { return _socket; }
	bool login() const { return _login; }
	void log_in() { _login = true; }
	void log_out() { _login = false; }
};

#endif