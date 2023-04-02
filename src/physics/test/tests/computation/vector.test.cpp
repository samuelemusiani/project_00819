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


	v1 = phy::Vector(2.236, 153);
	v2 = phy::Vector(10, 177);
	v3 = phy::Vector::sum(v1, v2);
	TEST_APPROX(abs(12.07 - v3.get_magnitude()) < 0.3, VECTOR_TEST);
	TEST_APPROX(abs(172 - v3.get_direction()) <= 5, VECTOR_TEST);

}

bool vector_test()
{
	vector_test_1();
	vector_test_2();
	vector_test_3();
	return VECTOR_TEST;
}
