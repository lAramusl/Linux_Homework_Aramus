#include <iostream>
#include <vector>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <semaphore.h>
#include <chrono>
#include <iomanip>

class Number {
private:
  sem_t* semaphore;
public:
  int x = 0;
  Number() : semaphore(sem_open("/semaphore", O_CREAT | O_RDWR, 0600, 1))
  {}

  void inc() {
      sem_wait(semaphore);

      x++;

      sem_post(semaphore);
  }
  ~Number() {
      sem_close(semaphore);
      sem_unlink("/semaphore");
  }
};

void* example(void* arg) {
  Number* num = (Number*)arg;
  for (int i = 0; i < 10000; ++i) {
    num->inc();
  }
  return nullptr;
}

int main(int argc, char** argv) {
  auto start = std::chrono::high_resolution_clock::now();
  std::cout << "semaphore\n";
  Number* num = new Number();
  num->x = 2;
  std::vector<pthread_t> tids(20);
  std::ios_base::sync_with_stdio(0);
  
  for (int i = 0; i < 20; ++i) {
    pthread_create(&tids[i], NULL, example, (void*)num);  
  }

  for (int i = 0; i < 20; ++i) {
    pthread_join(tids[i], NULL);
  }
  std::cout << num->x << std::endl;
  delete num;
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = duration_cast<std::chrono::milliseconds>(end - start);
  std::cout << double(duration.count())/1000.0  <<" seconds"<< std::endl;
  return 0;
}
