#include "handle_command.hpp"

Handle_command::Handle_command(std::string buf, std::vector<Client> &clients, int i) : _command(buf), _clients(clients), _fd(i) {
	_it = _clients.begin();
	while (_it->get_socket() != i)
		++_it;
}

int Handle_command::check_password(std::string pass) {
	if (_it->get_login())
		return 1;
	else if (pass == _command)
		return 1;
	std::cout << pass << " " << _command << std::endl;
	std::cout << pass.length() << " " << _command.length() << std::endl;
	return 0;
}