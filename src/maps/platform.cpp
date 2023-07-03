/*
* Alma Mater Studiorum - University of Bologna
* First cycle degree in Computer Science
* Computer Programming - 00819
*
* Author: Peronese Lorenzo #0001081726
*
* platform.cpp: Implementation of the Platform class
*/

#include "platform.hpp"

Platform::Platform() : Platform(phy::Point(0,0),0)
{

}

Platform::Platform(phy::Point pos, int len)
{
    this->set_position(pos);
    this->set_length(len);
}

void Platform::set_position(phy::Point x)
{
    this->position = x;
}

void Platform::set_length(int len)
{
    this->length = len;
}


phy::Point Platform::get_position() const {
    return this->position;
}

int Platform::get_length() const
{
    return this->length;
}
