#include "handle_command.hpp"

Handle_command::Handle_command(iterator &i, std::string comm, const Server* s) : _server(s), _it(i) {
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
		
	}
	return "1";
}

std::string Handle_command::do_for_login() {
	if (_command == "NICK") {
		
	}
	else if (_command == "USER") {

	}
	else if (_command == "PASS") {

	}
	return put_in_answer(" 451  :You have not registered\r\n");
}

std::string Handle_command::put_in_answer(std::string message) {
	std::string answer = ":";
	answer += _server->get_name_server();
	answer += message;
	return answer;
}
