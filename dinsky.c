#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>

int main(void) {
	struct sockaddr_in addr;
	struct hostent *hostinfo = NULL;
	hostinfo = gethostbyname("www.example.com");
	if (hostinfo == NULL) {
		printf("NO!\n");
		return 1;
	}
	addr.sin_family = AF_INET;
	addr.sin_port = htons(5555   );
	addr.sin_addr = *((struct in_addr *)hostinfo->h_addr);
	printf("%u\n", ntohl(addr.sin_addr.s_addr));

}