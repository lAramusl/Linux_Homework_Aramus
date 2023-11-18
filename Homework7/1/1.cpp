#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <cerrno>
#include <string>
int main(int argc, char** argv)
{
	if(argc != 3)
	{
		std::cout << "invalid arguments\n";
		exit(EXIT_FAILURE);
	}
	if(kill(std::stoi(argv[1]),std::stoi(argv[2])) == -1)
	{	
		std::perror("kill");
		exit(errno);
	}
	
	return 0;
}
