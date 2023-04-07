#include <iostream>
#include <cstring>
#include "vector.hpp"

#define deb(x) std::cerr << #x << ": " << (x) << std::endl;

int main()
{
	std::cout << "Hello world\n";
	nostd::vector v = nostd::vector(100);
	for (int i = 0; i < 100; i++)
	{
		v.push_back(i);
		deb(v.size());
		deb(v.capacity());
	}


	for (int i = 0; i < v.size(); i++)
		std::cout << v.at(i) << " ";
	// v.print();
	return 0;
}
