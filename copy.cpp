#include <iostream>
#include <fcntl.h>
#include <vector>
#include <cstdio>
#include <unistd.h>

int main(int argc, char**argv)
{
	const int buffsize = 8192;
	if(argc != 3)
	{
	std::cout << "invalid arguments\n";
	exit(EXIT_FAILURE);
	}
   int open_id = open(argv[1],O_RDONLY);
   if(open_id == -1)
   {
	  std::perror("open");
	   exit(EXIT_FAILURE);
   }
   int write_id = open(argv[2],O_WRONLY|O_CREAT|O_TRUNC, 0666);
   if(write_id == -1)
   {
	std::perror("write");
	exit(EXIT_FAILURE);
   }
   std::vector<char> buff(buffsize,0);
   int readBytes = read(open_id,buff.data(),buffsize);
   int writeBytes = 0;
   while(0 != readBytes)
   {
	writeBytes = write(write_id,buff.data(),buffsize);
	if(writeBytes == -1)
	{
		std::perror("write");
		exit(EXIT_FAILURE);
	}
	readBytes = read(open_id,buff.data(),buffsize);
	if(readBytes == -1)
	{
		std::perror("read");
		exit(EXIT_FAILURE);
	}
   }
   close(open_id);
   close(write_id);
	return 0;
}
