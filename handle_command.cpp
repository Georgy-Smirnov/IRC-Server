#include "handle_command.hpp"

Handle_command::Handle_command(std::string &buf, std::vector<Client> &clients, iterator i) : _command(buf), _clients(clients), _fd(i->get_socket()) {
	_it = _clients.begin();
	while (_it->get_socket() != i->get_socket())
		++_it;
}

int Handle_command::check_password(std::string pass) {
	if (_it->login())
		return 1;
	else if (pass == _command) {
		_it->log_in();
		return 1;
	}
	return 0;
}