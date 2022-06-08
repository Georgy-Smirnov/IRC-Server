#ifndef HANDLE_COMMAND_HPP
#define HANDLE_COMMAND_HPP

#include "client.hpp"
#include "server.hpp"
#include <vector>
#include <string>

class Server;

class Handle_command {
public:
	typedef std::vector<Client>::iterator iterator;
private:
	const Server*					_server;
	std::vector<Client>::iterator	_it;
	std::string						_prefix;
	std::string						_command;
	std::vector<std::string>		_parametrs;
public:
	Handle_command(iterator &i, std::string comm, const Server* s);
	std::string get_answer(void);
	std::string do_for_login(void);
	std::string put_in_answer(std::string message);
};

#endif