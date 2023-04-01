#include "point.test.cpp"

int main()
{
	bool generale = true;

	generale = generale && point_test();

	if (generale)
		std::cerr << "\033[1;32m" << "TUTTO OK!" << "\033[0m\n";
	else
		std::cerr << "\033[1;31m" << "ALCUNI TEST SONO FALLITI" << "\033[0m\n";
	return 0;
}
