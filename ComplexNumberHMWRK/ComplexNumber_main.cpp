#include <iostream>
#include "ComplexNumber.h"

int main()
{
	ComplexNumber a(0 , 0);
	ComplexNumber b(1.0, 0);
	ComplexNumber c(0, 5);
	ComplexNumber d = c + b;
	ComplexNumber e = d - (b * 5);
	std::cout << a << ' ' << b << ' ' << c << ' ' << d << ' ' << e;
	return 0;
}

