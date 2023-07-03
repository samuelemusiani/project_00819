/*
* Alma Mater Studiorum - University of Bologna
* First cycle degree in Computer Science
* Computer Programming - 00819
*
* Author: Musiani Samuele #0001069143
*
* vector.cpp: Implementation of the phy::Vector class.
*/

#include "vector.hpp"
#include "constants.hpp"
#include <math.h>

phy::Vector::Vector() : Vector(0, 0)
{

}

phy::Vector::Vector(double magnitude) : Vector(magnitude, 0)
{

}

phy::Vector::Vector(double magnitude, int alpha) 
{
	this->set_magnitude(magnitude);
	this->set_direction(alpha);
}

void phy::Vector::set_magnitude(double magnitude)
{
	this->magnitude = magnitude;
}

void phy::Vector::set_direction(int alpha)
{

	while (alpha < 0) alpha += 360;

	this->alpha = alpha % 360;
}

double phy::Vector::get_magnitude()
{
	return this->magnitude;
}

int phy::Vector::get_direction()
{
	return this->alpha;
}

int phy::Vector::get_xComponent()
{
	return round(get_magnitude() * cos(phy::PI / 180 * get_direction()));
}

int phy::Vector::get_yComponent()
{
	return round(get_magnitude() * sin(phy::PI / 180 * get_direction()));
}

phy::Vector phy::Vector::sum(phy::Vector v1, phy::Vector v2)
{
	//https://math.stackexchange.com/questions/1365622/adding-two-polar-vectors
	phy::Vector v = phy::Vector();

	double mV1 = v1.get_magnitude();
	double mV2 = v2.get_magnitude();

	int aV1 = v1.get_direction();
	int aV2 = v2.get_direction();


	v.set_magnitude(sqrt(mV1 * mV1 + mV2 * mV2 + 2 * mV1 * mV2 * cos(phy::PI / 180 * (aV1 - aV2))));
	v.set_direction(round(aV1 + atan2(mV2 * sin(phy::PI / 180 * (aV2 - aV1)), mV1 + mV2 * cos(phy::PI / 180 * (aV2 - aV1))) * 180 / phy::PI));

	return v;
}

bool phy::Vector::operator ==(const phy::Vector &p)
{
	return (magnitude == p.magnitude && alpha == p.alpha);
}

bool phy::Vector::operator !=(const phy::Vector &p)
{
	return !(magnitude == p.magnitude && alpha == p.alpha);
}

phy::Vector phy::Vector::operator +(const phy::Vector &p)
{
	return sum(phy::Vector(magnitude, alpha), p);
}
