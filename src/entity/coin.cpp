#include "coin.hpp"

Coin::Coin(const char* id, phy::Point p, int value)
    : Entity(id, p)
{
    this->value = value;
    this->collected = false;
}

Coin::Coin():Entity()
{
}

int Coin::get_value()
{
    return(this->value);
}

void Coin::make_collected()
{
    this->collected = true;
}

bool Coin::is_collected()
{
    return this->collected;
}
