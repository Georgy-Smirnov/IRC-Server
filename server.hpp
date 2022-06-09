#ifndef SERVER_HPP
#define SERVER_HPP

#include "client.hpp"
#include "handle_command.hpp"
#include "channel.hpp"
#include <algorithm>

#define BUFFER_SIZE 1024
#define SERVER_NAME "Kjaco's_server"
#define DELAY 10

struct fd_sets {
	fd_set read_set;
	int put_in_sets(const std::vector<Client> &vec);
};

class Server {
public:
	typedef std::vector<Client>::iterator iterator;
	typedef std::vector<Client>::const_iterator citerator;
private:
	int							_port;
	std::string					_password;
	fd_sets						_sets;
	std::vector<Client> 		_clients;
	std::vector<std::string>	_nicks;
	std::vector<Channel>		_channels;
	std::vector<std::string>	_chan;
public:
	Server(int port, std::string password);
	~Server();

	void start();
	void work();

	const std::string get_name_server() const;
	bool find_nick(std::string& str) const;
	void put_nick(std::string& str);

	const std::string get_password() const;
	const int get_socket_client(std::string& name) const;

	void exit_client(iterator& client);

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