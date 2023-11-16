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
#include <queue>

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
    if(str == "exit")
    {
      break;
    }
    ss << str;
    std::vector<std::string> args;
    std::queue<std::vector<std::string>> comands_queue;
    std::queue<std::string> divider_queue;
    std::string tmp;
    while(ss >> tmp)//watch here
    {
      if(tmp == "||" || tmp == "&&" || tmp == ";")
      {
        comands_queue.push(args);
        divider_queue.push(tmp);
        args = {};
        continue;
      }
      args.push_back(tmp);
    }
      comands_queue.push(args);
      bool lastIsSuccess = false;
      std::string divider;
      while(!(comands_queue.empty()))//and continue from here
      {
        if(lastIsSuccess && divider == "&&")
        {
          break;
        }
        else if(!lastIsSuccess && divider == "||")
        {
          break;
        }
        args = comands_queue.front();
        comands_queue.pop();
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
            if(args[i] == "||" || 
              args[i] == "&&" || 
              args[i] == ";")
            {
              divider = args[i];
              continue;
            }
            argv[i] = const_cast<char*>(args[i].data());
          }
          argv[args.size()] = NULL;
          int exec = execvp(argv[0],argv);
          lastIsSuccess = true;
          if(exec == -1)
          {
            lastIsSuccess = false;
            std::perror("execvp");
            exit(EXIT_FAILURE);
          }
        }
        else
        {	
          int wstatus = 0;
          pid_t waitCode = wait(&wstatus);
          if(waitCode == -1)
          {
            std::perror("wait");
            exit(EXIT_FAILURE);
          }
          if(!divider_queue.empty())
          {
            divider = divider_queue.front();
            divider_queue.pop();
          }
        }//fork else
      }//Commands
  }//shellIsRunning
  return 0;
}
