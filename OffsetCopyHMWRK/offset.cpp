#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cerrno>
#include <string>


int main()
{
	std::string source;
	std::string dest;
	unsigned int soffset = 0;
	unsigned int doffset = 0;
	unsigned int copySize = 0;
	constexpr int buffsize = 4096;

	std::cout << "Enter the name of the source file: ";
	std::cin >> source;
	std::cout << "Enter the name of the destination file: ";
	std::cin >> dest;
	std::cout << "Enter the initial offset in the soure file (in bytes): ";
	std::cin >> soffset;
	std::cout << "Enter the initial offset in the destination file (in bytes): ";
	std::cin >> doffset;
	std::cout << "Enter the number of bytes to copy: ";
	std::cin >> copySize;

	int fd_source = open(source.data(),O_RDONLY);
	if(fd_source == -1)
	{
		std::perror("open source");
		exit(EXIT_FAILURE);
	}
	off_t source_lseek = lseek(fd_source,soffset,SEEK_CUR);
	if(source_lseek == -1)
	{
		std::perror("lseek source");
		exit(EXIT_FAILURE);
	}
	int fd_dest = open(dest.data(),O_WRONLY|O_CREAT|O_TRUNC,0666);
	if(fd_dest == -1)
	{
		std::perror("open destination");
		exit(EXIT_FAILURE);
	}
	off_t dest_lseek = lseek(fd_dest,doffset,SEEK_CUR);
	if(dest_lseek == -1)
	{
		std::perror("lseek destination");
		exit(EXIT_FAILURE);
	}
	std::string buff(copySize,0);
	int source_read = read(fd_source,buff.data(),copySize);
	if(source_read == -1)
	{
		std::perror("source read");
		exit(EXIT_FAILURE);
	}
	int dest_write = write(fd_dest,buff.data(),copySize);
	if(dest_write == -1)
	{
		std::perror("destination write");
		exit(EXIT_FAILURE);
	}
	std::cout << "Successfully copied "<< dest_write << " bytes from the source file to the destination file.\n";
}
