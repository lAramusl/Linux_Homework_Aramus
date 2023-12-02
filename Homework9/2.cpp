#include <cerrno>
#include <cstdlib>
#include <fcntl.h>
#include <iostream>
#include <string>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
  const char *shm_name = "/Karobka";
  const int size = 4096;

  int shm_fd = shm_open(shm_name, O_RDWR , 0666);
  if (shm_fd == -1)
  {
    std::perror("Prog 2 : Shared memory open");
    exit(errno);
  }
  
  if (shm_unlink(shm_name) == -1) {
    std::perror("Prog 2 : Unlink");
    exit(errno);
  }

  if(close(shm_fd) == -1)
  {
    std::perror("Prog 2 : closefd");
    exit(errno);
  }

  return 0;
}

