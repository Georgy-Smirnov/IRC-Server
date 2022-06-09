#ifndef SERVER_HPP
#define SERVER_HPP

#include "client.hpp"
#include "handle_command.hpp"
#include <vector>
#include <algorithm>

#define BUFFER_SIZE 1024
#define SERVER_NAME "Kjaco's_server"

struct fd_sets {
	fd_set read_set;
	fd_set write_set;
	int put_in_sets(const std::vector<Client> &vec);
};

class Server {
public:
	typedef std::vector<Client>::iterator iterator;
private:
	int							_port;
	std::string					_password;
	fd_sets						_sets;
	std::vector<Client> 		_clients;
	std::vector<std::string>	_nicks;
public:
	Server(int port, std::string password);
	~Server();

	void start();
	void work();

	const std::string get_name_server() const;
	bool find_nick(std::string& str) const;
	void put_nick(std::string& str);

	const std::string get_password() const;

	int size() const;
private:
	void sort_out(int max_fd);
	void new_client();
	void old_client(iterator &i);

};

#endif

// 1 socket-server create error
// 2 socket-server bind error
// 3 server listen error
// 4 select error
// 5 accept error
// 6 recv error
// 7 send error