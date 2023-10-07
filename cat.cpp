#include <iostream>
#include <fcntl.h>
#include <vector>
#include <errno.h>
#include <unistd.h>

int main(int argc, char**argv)
{
	const int buffsize = 8192;
	if(argc != 2)
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
   std::vector<char> buf(buffsize,0);
   int readBytes = read(open_id,buf.data(),buffsize);
   int writecode = 0;
   while(0 != readBytes)
   {
	writecode = write(STDOUT_FILENO, buf.data(), readBytes);
	if(writecode == -1)
	{
	      std::perror("write");
	      exit(EXIT_FAILURE);	
	}
	readBytes = read(open_id,buf.data(),buffsize);
   }
   close(open_id);
	return 0;
}
