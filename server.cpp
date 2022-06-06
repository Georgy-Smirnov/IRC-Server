#include "server.hpp"

int fd_sets::put_in_sets(const std::vector<Client> &vec) {
	FD_ZERO(&read_set);
	FD_ZERO(&write_set);
	int max = 0;
	std::vector<Client>::const_iterator first = vec.begin();
	while (first != vec.end()) {
		FD_SET(first->get_socket(), &read_set);
		// FD_SET(first->get_socket(), &write_set);
		if (first->get_socket() > max)
			max = first->get_socket();
		++first;
	}
	return max;
}

Server::Server(int port, std::string password) : _port(port), _password(password) {}

Server::~Server() {
	close(_port);
}

void Server::start() {
	struct sockaddr_in serv;
	std::memset(&serv, 0, sizeof(serv));
	serv.sin_family = AF_INET;
	serv.sin_port = htons(_port);
	serv.sin_addr.s_addr = htonl(INADDR_ANY);

	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
		exit(1);

	int status = bind(sock, reinterpret_cast<const sockaddr *>(&serv), sizeof(serv));
	if (status == -1)
		exit(2);

	status = listen(sock, 10); // count?
	if (status == -1)
		exit(3);
	_clients.push_back(Client(sock));
}

void Server::work() {
	int max_fd = _sets.put_in_sets(_clients);
	int status = select(++max_fd, &(_sets.read_set), &(_sets.write_set), NULL, NULL);
	if (status == -1)
		exit(4);	
	sort_out(max_fd);
}

void Server::sort_out(int max_fd) {
	struct sockaddr_in _this, client;
	socklen_t size = sizeof(client);

	for (size_t i = 0; i < max_fd; ++i) {
		if (FD_ISSET(i, &_sets.read_set)) {
			if (i == _clients[0].get_socket())
				new_client();
			else 
				old_client(i);
		}		
	}
}

void Server::new_client() {
	struct sockaddr_in _this, client;
	socklen_t size = sizeof(client);

	int new_socket = accept(_clients[0].get_socket(), (struct sockaddr *)&client, &size);
	if (new_socket == -1)
		exit(5);
	std::cout << "NEW!\n";
	_clients.push_back(Client(new_socket));
}

void Server::old_client(int i) {
	char buf[100];
	int count_bytes = recv(i, buf, 100, 0);
	if (count_bytes <= 0) {
		for (std::vector<Client>::iterator it = _clients.begin(); it < _clients.end(); ++it) {
			if (it->get_socket() == i) {
				_clients.erase(it);
			}
		}
		close(i);
		std::cout << "Bye!\n";
	}
	else {
		buf[count_bytes - 1] = 0;
		Handle_command handle(buf, _clients, i);
		if (!handle.check_password(_password))
			send(i, "NEED REGISTR!\n", 14, 0);
	}
}

int Server::size() const {
	return _clients.size();
}