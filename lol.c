#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(int argc, char**argv) {
	int status;
	struct addrinfo hints, *res;
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC; // использовать либо IPv4 либо IPv6
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE; // заполнить мой IP для меня
	status = getaddrinfo("127.0.0.1", "3490", &hints, &res);
	if (status == -1) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
		return 2;
	}
	int sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if (sockfd == -1) {
		fprintf(stderr,"Socket create error\n");
		return 1;		
	}

	status = bind(sockfd, res->ai_addr, res->ai_addrlen);
	if (status == -1) {
		fprintf(stderr, "bind: %s\n", gai_strerror(status));
		return 2;
	}

	/*
	int socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if (socketfd == -1) {
		write(1, "Error1\n", 7);
		return 1;
	}
	int status;
	struct sockaddr_in info;

	memset(&info, 0, sizeof(info));
	info.sin_family = AF_UNIX;
	info.sin_port = htons(54000);
	inet_pton(AF_INET, "0.0.0.0", &(info.sin_addr));

	status = bind(socketfd, (struct sockaddr *)&info, sizeof(info));
	if (status == -1) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
		return 1;
	}
	struct sockaddr_in client;
	socklen_t client_sz = sizeof(client);
	listen(socketfd, 5);
	int clientSocket = accept(socketfd, (struct sockaddr *)&client, &client_sz);
	*/
}

/*
struct addrinfo hints, *res;
 int sockfd, new_fd;
// !! не забудьте проверить ошибки для этих вызовов !!
 // сначала заполнить адресные структуры с помощью getaddrinfo():
memset(&hints, 0, sizeof hints);
hints.ai_family = AF_UNSPEC; // использовать либо IPv4 либо IPv6
hints.ai_socktype = SOCK_STREAM;
 hints.ai_flags = AI_PASSIVE; // заполнить мой IP для меня
 getaddrinfo(NULL, MYPORT, &hints, &res);
 // создать сокет, связать и слушать:
sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
bind(sockfd, res->ai_addr, res->ai_addrlen);
 listen(sockfd, BACKLOG);
 // принять входящие подключения:
addr_size = sizeof their_addr;
 new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);
// связываемся по дескриптору сокета new_fd!
...
*/