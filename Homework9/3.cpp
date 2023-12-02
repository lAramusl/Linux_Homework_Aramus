#include <cerrno>
#include <cstdlib>
#include <fcntl.h>
#include <iostream>
#include <string>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <vector>

std::vector<int> reshetoDelat()
{
  std::vector<bool> vec(4096,true);
  std::vector<int> primes;
  primes.reserve(10);
  for(std::size_t i = 2; i < vec.size() ; ++i)
    {
      if(vec[i] == true)
      {
        primes.push_back(i);
        for(std::size_t j = i*i ; j < vec.size(); j += i)
          {
            vec[j] = false;
          }
      }
    }
  return primes;
}

int main() {
  const char *shm_name = "/Karobka";
  const int shm_size = 4096;

  int shm_fd = shm_open(shm_name, O_RDWR , 0666);
  if (shm_fd == -1)
  {
    std::perror("Prog 3 : Shared memory open");
    exit(errno);
  }

  std::vector<int> primes = reshetoDelat();

  void* ptr = mmap(0, shm_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
  if(ptr == MAP_FAILED)
  {
    std::perror("Prog 3 : Mapping");
    exit(errno);
  }

  std::string primes_str{};
  for(auto x : primes)
    primes_str += std::to_string(x) + " ";
  
  std::copy(primes_str.begin(), primes_str.end(), static_cast<char*>(ptr));

  if(munmap(ptr, shm_size) == -1)
  {
    std::perror("Prog 3 : Unmapping");
    exit(errno);
  }

  if(close(shm_fd) == -1)
  {
    std::perror("Prog 3 : Shared memory close");
    exit(errno);
  }

  return 0;
}

