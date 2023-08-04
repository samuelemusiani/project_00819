#include "coin.hpp"

Coin::Coin(phy::Point p) : Entity(p), collected(false) {}

void Coin::make_collected() { this->collected = true; }

bool Coin::is_collected() { return this->collected; }
