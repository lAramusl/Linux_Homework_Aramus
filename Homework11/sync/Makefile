all: main 

main: sync_mutex.cpp sync_sem.cpp sync_spin.cpp
	g++ sync_mutex.cpp -o mutex -pthread -std=c++20
	g++ sync_sem.cpp -o sem -pthread -std=c++20
	g++ sync_spin.cpp -o spin -pthread -std=c++20


