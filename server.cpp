#include "server.hpp"

// PUBLIC MEMBERS

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
	reserve_put_vectors(sock, serv);
}

int Server::put_in_set(fd_set* read_set) {
	FD_ZERO(read_set);
	int max = 0;
	client_const_it first = _clients.begin();
	while (first != _clients.end()) {
		FD_SET(first->get_socket(), read_set);
		if (first->get_socket() > max)
			max = first->get_socket();
		++first;
	}
	return max;
}

void Server::work() {
	fd_set read_set;
	struct sockaddr_in _this, client;
	socklen_t size = sizeof(client);

	int max_fd = put_in_set(&read_set);
	int status = select(++max_fd, &(read_set), NULL, NULL, NULL);
	if (status == -1) {
		exit(4);	
	}

	for (client_it it = _clients.begin(); it < _clients.end(); ++it) {
		if (FD_ISSET(it->get_socket(), &read_set)) {
			if (it->get_socket() == _clients[0].get_socket()) {
				new_client();
				break;
			}
			else 
				old_client(it);
		}
	}
}

size_t Server::count_clients() const {
	return _clients.size();
}

const std::string Server::get_name_server() const {
	return _clients[0].get_nick();
}

bool Server::find_nick(const std::string& str) const {
	for (str_pointer_it i = _nicks.begin(); i < _nicks.end(); ++i) {
		if (*(*i) == str)
			return true;
	}
	return false;
}

void Server::put_nick(const std::string& str) {
	_nicks.push_back(&str);
}

bool Server::find_chan(const std::string& str) const {
	for (str_pointer_it i = _chan.begin(); i < _chan.end(); ++i) {
		if (*(*i) == str)
			return true;
	}
	return false;
}

void Server::put_chan(const std::string& str) {
	_chan.push_back(&str);
}

const std::string Server::get_password() const {
	return _password;
}

Server::client_it Server::get_client(std::string& name) {
	for (client_it i = _clients.begin(); i < _clients.end(); ++i) {
		if (i->get_nick() == name)
			return i;
	}
	return _clients.begin();
}

Server::channel_it Server::get_chanel(std::string& name) {
	for (channel_it i = _channels.begin(); i < _channels.end(); ++i) {
		if (i->get_name_channel() == name)
			return i;
	}
	return _channels.begin();
}

const int Server::get_socket_client(std::string& name) const {
	for (client_const_it i = _clients.begin(); i < _clients.end(); ++i) {
		if (i->get_nick() == name)
			return i->get_socket();
	}
	return 0;
}

void Server::create_channels(std::string &name, client_const_it it) {
	_channels.push_back(Channel(name, it));
}

void Server::add_in_channel(std::string &name, client_const_it it) {
	get_chanel(name)->add_in_channel(it);
}

void Server::exit_client(client_it client) {
	if (client->get_nick().size() != 0) {
		for (str_pointer_it i = _nicks.begin(); i < _nicks.end(); ++i) {
			if (**i == client->get_nick()) {
				_nicks.erase(i);
				break;
			}
		}
	}
	close(client->get_socket());
	_clients.erase(client);
}

void Server::restart_server() {
	_chan.erase(_chan.begin(), _chan.end());
	_channels.erase(_channels.begin(), _channels.end());
	_nicks.erase(_nicks.begin(), _nicks.end());
	while (_clients.size() != 1) {
		close(_clients.rbegin()->get_socket());
		_clients.pop_back();
	}
}

//PRIVATE MEMBERS:

void Server::reserve_put_vectors(int& sock, struct sockaddr_in& serv) {
	try {
		_clients.reserve(COUNT_CLIENTS);
		_nicks.reserve(COUNT_CLIENTS);
		_channels.reserve(COUNT_CHANNEL);
		_chan.reserve(COUNT_CHANNEL);
	}
	catch(const std::exception&) {
		exit(8);
	}	
	_clients.push_back(Client(sock, serv));
	_clients[0].log_in();
	_clients[0].put_nick(SERVER_NAME);
}

void Server::new_client() {
	struct sockaddr_in _this, client;
	socklen_t size = sizeof(client);

	int new_socket = accept(_clients[0].get_socket(), (struct sockaddr *)&client, &size);
	if (new_socket == -1)
		exit(5);
	_clients.push_back(Client(new_socket, client));

	std::cout << "New client: IP " << inet_ntoa(client.sin_addr) << " PORT: " << ntohs(client.sin_port) << std::endl;

}

void Server::old_client(client_it &i) {
	char buf[BUFFER_SIZE];
	std::memset(buf, 0, BUFFER_SIZE);
	int count_bytes = recv(i->get_socket(), buf, BUFFER_SIZE, 0);
	if (count_bytes == 0) {
		exit_client(i);
		std::cout << "Bye!\n";
		return;
	}
	else if (count_bytes == -1) {
		exit(6);
	}
	std::string message = buf;
	if (message.back() == '\n') {
		message.pop_back();
		if (message.back() == '\r')
			message.pop_back();
	}
	while (message.size()) {
		std::string tmp = message.substr(0, message.find("\r\n"));
		message.erase(0, tmp.length() + 2);
		std::cout << "Message: " << tmp << std::endl;
		Handle_command handle(i, tmp, this);
		handle.handle_exec();
	}
}
