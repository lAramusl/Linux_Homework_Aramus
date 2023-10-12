run: main
	./ComplexNumber

ComplexNumber_main.o: ComplexNumber_main.cpp
	g++ ComplexNumber_main.cpp -c

ComplexNumber.o: ComplexNumber.cpp ComplexNumber.h
	g++ ComplexNumber.cpp -c

main: ComplexNumber_main.o ComplexNumber.o
	g++ ComplexNumber_main.o ComplexNumber.o -o ComplexNumber
