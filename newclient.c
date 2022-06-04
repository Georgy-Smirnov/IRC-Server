#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>

int main(int argc, const char** argv) {
	struct hostent *hostinf;
	hostinf = gethostbyname("127.0.0.1");
	if (hostinf == NULL)
		return 1;
	if (argc != 2)
		return 1;
	struct sockaddr_in inf;
	memset(&inf, 0, sizeof(inf));
	inf.sin_family = hostinf->h_addrtype;
	inf.sin_port = htons(5555);
	inf.sin_addr = *(struct in_addr *)hostinf->h_addr_list[0];
	int socketfd = socket(PF_INET, SOCK_STREAM, 0);
	if (socketfd == -1)
		return 1;
	int status = connect(socketfd, (struct sockaddr *)&inf, sizeof(inf));
	if (status == -1)
		return 1;
	char buf2[101];
    int bytes_read;
	bytes_read = send(socketfd, argv[1], 13, 0);
	bytes_read = recv(socketfd, buf2, 101, 0);
	printf("%s\n", buf2);
}