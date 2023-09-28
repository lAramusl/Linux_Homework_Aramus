#include <iostream>

int main(int argv, char* argc[])
{
	for(int i = argv-1; i >= 1;--i)
		std::cout << argc[i] << ' ';
	std::cout << '\n';
	return 0;
}
