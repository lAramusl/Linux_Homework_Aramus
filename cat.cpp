#include <iostream>
#include <fcntl.h>
#include <vector>
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
	   std::cout << "unable to open file " << argv[1] << '\n';
	   exit(EXIT_FAILURE);
   }
   std::vector<char> buf(buffsize,0);
   int readBytes = read(open_id,buf.data(),buffsize);
   while(0 != readBytes)
   {
	for(std::size_t i = 0; i < readBytes;++i)
	{
		std::cout << buf[i];
	}
	readBytes = read(open_id,buf.data(),buffsize);
   }
   close(open_id);
	return 0;
}
