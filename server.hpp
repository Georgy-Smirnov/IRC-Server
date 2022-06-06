#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <cstring>
 #include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>

class Server {
	int			_sock;
	int			_port;
	std::string	_password;
public:
	Server(unsigned int port, std::string password);
	~Server();

	void start();
};

#endif

// 1 socket-server create error
// 2 socket-server bind error
// 3 server listen error