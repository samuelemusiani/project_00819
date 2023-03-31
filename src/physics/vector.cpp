#include "vector.hpp"

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

	this->alpha = alpha;
}

double phy::Vector::get_magnitude()
{
	return this->magnitude;
}

int phy::Vector::get_direction()
{
	return this->alpha;
}
