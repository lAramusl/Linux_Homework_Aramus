#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <cerrno>
#include <signal.h>
#include <ucontext.h>

void signalHandler(int signo, siginfo_t* info, void* ucontextptr)
{
	if(signo == SIGUSR1)
	{

		pid_t pid = getpid();
		struct ucontext_t* context = static_cast<ucontext_t*>(ucontextptr);
		auto cont = context->uc_mcontext;
		std::cout << "RAX : "<< cont.gregs[REG_RAX] << std::endl;
		std::cout << "RBX : "<< cont.gregs[REG_RBX] << std::endl;
		std::cout << "RIP : "<< cont.gregs[REG_RIP] << std::endl;
		std::cout << "PID : "<< pid << std::endl;
			
	}
}

int main()
{
	struct sigaction act = {};
	act.sa_sigaction = signalHandler;
	if(sigaction(SIGUSR1,&act,nullptr) == -1)
	{
		std::perror("Signal handler SIGUSR1");
		exit(errno);
	}
	while(true)
	{
		std::cout << "running..." << std::endl;
		sleep(10);
	}
	return 0;


}
