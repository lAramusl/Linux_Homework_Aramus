#include <iostream>
#include "ComplexNumber.h"
#include <vector>
#include <algorithm>
#include <cstddef>
#include <string>
int main()
{
	std::size_t n = 0;
	std::cout << "Enter the amount of numbers to be written: ";
	std::cin >> n;
	std::vector<ComplexNumber> arr;
	std::cout << "Enter the numbers as a b : ";
	double a = 0;
	double b = 0;
	for(std::size_t i = 0;i < n; ++i)
	{
		std::cin >> a >> b;
		arr.push_back(std::make_pair(a,b));
	}
	std::sort(arr.begin(),arr.end(),[]
			(const ComplexNumber& n1,const ComplexNumber& n2)
			{return n1.abs() > n2.abs();});
	for(auto x : arr)
		std::cout << x << ' ';
	return 0;
}

