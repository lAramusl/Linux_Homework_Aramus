#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <vector>
#include <string>
#include <sstream>
#include <cerrno>
#include <sys/wait.h>

int main()
{
  std::cout << "Enter Your Command :" << std::endl;
  std::string str;
  std::stringstream ss;
  std::getline(std::cin,str);
  ss << str;
  str = {};
  std::vector<std::string> args;
  std::string symb;
  std::string file_name;
  while(ss >> str)
    {
      if(str == ">>" || str == ">")
      {
        symb = str;
        break;
      }
      args.push_back(str);
    }
  ss >> file_name;
  char* argv[args.size()+1];
  for(std::size_t i = 0; i < args.size();++i )
    {
      argv[i] = const_cast<char*>(args[i].data());
    }
  argv[args.size()] = NULL;
  pid_t cpid = fork();
  if(cpid == -1)
  {
    std::perror("fork");
    exit(EXIT_FAILURE);
  }
  int fd = 0;
  int dupfd = 0;
  if(cpid == 0)
  {
    if(!file_name.empty())
    {
      if(symb == ">")
      {
        fd = open(file_name.data(),O_TRUNC|O_WRONLY|O_CREAT,0666);
        if(fd == -1)
        {
          std::perror("open");
          exit(EXIT_FAILURE);
        }
      }
      else if (symb == ">>")
      {
        fd = open(file_name.data(),O_APPEND|O_WRONLY|O_CREAT,0666);
        if(fd == -1)
        {
          std::perror("open");
          exit(EXIT_FAILURE);
        }
      }
    }
    if(fd != 0)
    {
      dupfd = dup2(fd,1);
      if(dupfd == -1)
      {
        std::perror("dup2");
        exit(EXIT_FAILURE);
      }
    }
    int exec = execvp(argv[0],argv);
    if(exec == -1)
    {
      std::perror("exec");
      exit(EXIT_FAILURE);
    }
    if(dupfd != 0)
    {
      close(dupfd);
    }
  }
  else
  {
    int wstatus = 0;
    pid_t cwait = wait(&wstatus);
    if(cwait == -1)
    {
      std::perror("wait");
      exit(EXIT_FAILURE);
    }
  }
}
