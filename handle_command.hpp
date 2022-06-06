#ifndef HANDLE_COMMAND_HPP
#define HANDLE_COMMAND_HPP

#include "client.hpp"
#include <vector>
#include <string>

class Handle_command {
	int								_fd;
	std::string						_command;
	std::vector<Client>&			_clients;
	std::vector<Client>::iterator	_it;
public:
	Handle_command(std::string buf, std::vector<Client> &clients, int i);
	int check_password(std::string pass);
};

#endif