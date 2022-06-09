#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

int main() {
	std::string str = "hi\0";
	std::string str1 = "hi";
	if (str != str1)
		std::cout << "OK\n";
	else
		std::cout << "NO\n";
	std::cout << str << " " << str.length() <<std::endl;
	std::cout << str1 << " " << str1.length() <<std::endl;
}