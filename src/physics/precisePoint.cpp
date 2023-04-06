#include "precisePoint.hpp"
#include <math.h>

phy::PrecisePoint::PrecisePoint() : PrecisePoint(0, 0)
{

}

phy::PrecisePoint::PrecisePoint(double posX, double posY)
{
	this->set_xPosition(posX);
	this->set_yPosition(posY);
}

void phy::PrecisePoint::set_xPosition(double posX)
{
	this->posX = posX;
}

void phy::PrecisePoint::set_yPosition(double posY)
{
	this->posY = posY;
}

double phy::PrecisePoint::get_xPosition() 
{
	return this->posX;
}

double phy::PrecisePoint::get_yPosition()
{
	return this->posY;
}

phy::Point phy::PrecisePoint::toPoint()
{
	return phy::Point(round(this->get_xPosition()), round(this->get_yPosition()));
}
