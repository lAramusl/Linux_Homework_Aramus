#include "ComplexNumber.h"
#include <iostream>
#include <cmath>

ComplexNumber::ComplexNumber(double re, double im)
	: Re(re), Im(im) {}
ComplexNumber::ComplexNumber(const std::pair<double, double>& num)
	: ComplexNumber(num.first, num.second) {}

std::ostream& operator<<(std::ostream& out, const ComplexNumber& num)
{
	double imaginary = std::abs(num.Im);
	char sign = '+';
	if (num.Im == 0 && num.Re == 0)
		out << '0';
	if (num.Im < 0)
		sign = '-';
	if (num.Re != 0)
	{
		out << num.Re;
	}
	if (num.Im != 0)
	{
		out << sign << imaginary << 'i';
	}
	return out;
}

ComplexNumber operator+(const ComplexNumber& num1, const ComplexNumber& num2)
{
	return ComplexNumber(num1.Re + num2.Re, num1.Im + num2.Im);
}

ComplexNumber operator-(const ComplexNumber& num1, const ComplexNumber& num2)
{
	return ComplexNumber(num1.Re - num2.Re, num1.Im - num2.Im);
}

ComplexNumber operator*(const ComplexNumber& num1, double k)
{
	return ComplexNumber(k * num1.Re, k * num1.Im);
}

double ComplexNumber::abs(const ComplexNumber& num)
{
	return std::sqrt((num.Re * num.Re) + (num.Im * num.Im));
}

