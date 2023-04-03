#include "../../../point.hpp"
#include "../../../vector.hpp"
#include "../../../body.hpp"
#include "../test.hpp"
#include <math.h>

bool BODY_TEST = true;

void body_test_1()
{
	CERR_YELLOW("body_test_1");

	phy::Body b = phy::Body(phy::Point(0, 0), phy::Vector(0, 0), phy::Vector(0, 0));
	TEST(0, b.get_position().get_xPosition(), BODY_TEST);
	TEST(0, b.get_position().get_yPosition(), BODY_TEST);
	TEST(0, b.get_velocity().get_xComponent(), BODY_TEST);
	TEST(0, b.get_velocity().get_yComponent(), BODY_TEST);
	TEST(0, b.get_acceleration().get_xComponent(), BODY_TEST);
	TEST(0, b.get_acceleration().get_yComponent(), BODY_TEST);

	b = phy::Body(phy::Point(-4, 100), phy::Vector(55, -180), phy::Vector(60, 95));
	TEST(-4, b.get_position().get_xPosition(), BODY_TEST);
	TEST(100, b.get_position().get_yPosition(), BODY_TEST);
	TEST_APPROX(abs(-55 - b.get_velocity().get_xComponent()) < 2, BODY_TEST);
	TEST_APPROX(abs(0 - b.get_velocity().get_yComponent()) < 2, BODY_TEST);
	TEST_APPROX(abs(-5 - b.get_acceleration().get_xComponent()) < 2, BODY_TEST);
	TEST_APPROX(abs(60 - b.get_acceleration().get_yComponent()) < 2, BODY_TEST);

}

void body_test_2()
{
	CERR_YELLOW("body_test_2");

	phy::Body b;

	b.set_position(phy::Point(5, 7));
	b.set_velocity(phy::Vector(1, 45));
	b.set_acceleration(phy::Vector(10, -90));

	TEST(5, b.get_position().get_xPosition(), BODY_TEST);
	TEST(7, b.get_position().get_yPosition(), BODY_TEST);
	TEST_APPROX(abs(1 - b.get_velocity().get_xComponent()) < 2, BODY_TEST);
	TEST_APPROX(abs(1 - b.get_velocity().get_yComponent()) < 2, BODY_TEST);
	TEST_APPROX(abs(0 - b.get_acceleration().get_xComponent()) < 2, BODY_TEST);
	TEST_APPROX(abs(-10 - b.get_acceleration().get_yComponent()) < 2, BODY_TEST);

}

void body_test_3()
{
	CERR_YELLOW("body_test_3");

	phy::Body b;

	/* TEST 1 */

	b.set_position(phy::Point(0, 0));
	b.set_velocity(phy::Vector(1, 0));
	b.set_acceleration(phy::Vector(0, 0));

	b.update(1);

	TEST(1, b.get_position().get_xPosition(), BODY_TEST);
	TEST(0, b.get_position().get_yPosition(), BODY_TEST);
	TEST(1, b.get_velocity().get_xComponent(), BODY_TEST);
	TEST(0, b.get_velocity().get_yComponent(), BODY_TEST);
	TEST(0, b.get_acceleration().get_xComponent(), BODY_TEST);
	TEST(0, b.get_acceleration().get_yComponent(), BODY_TEST);

	b.update(10);

	TEST(11, b.get_position().get_xPosition(), BODY_TEST);
	TEST(0, b.get_position().get_yPosition(), BODY_TEST);
	TEST(1, b.get_velocity().get_xComponent(), BODY_TEST);
	TEST(0, b.get_velocity().get_yComponent(), BODY_TEST);
	TEST(0, b.get_acceleration().get_xComponent(), BODY_TEST);
	TEST(0, b.get_acceleration().get_yComponent(), BODY_TEST);

	/* TEST 2 */

	b.set_position(phy::Point(5, 100));
	b.set_velocity(phy::Vector(1, 0));
	b.set_acceleration(phy::Vector(10, -90));

	b.update(1);

	TEST(6, b.get_position().get_xPosition(), BODY_TEST);
	TEST(95, b.get_position().get_yPosition(), BODY_TEST);
	TEST(1, b.get_velocity().get_xComponent(), BODY_TEST);
	TEST(-10, b.get_velocity().get_yComponent(), BODY_TEST);
	TEST(0, b.get_acceleration().get_xComponent(), BODY_TEST);
	TEST(-10, b.get_acceleration().get_yComponent(), BODY_TEST);

	b.update(1);

	TEST(7, b.get_position().get_xPosition(), BODY_TEST);
	TEST(80, b.get_position().get_yPosition(), BODY_TEST);
	TEST(1, b.get_velocity().get_xComponent(), BODY_TEST);
	TEST(-20, b.get_velocity().get_yComponent(), BODY_TEST);
	TEST(0, b.get_acceleration().get_xComponent(), BODY_TEST);
	TEST(-10, b.get_acceleration().get_yComponent(), BODY_TEST);


	b.update(5);

	TEST(12, b.get_position().get_xPosition(), BODY_TEST);
	TEST(-145, b.get_position().get_yPosition(), BODY_TEST);
	TEST(1, b.get_velocity().get_xComponent(), BODY_TEST);
	TEST(-70, b.get_velocity().get_yComponent(), BODY_TEST);
	TEST(0, b.get_acceleration().get_xComponent(), BODY_TEST);
	TEST(-10, b.get_acceleration().get_yComponent(), BODY_TEST);

	/* TEST 3 */

	b.set_position(phy::Point(3, 0));
	b.set_velocity(phy::Vector(10, 60));
	b.set_acceleration(phy::Vector(10, -90));
	b.update(7);

	TEST(38, b.get_position().get_xPosition(), BODY_TEST);
	TEST_APPROX(abs(-184 - b.get_position().get_yPosition()) < 3, BODY_TEST);
	TEST_APPROX(abs(5 - b.get_velocity().get_xComponent()) < 2, BODY_TEST);
	TEST_APPROX(abs(-61 - b.get_velocity().get_yComponent()) < 2, BODY_TEST);
	TEST(0, b.get_acceleration().get_xComponent(), BODY_TEST);
	TEST(-10, b.get_acceleration().get_yComponent(), BODY_TEST);
}

bool body_test()
{
	body_test_1();
	body_test_2();
	body_test_3();
	return BODY_TEST;
}
