#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/time.h>
#include <fcntl.h>
#include <iostream>

int main(void) {
	fd_set rd_fds, wr_fds;
	struct timeval tv;

	FD_ZERO(&rd_fds);
	FD_SET(0, &rd_fds);
	FD_SET(1, &wr_fds);
	int fd3 = open("2", O_CREAT, S_IRWXU, O_RDONLY);
	FD_SET(fd3, &rd_fds);
	tv.tv_sec = 10;
	tv.tv_usec = 0;
	int max_num = 1;
	while (1) {
		for (size_t i = 0; i < 32; ++i)
			std::cout << rd_fds.fds_bits[i] << " ";
		std::cout << std::endl;
		int ret = select(max_num, &rd_fds, &wr_fds, NULL, &tv);
		if (ret) {
			for (size_t i = 0; i < 32; ++i)
				std::cout << rd_fds.fds_bits[i] << " ";
			std::cout << std::endl;
			
			printf("Data is ready\n");
			printf("FD_ISSET status: %u\n", FD_ISSET(0, &rd_fds));
			if (FD_ISSET(0, &rd_fds)) {
				char str[1024];
				scanf("%s", str);
				printf("%s\n", str);
			}
		}
		else {
			printf("TIMEOUT\n");
		}
	}
	return 0;
}
