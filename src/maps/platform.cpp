#include "platform.hpp"

Platform::Platform() : Platform(0, 0, 0)
{

}

Platform::Platform(int x, int y, int len)
{
    this->set_xPosition(x);
    this->set_yPosition(y);
    this->set_length(len);
}

void Platform::set_xPosition(int x)
{
    this->x_pos = x;
}

void Platform::set_yPosition(int y)
{
    this->y_pos = y;
}

void Platform::set_length(int len)
{
    this->length = len;
}


int Platform::get_xPosition()
{
    return this->x_pos;
}

int Platform::get_yPosition()
{
    return this->y_pos;
}

int Platform::get_length()
{
    return this->length;
}
