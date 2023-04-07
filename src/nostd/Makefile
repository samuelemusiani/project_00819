all: main.o vector.o
	g++ main.o vector.o -o vector

main.o: main.cpp
	g++ -c main.cpp

vector.o: vector.cpp vector.hpp
	g++ -c vector.cpp

clean:
	rm -rf *.o
