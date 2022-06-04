#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

/*
struct addrinfo {
 int ai_flags; // AI_PASSIVE, AI_CANONNAME, т.д.
 int ai_family; // AF_INET, AF_INET6, AF_UNSPEC
 int ai_socktype; // SOCK_STREAM, SOCK_DGRAM
 int ai_protocol; // используйте 0 для"any"
 size_t ai_addrlen; // размер ai_addr в байтах
 struct sockaddr *ai_addr; // struct sockaddr_in или _in6
 char *ai_canonname; // полное каноническое имя хоста
 struct addrinfo *ai_next; // связанный список, следующий
 };
*/

int main(int argc, char *argv[])
{
	if (argc != 2) {
		fprintf(stderr,"usage: showip hostname\n");
		return 1;
	}
	
	struct addrinfo hints, *res, *p;
	int status;
	char ipstr[INET6_ADDRSTRLEN];
	memset(&hints, 0, sizeof hints);
	
	hints.ai_family = AF_UNSPEC; // AF_INET или AF_INET6 если требуется
	hints.ai_socktype = SOCK_STREAM;

	if ((status = getaddrinfo(argv[1], NULL, &hints, &res)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
		return 2;
	}
	printf("IP addresses for %s:\n\n", argv[1]);
	for(p = res;p != NULL; p = p->ai_next) {
		void *addr;
		const char *ipver;
		// получить,
		// в IPv4 и IPv6 поля разные:
		if (p->ai_family == AF_INET) { // IPv4
			struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
			addr = &(ipv4->sin_addr);
			ipver = "IPv4";
		}
		else { // IPv6
			struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
			addr = &(ipv6->sin6_addr);
			ipver = "IPv6";
		}
		// перевести IP в строку и распечатать:
		inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
		printf(" %s: %s\n", ipver, ipstr);
	}
	freeaddrinfo(res); // освободить связанный список
	return 0;
} 