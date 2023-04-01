#include "../../point.hpp"
#include "../test.hpp"

bool POINT_TEST = true;

void point_test_1()
{
	CERR_YELLOW("point_test_1");

	phy::Point p = phy::Point();
	TEST(0, p.get_xPosition(), POINT_TEST);
	TEST(0, p.get_yPosition(), POINT_TEST);

	p = phy::Point(5, 7);
	TEST(5, p.get_xPosition(), POINT_TEST);
	TEST(7, p.get_yPosition(), POINT_TEST);
	
}

void point_test_2()
{
	CERR_YELLOW("point_test_2");

	phy::Point p = phy::Point(-3000, 100);
	TEST(-3000, p.get_xPosition(), POINT_TEST);
	TEST(100, p.get_yPosition(), POINT_TEST);

	p.set_xPosition(56);
	p.set_yPosition(10000);
	TEST(56, p.get_xPosition(), POINT_TEST);
	TEST(10000, p.get_yPosition(), POINT_TEST);


	p.set_yPosition(11);
	p.set_yPosition(-11);
	p.set_yPosition(123849);
	TEST(123849, p.get_yPosition(), POINT_TEST);
}

bool point_test()
{
	point_test_1();
	point_test_2();
	return POINT_TEST;
}
