#include "handle_command.hpp"

Handle_command::Handle_command(std::vector<Client>::iterator &i, std::string comm, Server* s) : _server(s), _it(i) {
	char rem = ' ';
	if (comm.front() == ':') {
		_prefix = comm.substr(1, comm.find(' ', 1) - 1);
		comm.erase(0, comm.find(' ', 1));
	}
	if (comm.front() == ' ')
		comm.erase(0, comm.find_first_not_of(' '));
	if (comm.find(' ') > comm.find(':') && comm.find(':') != std::string::npos)
		rem = ':';
	_command = comm.substr(0, comm.find(rem, 1));
	comm.erase(0, _command.length());
	comm.erase(0, comm.find_first_not_of(' '));
	while (comm.size() > 0) {
		comm.erase(0, comm.find_first_not_of(' '));
		rem = ' ';
		if (comm.find(' ') > comm.find(':') && comm.find(':') != std::string::npos)
			rem = ':';
		if (comm[0] == ':') {
			comm.erase(0, comm.find_first_not_of(' ', 1));
			_parametrs.push_back(comm.substr(0, comm.length()));
			break;
		}
		std::string tmp = comm.substr(0, comm.find(rem));
		_parametrs.push_back(tmp);
		comm.erase(0, tmp.length());
	}
	std::cout << "=============================================\n";
	std::cout << "Prefix: \"" << _prefix << "\"" << std::endl;
	std::cout << "Command: \"" << _command << "\"" << std::endl;
	std::cout << "Params: ";
	for (size_t i = 0; i < _parametrs.size(); ++i)
		std::cout << "\"" << _parametrs[i] << "\" ";
	std::cout << std::endl;
	std::cout << "=============================================\n";
}

std::string Handle_command::get_answer() {
	if (_it->login() == 0)
		return do_for_login();
	else {
		return execute();
	}
}

std::string Handle_command::do_for_login() {
	if (_command == "NICK") {
		if (_parametrs.size() < 1 || _parametrs.size() > 2)
			return put_in_answer(" 461  PASS :Not enough parameters\r\n");
		if (_server->find_nick(_parametrs[0]))
			return put_in_answer(" 433  " + _parametrs[0] + " :Nickname is already in use\r\n");
		if (_it->get_real_name().size() != 0 && !_it->get_password())
			return put_in_answer("");
		_it->put_nick(_parametrs[0]);
		_server->put_nick(_parametrs[0]);
		return (welcome());		
	}
	else if (_command == "USER") {
		if (_parametrs.size() < 4)
			return put_in_answer(" 461  PASS :Not enough parameters\r\n");
		if (_it->get_nick().size() != 0 && !_it->get_password())
			return put_in_answer("");
		_it->put_real_name(_parametrs[3]);
		return (welcome());
	}
	else if (_command == "PASS") {
		std::string s = _parametrs[0];
		std::string q = _server->get_password();
		if (_parametrs.size() != 1)
			return put_in_answer(" 461  PASS :Not enough parameters\r\n");
		if (_parametrs[0] != _server->get_password())
			return put_in_answer(" 464  :Password incorrect\r\n");
		_it->put_password();
		return (welcome());
		
	}
	return put_in_answer(" 451  :You have not registered\r\n");
}

std::string Handle_command::welcome() {
	if (_it->get_nick().size() != 0 && _it->get_password() && _it->get_real_name().size() != 0) {
		_it->log_in();
		std::string answer =	put_in_answer(" 375  : -" + _server->get_name_server() + "- Message of the day -\r\n") +
								put_in_answer(" 372  : Welcome!!!\r\n") +
								put_in_answer(" 376  : End of /MOTD command\r\n");
		return answer;
	}
	return ("");
}

std::string Handle_command::put_in_answer(std::string message) {
	if (message.size() == 0)
		return "-1";
	std::string answer = ":";
	answer += _server->get_name_server();
	answer += message;
	return answer;
}

std::string Handle_command::execute() {
	if (_command == "QUIT")
		return quit();
	else if (_command == "NOTICE")
		return notice();
	else if (_command == "PRIVMSG")
		return privmsg();
	else if (_command == "JOIN")
		return join();
	else if (_command == "INVITE")
		return invite();
	else if (_command == "KICK") 
		return kick();
	else if (_command == "PING") 
		return ping();
	else if (_command == "PONG") 
		return pong();
	else
		return put_in_answer(_command + " :Unknown command\r\n");
}

std::string Handle_command::quit() {
	return "1";
}

std::string Handle_command::notice() {
	return "1";
}

std::string Handle_command::privmsg() {
	// if (_parametrs.size() < 2)
	// 	return put_in_answer(" 461  PASS :Not enough parameters\r\n");
	// std::vector<std::string>::iterator it = _parametrs.begin();
	// std::string answer = "";
	// while (it < _parametrs.end() - 2) {
	// 	if (!_server->find_nick(*it))
	// 		return put_in_answer(" 401 " + *it + " :No such nick/channel\r\n");
	// 	answer += put_in_answer("PRIVMSG" + *it + " : " + _parametrs.back() + "\r\n");
	// }
	// return answew
	return "1";
}

std::string Handle_command::join() {
	return "1";
}

std::string Handle_command::invite() {
	return "1";
}

std::string Handle_command::kick() {
	return "1";
}

std::string Handle_command::ping() {
	return "1";
}

std::string Handle_command::pong() {
	return "1";
}
