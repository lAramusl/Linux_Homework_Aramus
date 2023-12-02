all: compile run clear

compile: 1.cpp 2.cpp 3.cpp 4.cpp
	g++ 1.cpp -o shm_creation
	g++ 2.cpp -o shm_destruction
	g++ 3.cpp -o array_creation
	g++ 4.cpp -o number_checking

run:
	touch answer.txt
	./shm_creation
	./array_creation
	./number_checking $(N) >> answer.txt
	./shm_destruction
	cat answer.txt

clear:
	rm answer.txt
	rm shm_creation
	rm shm_destruction
	rm array_creation
	rm number_checking
