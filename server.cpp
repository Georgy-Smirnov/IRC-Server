#include "server.hpp"

Server::Server(unsigned int port, std::string password) : _port(port), _password(password) {}

Server::~Server() {
	close(_port);
}

void Server::start() {
	struct sockaddr_in serv;
	std::memset(&serv, 0, sizeof(serv));
	serv.sin_family = AF_INET;
	serv.sin_port = htons(_port);
	serv.sin_addr.s_addr = htonl(INADDR_ANY);

	_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (_sock == -1)
		exit(1);

	int status = bind(_sock, reinterpret_cast<const sockaddr *>(&serv), sizeof(serv));
	if (status == -1)
		exit(2);

	status = listen(_sock, 10); // count?
	if (status == -1)
		exit(3);
}