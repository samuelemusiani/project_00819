/*
* Alma Mater Studiorum - University of Bologna
* First cycle degree in Computer Science
* Computer Programming - 00819
*
* Author: Musiani Samuele #0001069143
*
* vector.test.cpp: All the tests for the phy::Vector class
*/

#include "../../../vector.hpp"
#include "../test.hpp"
#include <math.h>

bool VECTOR_TEST = true;

void vector_test_1()
{
	CERR_YELLOW("vector_test_1");
	
	phy::Vector v = phy::Vector();
	TEST(0, v.get_magnitude(), VECTOR_TEST);
	TEST(0, v.get_direction(), VECTOR_TEST);


	v = phy::Vector(127, 55);
	TEST(127, v.get_magnitude(), VECTOR_TEST);
	TEST(55, v.get_direction(), VECTOR_TEST);
}

void vector_test_2()
{
	CERR_YELLOW("vector_test_2");

	phy::Vector v = phy::Vector();

	v.set_magnitude(66);
	v.set_direction(180);
	TEST(66, v.get_magnitude(), VECTOR_TEST);
	TEST(180, v.get_direction(), VECTOR_TEST);


	v.set_direction(180);
	v.set_direction(181);
	v.set_direction(182);
	TEST(182, v.get_direction(), VECTOR_TEST);


	v.set_magnitude(66);
	v.set_magnitude(33);
	v.set_magnitude(277);
	TEST(277, v.get_magnitude(), VECTOR_TEST);

	v.set_direction(-180);
	TEST(180, v.get_direction(), VECTOR_TEST);

	v.set_direction(-3056);
	TEST(184, v.get_direction(), VECTOR_TEST);

	v.set_direction(3600);
	TEST(0, v.get_direction(), VECTOR_TEST);

	v.set_direction(1111);
	TEST(31, v.get_direction(), VECTOR_TEST);
}

void vector_test_3()
{

	CERR_YELLOW("vector_test_3");
	phy::Vector v1 = phy::Vector(0, 0);
	TEST(0, v1.get_xComponent(), VECTOR_TEST);
	TEST(0, v1.get_yComponent(), VECTOR_TEST);

	v1 = phy::Vector(0, 100);
	TEST(0, v1.get_xComponent(), VECTOR_TEST);
	TEST(0, v1.get_yComponent(), VECTOR_TEST);

	v1.set_magnitude(3);
	v1.set_direction(90);
	TEST(0, v1.get_xComponent(), VECTOR_TEST);
	TEST(3, v1.get_yComponent(), VECTOR_TEST);


	v1.set_magnitude(7);
	v1.set_direction(-180);
	TEST(-7, v1.get_xComponent(), VECTOR_TEST);
	TEST(0, v1.get_yComponent(), VECTOR_TEST);


	v1.set_magnitude(10.44);
	v1.set_direction(107);
	TEST(-3, v1.get_xComponent(), VECTOR_TEST);
	TEST(10, v1.get_yComponent(), VECTOR_TEST);

	v1.set_magnitude(6.403);
	v1.set_direction(39);
	TEST(5, v1.get_xComponent(), VECTOR_TEST);
	TEST(4, v1.get_yComponent(), VECTOR_TEST);
}

void vector_test_4()
{
	CERR_YELLOW("vector_test_4");

	phy::Vector v1 = phy::Vector(0, 0);
	phy::Vector v2 = phy::Vector(0, 0);
	phy::Vector v3;

	v3 = phy::Vector::sum(v1, v2);
	TEST(0, v3.get_magnitude(), VECTOR_TEST);
	TEST(0, v3.get_direction(), VECTOR_TEST);

	v1.set_magnitude(1);
	v2.set_magnitude(1);
	v3 = phy::Vector::sum(v1, v2);
	TEST(2, v3.get_magnitude(), VECTOR_TEST);
	TEST(0, v3.get_direction(), VECTOR_TEST);

	v1.set_direction(90);
	v2.set_direction(90);
	v3 = phy::Vector::sum(v1, v2);
	TEST(2, v3.get_magnitude(), VECTOR_TEST);
	TEST(90, v3.get_direction(), VECTOR_TEST);

	v1.set_direction(90);
	v2.set_direction(270);
	v3 = phy::Vector::sum(v1, v2);
	TEST_APPROX(abs(v3.get_magnitude()) < 0.3, VECTOR_TEST);
	//No need to check direction when vector is 0 in magnitude

	
	v1.set_magnitude(100);
	v2.set_magnitude(100);
	v1.set_direction(0);
	v2.set_direction(180);
	v3 = phy::Vector::sum(v1, v2);
	TEST_APPROX(abs(v3.get_magnitude()) < 0.3, VECTOR_TEST);
	//No need to check direction when vector is 0 in magnitude


	v1.set_magnitude(100);
	v2.set_magnitude(99);
	v1.set_direction(0);
	v2.set_direction(180);
	v3 = phy::Vector::sum(v1, v2);
	TEST_APPROX(abs(1 - v3.get_magnitude()) < 0.3, VECTOR_TEST);
	TEST_APPROX(abs(1 - v3.get_direction()) < 5, VECTOR_TEST);

	v1 = phy::Vector(5, 60);
	v2 = phy::Vector(5, 0);
	v3 = phy::Vector::sum(v1, v2);
	TEST_APPROX(abs(8.66025 - v3.get_magnitude()) < 0.3, VECTOR_TEST);
	TEST_APPROX(abs(30 - v3.get_direction()) <= 5, VECTOR_TEST);


	v2 = phy::Vector(10, 177);
	v1 = phy::Vector(2.236, 153);
	v3 = phy::Vector::sum(v1, v2);
	TEST_APPROX(abs(12.07 - v3.get_magnitude()) < 0.3, VECTOR_TEST);
	TEST_APPROX(abs(172 - v3.get_direction()) <= 5, VECTOR_TEST);

}

void vector_test_5()
{
	CERR_YELLOW("vector_test_4");

	phy::Vector a = phy::Vector(10, 90);
	phy::Vector b = phy::Vector(10, 90);
	TEST(true, a == b, VECTOR_TEST);

	a.set_magnitude(20);
	TEST(false, a != b, VECTOR_TEST);

	phy::Vector c = a + b;
	TEST(true, c == phy::Vector(0, 0), VECTOR_TEST);

	a = phy::Vector(10, 177);
	b = phy::Vector(2.236, 153);
	c = a + b;
	TEST_APPROX(abs(12.07 - c.get_magnitude()) < 0.3, VECTOR_TEST);
	TEST_APPROX(abs(172 - c.get_direction()) <= 5, VECTOR_TEST);
}


bool vector_test()
{
	vector_test_1();
	vector_test_2();
	vector_test_3();
	vector_test_4();
	return VECTOR_TEST;
}
