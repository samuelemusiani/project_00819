#include "../point.hpp"
#include <iostream>

bool POINT_TEST = true;

#define TEST(X, Y) if((X) != (Y)) {std::cerr << "\033[1;31m" << "TEST FALLITO! RIGA: " << __LINE__ << "\033[0m\n" << "\n"; POINT_TEST = false;}

void point_test_1()
{
	phy::Point p = phy::Point();
	TEST(0, p.get_xPosition());
	TEST(0, p.get_yPosition());

	p = phy::Point(5, 7);
	TEST(5, p.get_xPosition());
	TEST(7, p.get_yPosition());
}

void point_test_2()
{
	phy::Point p = phy::Point(-3000, 100);
	TEST(-3000, p.get_xPosition());
	TEST(100, p.get_yPosition());

	p.set_xPosition(56);
	p.set_yPosition(10000);
	TEST(56, p.get_xPosition());
	TEST(10000, p.get_yPosition());


	p.set_yPosition(11);
	p.set_yPosition(-11);
	p.set_yPosition(123849);
	TEST(123849, p.get_yPosition());
}

bool point_test()
{
	point_test_1();
	point_test_2();
	return POINT_TEST;
}
