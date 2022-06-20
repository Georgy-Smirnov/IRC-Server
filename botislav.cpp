#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <iostream>
#include <time.h>

bool work = true;
int sock_sig = 0;
// :b!b@127.0.0.1 PRIVMSG a : Hello
void sig_handler(int signal)
{
	(void)signal;
	// std::cout << "Bliiin" << std::endl;
	work = false;
	send(sock_sig, "QUIT\r\n", 6, 0);
}

void auth(int sock, const std::string &pass)
{
	std::string pass_("PASS "), nick_("NICK bot\r\n"), user_("USER a a a :a\r\n");

	if (send(sock, (pass_ + pass + "\r\n").c_str(), (pass_ + pass + "\r\n").length(), 0) < 0)
	{
		std::cout << "Could not auth. Pass error" << std::endl;
		exit (1);
	}
	if (send(sock, nick_.c_str(), nick_.length(), 0) < 0)
	{
		std::cout << "Could not auth. Nick error" << std::endl;
		exit (1);
	}
	if (send(sock, user_.c_str(), user_.length(), 0) < 0)
	{
		std::cout << "Could not auth. User error" << std::endl;
		exit (1);
	}
}

void draw_tree(int sock, std::string const &name)
{
	std::string s1("PRIVMSG " + name + " :|......._-_.......|" + "\r\n");
	std::string s2("PRIVMSG " + name + " :|..../~~...~~\\....|" + "\r\n");
	std::string s3("PRIVMSG " + name + " :|./~~.........~~\\.|" + "\r\n");
	std::string s4("PRIVMSG " + name + " :|{...............}|" + "\r\n");
	std::string s5("PRIVMSG " + name + " :|.\\.._-.....-_../.|" + "\r\n");
	std::string s6("PRIVMSG " + name + " :|...~..\\\\.//..~...|" + "\r\n");
	std::string s7("PRIVMSG " + name + " :|_-.-...|.|._-._..|" + "\r\n");
	std::string s8("PRIVMSG " + name + " :|.._.-..|.|...-_..|" + "\r\n");
	std::string s9("PRIVMSG " + name + " :|......//.\\\\......|" + "\r\n");

	send(sock, s1.c_str(), s1.length(), 0);
	send(sock, s2.c_str(), s2.length(), 0);
	send(sock, s3.c_str(), s3.length(), 0);
	send(sock, s4.c_str(), s4.length(), 0);
	send(sock, s5.c_str(), s5.length(), 0);
	send(sock, s6.c_str(), s6.length(), 0);
	send(sock, s7.c_str(), s7.length(), 0);
	send(sock, s8.c_str(), s8.length(), 0);
	send(sock, s9.c_str(), s9.length(), 0);
}

std::string extract_nick(std::string &message)
{
	std::string ret;
	for (std::string::iterator It = message.begin() ; It != message.end(); ++It)
	{
		if (*It == '!')
		{
			ret = std::string(++message.begin(), It);
			break ;
		}
	}
	return (ret);
}

void message_processing(int sock, std::string &message)
{
	if (message.find("PRIVMSG") == std::string::npos)
		return ;
	std::string name = extract_nick(message);
	draw_tree(sock, name);
}


int main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cout << "Usage: ./bot <port> <password>" << std::endl;
		exit (0);
	}


	int sock;
	sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(atoi(argv[1]));
	inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

	int opt = 1;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt));
	connect(sock, (sockaddr *)&server, sizeof(server));

	// fcntl(sock, F_SETFL, O_NONBLOCK);
	auth(sock, std::string(argv[2]));
	char buf[512];

	signal(SIGINT, sig_handler);
	sock_sig = sock;
	std::string message;
	while (work)
	{	memset(buf, 0, 512);
		message.clear();
		if (recv(sock, buf, 512, 0) < 0)
		{
			std::cout << "gg" << std::endl;
			break;
		}
		message = buf;
		message_processing(sock, message);
		// std::cout << buf << std::endl;
	}
}
