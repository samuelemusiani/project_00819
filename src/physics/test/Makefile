all: point vector
	g++ main.cpp $(shell find object/*) -o TEST
	./TEST

point: ../point.cpp ../point.hpp tests/point.test.cpp DIR
	g++ -c ../point.cpp -o object/point.o
	g++ -c tests/point.test.cpp -o object/point.test.o

vector: ../vector.cpp ../vector.hpp tests/vector.test.cpp DIR
	g++ -c ../vector.cpp -o object/vector.o
	g++ -c tests/vector.test.cpp -o object/vector.test.o

DIR:
	mkdir -p object

clean:
	rm -rf object/*
