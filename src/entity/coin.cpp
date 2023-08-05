/*
 * Alma Mater Studiorum - University of Bologna
 * First cycle degree in Computer Science
 * Computer Programming - 00819
 *
 * Author: Ayache Omar #0001068895
 *
 * coin.cpp: Class that implements
 * a coin extending Entity
 */

#include "coin.hpp"

Coin::Coin(phy::Point p) : Entity(p), collected(false) {}

void Coin::make_collected() { this->collected = true; }

bool Coin::is_collected() { return this->collected; }
