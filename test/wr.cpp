#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

int main() {
	char buf[1];
	std::string str;
	int sz;
	int fd = open("2", O_CREAT, S_IRWXU, O_RDONLY);
	while ((sz = read(fd, buf, 1)) > 0) {
		if (sz != 2)
			buf[sz] = 0;
		str += buf;
	}
	std::cout << str <<std::endl;
}