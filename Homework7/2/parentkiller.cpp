#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <cerrno>
#include <signal.h>
#include <sys/wait.h>

int main()
{
	pid_t cpid = fork();
	if(cpid == -1)
	{
		std::perror("fork");
		exit(errno);
	}
	if(cpid == 0)
	{
		pid_t ppid = getppid();
		std::cout << "C: i am trying to kill\n"; 
		int kil = kill(ppid,SIGKILL);
		if(kil == -1)
		{
			std::perror("C: i've failed to kill");
			exit(errno);
		}
	}
	else
	{
		std::cout << "P: i am alive\n";
		int wstatus = 0;
		int x = wait(&wstatus);
		if(x == -1)
		{
			std::perror("wait");
			exit(errno);
		}
	}
	return 0;
}
