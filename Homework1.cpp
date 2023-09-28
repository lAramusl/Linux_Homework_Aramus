#include <iostream>
#include <string>
#include <climits>

int main(int argc, char* argv[])
{
	int min = INT_MAX;
	int max = INT_MIN;
	for(int i = 1; i < argc; ++i)
	{
	   if(min > std::stoi(argv[i]))
		   min = std::stoi(argv[i]);
	   if(max < std::stoi(argv[i]))
		   max = std::stoi(argv[i]);
	}
	std::cout << "min-" << min << ' ' << "max-" << max << '\n';
	return 0;
}
