#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cerrno>
#include <vector>
#include <algorithm>
#include <string>

int main(int argc, char** argv)
{
	const int buffsize = 4096;
	int fd = open(argv[1],O_RDONLY);
	if(fd == -1)
	{
		std::perror("1st open");
		exit(EXIT_FAILURE);
	}
	std::vector<char> buff(buffsize,0);
	std::vector<std::string> lines;
	int read_id = 1;
	std::string temp;
	while(read_id != 0)
	{
		read_id = read(fd,buff.data(),buffsize);
		if(read_id == -1)
		{
			std::perror("1st read");
			exit(EXIT_FAILURE);
		}
		for(std::size_t i = 0; i < buff.size();++i)
		{
			temp.push_back(buff[i]);
			if(buff[i] == '\n')
			{
				lines.push_back(temp);
				temp = {};
			}
		}
		buff = {};
	}
	std::cout << lines.size() << std::endl;
	for(std::size_t i = 0; i < lines.size(); ++i)
	{
		std::reverse(lines[i].begin(),lines[i].end());
	}
	std::reverse(lines.begin(),lines.end());
	int write_fd = open("output.txt",O_WRONLY|O_TRUNC|O_CREAT,0666);
	if(write_fd == -1)
	{
		std::perror("2nd open");
		exit(EXIT_FAILURE);
	}
	int writecode = 0;
	for(std::size_t i = 0; i < lines.size();++i)
	{
		writecode = write(write_fd,lines[i].data(),lines[i].size());
		if(writecode == -1)
		{
			std::perror("write");
			exit(EXIT_FAILURE);
		}
	}
	close(write_fd);
	close(fd);
}
