#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>

#define BUFFSIZE 100

int main(void) {
	struct sockaddr_in inf;
	memset(&inf, 0, sizeof(inf));

	inf.sin_family = AF_INET;
	inf.sin_port = htons(5555);
	inf.sin_addr.s_addr = htonl(INADDR_ANY);

	int socketfd = socket(PF_INET, SOCK_DGRAM, 0);
	if (socketfd == -1)
		return 1;
	int opt = 1;
	setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt));

	int status = bind(socketfd, (struct sockaddr *)&inf, sizeof(inf));
	if (status == -1)
		return 1;

	// fcntl(socketfd, F_SETFL, O_NONBLOCK); если раскоментировать, то не будет ждать на recvfrom 

	struct sockaddr_in from;
	memset(&inf, 0, sizeof(inf));
	socklen_t len = sizeof(from);

	while (1) {
		char buf[BUFFSIZE];
		memset(buf, 0, BUFFSIZE);

		status = recvfrom(socketfd, buf, BUFFSIZE, 0, (struct sockaddr *)&from, &len); // зависает и ждет, что прочитать

		buf[status] = 0;
		printf("New connect:\nIP: %s, PORT: %d\n", inet_ntoa(from.sin_addr), ntohs(from.sin_port));
		for (unsigned int i = 0; buf[i]; ++i)
			buf[i] = toupper(buf[i]);
		printf("OK, work is done!\n");

		status = sendto(socketfd, buf, strlen(buf) + 1, 0, (struct sockaddr *)&from, len);
		if (status != strlen(buf) + 1)
			return 1;
	}
	close(socketfd);
}
