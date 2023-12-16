#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <vector>
#include <string>
#include <cerrno>

struct BankAccount
{
private:
	long balance;
	pthread_mutex_t* mutex;
public:
	BankAccount(long amount)
	       	: balance(amount)
		, mutex(new pthread_mutex_t())
	{}

	void debit(long amount)
	{
		pthread_mutex_lock(mutex);
		balance -= amount;
		pthread_mutex_unlock(mutex);
	}

	void credit(long amount)
	{
		pthread_mutex_lock(mutex);
		balance += amount;
		pthread_mutex_unlock(mutex);
	}

	long getbalance()
	{
		return balance;
	}

	~BankAccount()
	{
		pthread_mutex_destroy(mutex);
		delete mutex;
	}
};

BankAccount bank(500);

void* debit(void* args)
{
  long diff = *(static_cast<long*>(args));
  bank.debit(diff);
  std::cout << "the amount after debit : " << bank.getbalance() << "\n";
  return nullptr;
}

void* credit(void* args)
{
  long diff = *(static_cast<long*>(args));
  bank.credit(diff);
  std::cout << "the amount after credit : " << bank.getbalance() << "\n";
  return nullptr;
}

int main()
{
	std::cout << "the amount before : " << bank.getbalance() << "\n";
	std::vector<pthread_t> tids(10);
	std::vector<long> difs(10);
	for(std::size_t i = 0; i < tids.size();++i)
	{
		difs[i] = i*10;
		if(i%3 == 0)
			pthread_create(&tids[i], NULL, debit , &difs[i]);
		else
			pthread_create(&tids[i], NULL, credit , &difs[i]); 
	}
	for(std::size_t i = 0; i < tids.size(); ++i)
	{
		if(pthread_join(tids[i],nullptr) != 0)
		{
			std::perror("join :");
			exit(errno);
		}
	}
	std::cout << "the amount after : " << bank.getbalance() << "\n";
	return 0;
}
