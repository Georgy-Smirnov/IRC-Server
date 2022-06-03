#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h> //for struct socketaddr_in

/*
prototype:
int socket(int domain, int type, int protocol);
create new socket;
DOMAIN: AF_UNIX or AF_INET; af - address family;
AF_UNIX for proccess exchange at 1 pc;
AF_INET internet-domain;

TYPE: type socket;
SOCK_STREAM - protocol TCP;
SOCK_DGRAM - protocol UDP;
SOCK_RAW - protocol ICMP;
if use AF_UNIX then only SOCK_STREAM;

PROTOCOL: use 0 for auto choose.

return: socket descriptor;
*/

/*
prototype:
int bind(int sockfd, struct sockaddr *addr, int addrlen);
bind socket with address;
SOCKFD: socket descriptor;
ADDR:
struct sockaddr {
	unsigned short	sa_family; //addres family, AF_xxx, use DOMAIN.
	char			sa_data[14]; //14byte for address
}

Use other struct for put in sa_data:
struct socketaddr_in {
	short int			sin_family; // address family, = sa_family;
	unsigned short int	sin_port; // number of port;
	struct in_addr		sin_addr; // IP-address;
	unsigned char		sin_zero[8]; // aligned for sizeof(sockaddr) = sizeof(sockaddr_in);
}
or
struct socketaddr_un {} 

struct in_addr {
	unsigned long s_addr;
}
ADDRLEN: size of struct;

htons - Host To Network Short;
htonl - Host To Network Long;
ntohs - Network To Host Short;
ntohl - Network To Host Long;

*/

int main(int argc, const char** argv){
	// Create a socket
	int listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == -1) {
		std::cerr << "Can't create a socket! Quitting" << std::endl;
		return -1;
	}
	// Bind the ip address and port to a socket
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(54000);
	inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);
	bind(listening, (sockaddr*)&hint, sizeof(hint));
}
