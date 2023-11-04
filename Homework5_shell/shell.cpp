#include <iostream>
#include <fcntl.h>
#include <string>
#include <vector>
#include <algorithm>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
#include <limits.h>
#include <cerrno>
#include <sstream>
#include <cstring>
#include <sys/wait.h>

int main() 
{
  char host[HOST_NAME_MAX];
  int host_name = gethostname(host,HOST_NAME_MAX);
  if(host_name == -1)
  {
    std::perror("host name");
    exit(EXIT_FAILURE);
  }
  char user[LOGIN_NAME_MAX];
  int user_name = getlogin_r(user,HOST_NAME_MAX);
  if(user_name == -1)
  {
    std::perror("host name");
    exit(EXIT_FAILURE);
  }
  bool shellIsRunning = true;
  std::string str;
  while(shellIsRunning)
  { 
    std::cout << "\033[0;32m" << user <<"@"<< host << "\033[0m" << ":\033[0;34m~\033[0m$ ";
    std::stringstream ss; 
    std::getline(std::cin,str);
    if(str == "close shell")
    {
	    break;
    }
    ss << str;
    std::vector<std::string> args;
    std::string cmd;
    std::string tmp;
    ss >> cmd;
    args.push_back(cmd);
    while(ss >> tmp)
    {
	 /*   if(tmp == "&&" || tmp == "||")
	    {
		cmd += " " + tmp;
		ss >> tmp;
		cmd += tmp;
	    }
	    else
	    {
		    args.push_back(tmp);
	    }*/
	    // es pordzum ei && u || ashxatacnei heto imaca vor petq chi
	    // alarum em jnjem ynenc vor comment em toxum)
	    args.push_back(tmp);
    }
    pid_t cpid = fork();
    if(cpid == -1)
    {
	    std::perror("fork");
	    exit(EXIT_FAILURE);
    }
    if(cpid == 0)
    {
	    char* argv[args.size()+1];
	    for(std::size_t i = 0; i < args.size();++i)
	    {
		    argv[i] = args[i].data();
	    }
	    argv[args.size()] = NULL;
	int exec = execvp(cmd.data(),argv);
	if(exec == -1)
	{
		std::perror("execvp");
		exit(EXIT_FAILURE);
	}
    }
    else
    {	
	    int wstatus = 0;
	    pid_t waitCode = wait(&wstatus); 
	    continue;
    }
  }
  return 0;
}
