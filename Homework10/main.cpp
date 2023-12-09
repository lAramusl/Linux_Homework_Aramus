#include <iostream>
#include <pthread.h>
#include <string>
#include <sstream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <cerrno>
#include <vector>
#include <iomanip>

struct thread_helper
{
  std::string input_data;
  std::size_t thread_number;
};

void* calculateAndWrite(void* arg)
{
  thread_helper* const input = (thread_helper*)arg;
  
  std::stringstream ss;
  std::string filename = "out_";
  filename += std::to_string(input->thread_number);
  ss << input->input_data;
  long a = 0;
  long b = 0;
  long long ans = 0;
  std::string oper;
  ss >> a; ss >> b; ss >> oper;
  if(oper == "s")
  {
    ans = a + b;
  }
  else if(oper == "m")
  {
    ans = a * b;
  }
  else if(oper == "ss")
  {
    ans = (a*a) + (b*b);
  }
  std::string write_data;
  write_data += '"' + std::to_string(a) + ' ' + oper + ' ' + std::to_string(b);
  write_data += " = " + std::to_string(ans) + '"';
  int fd = open(filename.c_str(), O_CREAT|O_TRUNC|O_WRONLY, 0666);
  if(fd == -1)
  {
    std::perror("open");
    exit(errno);
  }
  if(write(fd,write_data.c_str(),write_data.size()) == -1)
  {
    std::perror("write");
    exit(errno);
  }
  if(close(fd) == -1)
  {
    std::perror("close");
    exit(errno);
  }

  
  delete input;

  
  return nullptr;
}

int main()
{
  std::size_t n = 0;
  std::cin >> n;
  
  std::vector<pthread_t> tids(n);
  std::vector<std::string> commands(n);
  std::vector<thread_helper*> helpers(n);
  std::string temp;
  
  for(std::size_t i = 0; i < n+1; ++i)
    {
      std::getline(std::cin, temp);
      if(i == 0)
      {
        continue;//senc em arel vortev sxal er inputy kardum
      }
      commands[i-1] = temp;
    }
  for(std::size_t j = 0; j < n; ++j)
  {
    helpers[j] = new thread_helper;
    helpers[j]->thread_number = j+1;
    helpers[j]->input_data = commands[j];
    pthread_create(&tids[j], NULL , calculateAndWrite, (void*)helpers[j]);
  }

  for(std::size_t i = 0; i < n; ++i)
  {
    pthread_join(tids[i],NULL);
  }
  
  return 0;

}
