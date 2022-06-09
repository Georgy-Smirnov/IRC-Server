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
	int				_socket;
	addrinfov4		_addrinfo;
	bool			_login;
	bool			_password;
	std::string		_nick;
	std::string 	_real_name;
public:	
	Client(int socket, addrinfov4 c) : _socket(socket), _addrinfo(c), _login(false), _password(false), _nick(std::string()), _real_name(std::string()) {}
	int get_socket() const { return _socket; }
	
	bool login() const { return _login; }
	void log_in() { _login = true; }
	void log_out() { _login = false; }

	void put_password() { _password = true; }
	void put_nick(std::string n) { _nick = n; }
	void put_real_name(std::string& n) { _real_name = n; }

	const bool get_password() const { return _password; }
	const std::string get_nick() const { return _nick; }
	const std::string get_real_name() const { return _real_name; }
	const std::string get_ip_address() const { return inet_ntoa(_addrinfo.sin_addr); }
	const std::string str_for_irc() const {
		std::string rezult = _nick + "!" + _real_name;
		rezult += "@" + get_ip_address();
		return rezult;
	}
};

#endif
