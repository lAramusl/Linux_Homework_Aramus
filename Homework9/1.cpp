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
  const int shm_size = 4096;

  int shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, 0666);
  if (shm_fd == -1)
  {
    std::perror("Prog 1 : Shared memory creation");
    exit(errno);
  }
  if (ftruncate(shm_fd, shm_size) == -1) {
    std::perror("Prog 1 : Truncating");
    exit(errno);
  }
  if(close(shm_fd) == -1)
  {
    std::perror("Prog 1 : close");
    exit(errno);
  }

  return 0;
}

