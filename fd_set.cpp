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

int main() {
	fd_set active_set;
	int fd3 = open("2", O_CREAT, S_IRWXU, O_RDONLY);
	int fd4 = open("1", O_CREAT, S_IRWXU, O_RDONLY);
	std::cout << "NUMBER FILEDIS: " << fd3 << std::endl;
	std::cout << "NUMBER FILEDIS: " << fd4 << std::endl;

	for (size_t i = 0; i < 32; ++i)
		std::cout << active_set.fds_bits[i] << " ";
	std::cout << std::endl;
	FD_ZERO(&active_set);
	for (size_t i = 0; i < 32; ++i)
		std::cout << active_set.fds_bits[i] << " ";
	std::cout << std::endl;
	FD_SET(fd3, &active_set); // 0000 1000 << 3
	FD_SET(fd4, &active_set); // 0001 0000 << 4
	for (size_t i = 0; i < 32; ++i)
		std::cout << active_set.fds_bits[i] << " ";
	std::cout << std::endl;
	close(fd3);
	close(fd4);
}