#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>

#define BUFFSIZE 100

int main(int argc, const char** argv) {
	if (argc != 2)
		return 1;
	struct sockaddr_in _this;
	struct sockaddr_in _server;
	struct hostent *server;
	socklen_t len = sizeof(_server);

	memset(&_this, 0, sizeof(_this));
	memset(&_server, 0, sizeof(_server));
	memset(&server, 0, sizeof(server));
	
	server = gethostbyname("127.0.0.1");
	if (server == NULL)
		return 1;
	_server.sin_family = server->h_addrtype;
	_server.sin_port = htons(5555);
	_server.sin_addr = *(struct in_addr *)server->h_addr_list[0];

	_this.sin_family = AF_INET;
	_this.sin_port = htons(5556);
	_this.sin_addr.s_addr = htonl(INADDR_ANY);

	int sock = socket(PF_INET, SOCK_DGRAM, 0);
	if (sock == 0)
		return 1;
	int opt = 1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt));
	
	int status = bind(sock, (struct sockaddr *)&_this, (socklen_t)sizeof(_this));
	
	int count_byte = 0;
	count_byte = sendto(sock, argv[1], strlen(argv[1]) + 1, 0, (struct sockaddr *)&_server, (socklen_t)sizeof(_server));
	if (count_byte != strlen(argv[1]) + 1)
		return 1;
	
	char buf[BUFFSIZE];
	memset(buf, 0, BUFFSIZE);
	count_byte = recvfrom(sock, buf, BUFFSIZE, 0, (struct sockaddr *)&_server, &len);

	printf("%s\n", buf);
	close(sock);
}