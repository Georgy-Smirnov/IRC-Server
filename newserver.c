#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>

int main(void) {
	struct sockaddr_in inf;
	memset(&inf, 0, sizeof(inf));
	inf.sin_family = AF_INET;
	inf.sin_port = htons(5555);
	inf.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	int socketfd = socket(PF_INET, SOCK_STREAM, 0);
	if (socketfd == -1)
		return 1;
	int status = bind(socketfd, (struct sockaddr *)&inf, sizeof(inf));
	if (status == -1)
		return 1;
	status = listen(socketfd, 5);
	if (status == -1)
		return 1;
	struct sockaddr_in new_inf;
	socklen_t l = sizeof(new_inf);
	printf("Hello!\n");
	int new_sock = accept(socketfd, (struct sockaddr *)&new_inf, &l);
	if (new_sock < 0)
		return 1;
	printf("%hu %u\n", ntohs(new_inf.sin_port), ntohl(new_inf.sin_addr.s_addr));
	char buf[100];
    int bytes_read;
	bytes_read = recv(new_sock, buf, 100, 0);
	int i = 0;
	while (buf[i] != '\0')
		++i;
	buf[i] = '!';
	buf[++i] = '\0';
	bytes_read = send(new_sock, buf, 101, 0);
	close(new_sock);
	close(socketfd);
}
