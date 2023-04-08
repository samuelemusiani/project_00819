#include "point.hpp"

phy::Point::Point() : Point(0, 0)
{

}

phy::Point::Point(int posX, int posY)
{
	this->set_xPosition(posX);
	this->set_yPosition(posY);
}

void phy::Point::set_xPosition(int posX)
{
	this->posX = posX;
}

void phy::Point::set_yPosition(int posY)
{
	this->posY = posY;
}

int phy::Point::get_xPosition() 
{
	return this->posX;
}

int phy::Point::get_yPosition()
{
	return this->posY;
}

bool phy::Point::operator ==(const phy::Point &p)
{
	return (posX == p.posX && posY == p.posY);
}

bool phy::Point::operator !=(const phy::Point &p)
{
	return !(posX == p.posX && posY == p.posY);
}

phy::Point phy::Point::operator +(const phy::Point &p)
{
	phy::Point tmp = phy::Point(posX + p.posX, posY + p.posY);
	return tmp;
}

phy::Point phy::Point::operator -(const phy::Point &p)
{
	phy::Point tmp = phy::Point(posX - p.posX, posY - p.posY);
	return tmp;
}
