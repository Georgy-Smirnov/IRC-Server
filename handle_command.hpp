#ifndef HANDLE_COMMAND_HPP
#define HANDLE_COMMAND_HPP

#include "client.hpp"
#include "server.hpp"
#include <vector>
#include <string>

class Server;

class Handle_command {
	Server*							_server;
	std::vector<Client>::iterator	_it;
	std::string						_prefix;
	std::string						_command;
	std::vector<std::string>		_parametrs;

	std::string do_for_login(void);
	std::string put_in_answer(std::string message);
	std::string welcome(void);
	std::string execute(void);
	std::string quit(void);
	std::string notice(void);
	std::string privmsg(void);
	std::string join(void);
	std::string invite(void);
	std::string kick(void);
	std::string ping(void);
	std::string pong(void);
public:
	Handle_command(std::vector<Client>::iterator &i, std::string comm, Server* s);
	std::string get_answer(void);
};

#endif

//asd
//asddas
//qwe