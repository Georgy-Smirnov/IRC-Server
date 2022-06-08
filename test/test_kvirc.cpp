#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

int main()
{
	int sock, listener;
	struct sockaddr_in addr;
	char buf[1024];
	int bytes_read;

	listener = socket(AF_INET, SOCK_STREAM, 0);
	if(listener < 0)
	{
		perror("socket");
		exit(1);
	}

	addr.sin_family = AF_INET;
	addr.sin_port = htons(6667);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		perror("bind");
		exit(2);
	}


	listen(listener, 1);

    sock = accept(listener, NULL, NULL);
	if(sock < 0)
	{
		perror("accept");
		exit(3);
	}
	printf("New user add:\n");
	
	while(1)
	{
		std::string str;
		bytes_read = recv(sock, buf, 1024, 0);
		if(bytes_read <= 0) break;
		if (buf[bytes_read - 1] == '\n')
			buf[bytes_read - 1] = 0;
		printf("recv: %s\n", buf);
		if (!strcmp(buf, "CAP LS")) {
			printf("Bye!\n");
			close(sock);
		}
		str = ":IRCat 451  :You have not registered";
		bytes_read = str.size();
		send(sock, str.c_str(), bytes_read, 0);
		printf("send: %s\n", str.c_str());

	}

	printf("User left!\n");
	close(listener);
}
