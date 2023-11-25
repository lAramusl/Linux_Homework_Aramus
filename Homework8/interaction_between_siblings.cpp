#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <array>
#include <sys/types.h>
#include <vector>
#include <string>
#include <sys/wait.h>

int main() 
{
  const int buffsize = 4096;
  int pipe1[2];
  int pipe2[2];
  
  if(pipe(pipe1) == -1)
  {
    std::perror("pipe1");
    exit(errno);
  }
  if(pipe(pipe2) == -1)
  {
    std::perror("pipe2");
    exit(errno);
  }
  pid_t cpid = fork();
  if(cpid == -1)
  {
    std::perror("1st fork ");
    exit(errno);
  }
  if(cpid == 0)
  {
    std::cout << '\n';
    close(pipe1[0]);
    close(pipe2[1]);
    std::string my_pid = std::to_string(getpid());
    int wr = write(pipe1[1],my_pid.c_str(),my_pid.size());
    if(wr == -1)
    {
      std::perror("child 1 write");
      exit(errno);
    }
    close(pipe1[1]);
    std::string my_broS_pid(buffsize,{});
    int rd = read(pipe2[0],const_cast<char*>(my_broS_pid.c_str()),buffsize);
    if(rd == -1)
    {
      std::perror("child 1 read");
      exit(errno);
    }
    close(pipe2[0]);
    std::cout << " I am the 1st Child, my pid is "<< my_pid << " and my sibling's is "<< my_broS_pid << "\n"; 
    exit(0);
  }
  else
  {
    pid_t cpid2 = fork();
    if(cpid2 == -1)
      {
        std::perror("2nd fork ");
        exit(errno);
      }
    else if(cpid2 == 0)
    {
      std::cout << '\n';
      close(pipe2[0]);
      close(pipe1[1]);
      std::string my_pid = std::to_string(getpid());
      int wr = write(pipe2[1],my_pid.c_str(),my_pid.size());
      if(wr == -1)
      {
        std::perror("child 2 write");
        exit(errno);
      }
      close(pipe2[1]);
      std::string my_broS_pid(buffsize,{});
      int rd = read(pipe1[0],const_cast<char*>(my_broS_pid.c_str()),buffsize);
      if(rd == -1)
      {
        std::perror("child 2 read");
        exit(errno);
      }
      close(pipe1[0]);
      std::cout << " I am the 2nd Child, my pid is "<< my_pid << " and my sibling's is "<< my_broS_pid << '\n'; 
      exit(0);
    }
    else
    {
      if(waitpid(cpid,NULL,0) == -1)
      {
        std::perror("wait child 1");
        exit(errno);
      }
      if(waitpid(cpid2,NULL,0) == -1)
      {
        std::perror("wait child 2");
        exit(errno);
      }
    }
  }
  return 0;
}
