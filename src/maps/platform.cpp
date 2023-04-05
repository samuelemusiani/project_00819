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


phy::Point Platform::get_position()
{
    return this->position;
}

int Platform::get_length()
{
    return this->length;
}
