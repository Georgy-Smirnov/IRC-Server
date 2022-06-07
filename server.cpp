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
	int opt = 1;
	std::memset(&serv, 0, sizeof(serv));
	serv.sin_family = AF_INET;
	serv.sin_port = htons(_port);
	serv.sin_addr.s_addr = htonl(INADDR_ANY);

	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
		exit(1);
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt));
	int status = bind(sock, reinterpret_cast<const sockaddr *>(&serv), sizeof(serv));
	if (status == -1)
		exit(2);

	status = listen(sock, 10); // count?
	if (status == -1)
		exit(3);
	_clients.push_back(Client(sock, serv));
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

	for (iterator it = _clients.begin(); it < _clients.end(); ++it) {
		if (FD_ISSET(it->get_socket(), &_sets.read_set)) {
			if (it->get_socket() == _clients[0].get_socket()) {
				new_client();
				break;
			}
			else 
				old_client(it);
		}
	}
}

void Server::new_client() {
	struct sockaddr_in _this, client;
	socklen_t size = sizeof(client);

	int new_socket = accept(_clients[0].get_socket(), (struct sockaddr *)&client, &size);
	if (new_socket == -1)
		exit(5);
	_clients.push_back(Client(new_socket, client));
	send(new_socket, ":Welcome to the Internet Relay Network lol!lol@lol\r\n", 52, 0);
	std::cout << "New client: IP " << inet_ntoa(client.sin_addr) << " PORT: " << ntohs(client.sin_port) << std::endl;

}

void Server::old_client(iterator &i) {
	char buf[BUFFER_SIZE];

	int count_bytes = recv(i->get_socket(), buf, BUFFER_SIZE, 0);
	if (count_bytes == 0) {
		close(i->get_socket());
		_clients.erase(i);
		std::cout << "Bye!\n";
		return;
	}
	else if (count_bytes == 0) {
		exit(6);
	}
	std::string message = buf;
	if (message.back() == '\n')
		message.back() = 0;
	else
		message.push_back(0);
	// Handle_command handle(message, _clients, i);
	// if (!handle.check_password(_password))
	// 	send(i->get_socket(), "NEED REGISTR!\n", 14, 0);
	
	
	std::cout << message << std::endl;
}

int Server::size() const {
	return _clients.size();
}