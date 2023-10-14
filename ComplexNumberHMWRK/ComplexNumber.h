#ifndef ARAMUS_COMPLNUMBER
#define ARAMUS_COMPLNUMBER
#include <iostream>
#include <algorithm>

class ComplexNumber
{
public:
	double Re;
	double Im;

	ComplexNumber() = default;
	ComplexNumber(double re, double im);
	ComplexNumber(const std::pair<double, double>& num);
	ComplexNumber(const ComplexNumber& other) = default;
	ComplexNumber& operator=(const ComplexNumber& other) = default;
	~ComplexNumber() = default;

	friend std::ostream& operator<<(std::ostream& out, const ComplexNumber& num);
	friend ComplexNumber operator+(const ComplexNumber& num1, const ComplexNumber& num2);
	friend ComplexNumber operator-(const ComplexNumber& num1, const ComplexNumber& num2);
	friend ComplexNumber operator*(const ComplexNumber& num1, double k);

	double abs()const;


};
#endif
