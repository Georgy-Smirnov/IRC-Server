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

void Handle_command::handle_exec() {
	if (_it->login() == 0) {
		std::string tmp = do_for_login();
		int count_bytes = send(_it->get_socket(), (const void *)(tmp.c_str()), tmp.length(), 0);
		if (count_bytes == -1 || tmp == "-1") {
			exit(7);
		}
		return;
	}
	else
		execute();
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

std::string Handle_command::create_welc_message() {
	std::string rezult = ":" + _server->get_name_server() + " 001 ";
	rezult += _it->get_nick() + " :Welcome to the Internet Relay Network ";
	rezult += _it->str_for_irc() + "\r\n";
	return rezult;
}

void Handle_command::send_motd() {
	send_message(_it->get_socket(), put_in_answer(" 375  : -" + _server->get_name_server() + "- Message of the day -\r\n"));
	send_message(_it->get_socket(), put_in_answer(" 372  : \r\n"));
	send_message(_it->get_socket(), put_in_answer(" 372  : HELLO, WORLD!!!\r\n"));
	send_message(_it->get_socket(), put_in_answer(" 372  : \r\n"));
	send_message(_it->get_socket(), put_in_answer(" 372  : WELCOME TO IRC SERVER\r\n"));
	send_message(_it->get_socket(), put_in_answer(" 372  : \r\n"));
	send_message(_it->get_socket(), put_in_answer(" 372  : \r\n"));
	send_message(_it->get_socket(), put_in_answer(" 376  : End of /MOTD command\r\n"));		
}

std::string Handle_command::welcome() {
	if (_it->get_nick().size() != 0 && _it->get_password() && _it->get_real_name().size() != 0) {
		_it->log_in();
		send_message(_it->get_socket(), create_welc_message());
		send_motd();
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

void Handle_command::execute() {
	if (_command == "QUIT")
		quit();
	else if (_command == "NOTICE")
		privmsg(0);
	else if (_command == "PRIVMSG")
		privmsg(1);
	else if (_command == "JOIN")
		join();
	else if (_command == "INVITE")
		invite();
	else if (_command == "KICK") 
		kick();
	else if (_command == "PING") 
		ping();
	else if (_command == "PONG") 
		pong();
	else {
		send_message(_it->get_socket(), put_in_answer(_command + " :Unknown command\r\n"));
	
	}
}

void Handle_command::send_message(int sock, std::string str) {
	int count_bytes = send(sock, str.c_str(), str.length(), 0);
	if (count_bytes == -1)
		exit(7);
}

std::string Handle_command::create_priv_message(std::string& name, std::string& mes, bool flag) {
	std::string rezult = ":" + _it->str_for_irc() + " ";
	if (flag == 0)
		rezult += " NOTICE ";
	else
		rezult += " PRIVMSG ";
	rezult += name + " : " + mes + "\r\n";
	return rezult;
}

void Handle_command::quit() {

}

void Handle_command::privmsg(bool flag) {
	if (_parametrs.size() < 2) {
		send_message(_it->get_socket(), put_in_answer(" 461  PASS :Not enough parameters\r\n"));
		return;
	}
	for (size_t i = 0; i < _parametrs.size() - 1; ++i) {
		if (!_server->find_nick(_parametrs[i])) {
			send_message(_it->get_socket(), put_in_answer(" 401 " + _parametrs[i] + " :No such nick/channel\r\n"));
			return;
		}
		std::string answer = create_priv_message(_parametrs[i], _parametrs[_parametrs.size() - 1], flag);
		send_message(_server->get_socket_client(_parametrs[i]), answer);
	}
}

void Handle_command::join() {}

void Handle_command::invite() {}

void Handle_command::kick() {}

void Handle_command::ping() {}

void Handle_command::pong() {}
