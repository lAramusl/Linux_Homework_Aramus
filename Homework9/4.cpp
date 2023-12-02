#include <cerrno>
#include <cstdlib>
#include <fcntl.h>
#include <iostream>
#include <string>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sstream>

int main(int argc, char** argv) 
{
  if(argc != 2)
  {
    throw std::runtime_error("Invalid Arguments");
    exit(EXIT_FAILURE);
  }

  int n = std::stoi(std::string(argv[1]));
  
  const char *shm_name = "/Karobka";
  const int shm_size = 4096;

  int shm_fd = shm_open(shm_name, O_RDWR , 0666);
  if (shm_fd == -1)
  {
    std::perror("Prog 4 : Shared memory open");
    exit(errno);
  }

  void* ptr = mmap(0, shm_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
  if(ptr == MAP_FAILED)
  {
    std::perror("Prog 4 : Mapping");
    exit(errno);
  }

  std::string input(static_cast<const char*>(ptr));
  std::stringstream ss;
  ss << input;
  int x;
  while(ss >> x)
    {
      if(n == x)
      {
        std::cout << "Yes" << '\n';
        break;
      }
    }
  if(n != x)
  {
    std::cout << "No" << '\n';
  }

  if(munmap(ptr, shm_size) == -1)
  {
    std::perror("Prog 4 : Unmapping");
    exit(errno);
  }

  if(close(shm_fd) == -1)
  {
    std::perror("Prog 4 : Shared memory close");
    exit(errno);
  }

  return 0;
}

