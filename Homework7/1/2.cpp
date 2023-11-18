#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <cerrno>

void siegHandler(int siegheil)
{
	static unsigned int SIGUSR2_count = 0;
	if(siegheil == SIGUSR2)
	{
		++SIGUSR2_count;
	}
	if(siegheil == SIGUSR1)
	{}
	if(siegheil == SIGINT)
	{
		std::cout << SIGUSR2_count << std::endl;
		exit(0);
	}
}

int main()
{
	std::cout << "My Pid is: " << getpid() << std::endl;
	struct sigaction sieg = {};
	sieg.sa_handler = siegHandler;
	if(sigaction(SIGUSR2, &sieg,nullptr) == -1)
	{
		std::perror("siegaction: SIGUSR2");
		exit(errno);
	}
	if(sigaction(SIGINT, &sieg, nullptr) == -1)
	{
		std::perror("siegaction: SIGINT");
		exit(errno);
	}
	if(sigaction(SIGUSR1, &sieg,nullptr) == -1)
	{
		std::perror("siegaction: SIGUSR1");
		exit(errno);
	}
	while(true)
	{
		std::cout<< "SIEG HEIL!!" <<std::endl;
		sleep(5);
	}
	return 0;

}
