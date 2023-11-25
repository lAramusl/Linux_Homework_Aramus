#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <array>
#include <sys/types.h>
#include <vector>
#include <string>
#include <sys/wait.h>
#include <sstream>

int main(int argc, char** argv)
{
  if(argc != 1)
  {
    std::cout << "Not through the arguments, please\n";
    exit(0);
  }
  std::string cmd;

  std::cout << "Enter the commands : ";
  std::getline(std::cin,cmd);
  std::stringstream ss;
  std::vector<std::string> lhs_tmp;
  std::vector<std::string> rhs_tmp;
  bool left_from_the_pipe = true;
  ss << cmd;
  while(ss >> cmd)
    {
      if(cmd == "|")
      {
        left_from_the_pipe = false;
        continue;
      }
      if(left_from_the_pipe)
      {
        lhs_tmp.push_back(cmd);
      }
      else
      {
        rhs_tmp.push_back(cmd);
      }
    }

  char* lhs [lhs_tmp.size()+1];
  for(std::size_t i = 0; i < lhs_tmp.size();++i)
    {
      lhs[i] = const_cast<char*>(lhs_tmp[i].c_str());
    }
  lhs[lhs_tmp.size()] = nullptr;

  char* rhs [rhs_tmp.size()+1];
  for(std::size_t i = 0; i < rhs_tmp.size(); ++i)
    {
      rhs[i] = const_cast<char*>(rhs_tmp[i].c_str());
    }
  rhs[rhs_tmp.size()] = nullptr;
  
  int pipefd[2];
  if(pipe(pipefd) == -1)
  {
    std::perror("truba");
    exit(errno);
  }

  pid_t cpid = fork();
  if(cpid == -1)
  {
    std::perror("fork 1 ");
    exit(errno);
  }
  
  if(cpid == 0)
  {
    if (dup2(pipefd[1], STDOUT_FILENO) == -1)
      {
          std::perror("dup2 : stdOUT and pipe_in");
          exit(errno);
      }
      close(pipefd[0]);
      close(pipefd[1]);
      execvp(lhs[0], lhs);
  }

  if(waitpid(cpid,nullptr,0) == -1)
  {
    std::perror("wait child 1 ");
    exit(errno);
  }
  
  pid_t cpid2 = fork();
  
  if(cpid2 == -1)
  {
    std::perror("fork 2 ");
    exit(errno);
  }
  if(cpid2 == 0)
  {  
      if(dup2(pipefd[0],STDIN_FILENO) == -1)
      {
        std::perror("dup2 : stdIN and pipe_out");
        exit(errno);
      }
      close(pipefd[1]);
      close(pipefd[0]);
      execvp(rhs[0],rhs);
  }
  close(pipefd[0]);
  close(pipefd[1]);

  if(waitpid(cpid2,nullptr,0) == -1)
  {
    std::perror("wait child 2 ");
    exit(errno);
  }
}
