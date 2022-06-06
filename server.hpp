#ifndef SERVER_HPP
#define SERVER_HPP

#include "client.hpp"
#include "handle_command.hpp"
#include <vector>


struct fd_sets {
	fd_set read_set;
	fd_set write_set;
	int put_in_sets(const std::vector<Client> &vec);
};

class Server {
private:
	int					_port;
	std::string			_password;
	fd_sets				_sets;
	std::vector<Client> _clients;
public:
	Server(int port, std::string password);
	~Server();

	void start();
	void work();

	int size() const;
private:
	void sort_out(int max_fd);
	void new_client();
	void old_client(int i);

};

#endif

// 1 socket-server create error
// 2 socket-server bind error
// 3 server listen error
// 4 select error
// 5 send error