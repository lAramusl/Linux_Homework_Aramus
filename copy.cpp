#include <iostream>
#include <fcntl.h>
#include <vector>
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
	   std::cout << "unable to open file " << argv[1] << '\n';
	   exit(EXIT_FAILURE);
   }
   int write_id = open(argv[2],O_WRONLY|O_CREAT|O_TRUNC, S_IRWXO);
   if(write_id == -1)
   {
	std::cout << "unable to open/create file" << argv[2] << '\n';
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
		std::cout << "Error durring writing" << '\n';
		exit(EXIT_FAILURE);
	}
	readBytes = read(open_id,buff.data(),buffsize);
   }
   close(open_id);
   close(write_id);
	return 0;
}
