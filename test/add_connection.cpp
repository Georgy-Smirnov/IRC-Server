#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
/*
prototype:
int listen(int sockfd, int backlog);
create turn for connection;
SOCKFD: socket descriptor;
BACKLOG: sizeof turn; SOMAXCONN = 128, for Linux;

prototype:
int accept(int socketfd, void *addr, int *addrlen);
create new socket for client;
SOCKETFD: socket descriptor server;
ADDR: write info about client;
ADDRLEN: sizeof addr;
ADDR and ADDRLEN may be NULL, if I don't want to use client's info;

prototype:
int connect(int sockfd, struct addr *serv_addr, int addrlen);
connect with server;
SOCKFD: socket descriptor client;
SERV_ADDR: struct server;
ADDRLEN: sizeof struct server;
OS auto bind client socket;
*/
