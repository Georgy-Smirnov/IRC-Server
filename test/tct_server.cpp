#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>

#define BUF_SIZE 1024


int readFromClient(int fd, char *buf) {
	int count_bytes;
	count_bytes = recv(fd, buf, BUF_SIZE, 0);
	if (count_bytes < 0)
		return -1;
	else
		std::cout << "Ok, server got message: " << buf << "\n";
	return count_bytes;
}

void writeToClient(int fd, char*buf) {
	int count_bytes;
	for (size_t i = 0; buf[i]; ++i)
		buf[i] = toupper(buf[i]);
	count_bytes = send(fd, buf, strlen(buf), 0);
	if (count_bytes < 0)
		exit(1);
	else
		std::cout << "Ok, server send message: " << buf << "\n";
}

int main(void) {
	int err, opt = 1;
	char buf[BUF_SIZE];
	int sock, new_sock;
	socklen_t size;
	
	fd_set active_set, read_set;

	struct sockaddr_in _this, _client;
	_this.sin_family = AF_INET;
	_this.sin_port = htons(5555);
	_this.sin_addr.s_addr = htonl(INADDR_ANY);

	sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock == -1)
		return 1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt));

	err = bind(sock, (struct sockaddr *)&_this, sizeof(_this));
	if (err == -1)
		return 1;

	err = listen(sock, 5);
	if (err == -1)
		return 1;

	FD_ZERO(&active_set);
	FD_SET(sock, &active_set);

	while (1) {
		read_set = active_set;
		if (select(FD_SETSIZE, &read_set, NULL, NULL, NULL) < 0) {
			std::cout << "select error!\n";
			return 1;
		}
		for (size_t i = 0; i < FD_SETSIZE; ++i){
			if (FD_ISSET(i, &read_set)) {
				if (i == sock) {
					size = sizeof(_client);
					new_sock = accept(sock, (struct sockaddr *)&_client, &size);
					if (new_sock == -1)
						return 1;
					std::cout << "New connect:\nIP: " << inet_ntoa(_client.sin_addr) << " PORT: " << ntohs(_client.sin_port) << std::endl;
					FD_SET(new_sock, &active_set);
				}
				else {
					err = readFromClient(i, buf);
					if (err <= 0) {
						close(i);
						FD_CLR(i, &active_set);
						std::cout << "Bye!\n";
					}
					else {
						writeToClient(i, buf);
					}
				}
			}
		}
	}
	close (sock);
}