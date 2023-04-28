/*
* Alma Mater Studiorum - University of Bologna
* First cycle degree in Computer Science
* Computer Programming - 00819
*
* Author: Peronese Lorenzo #0001081726
*
* seed.cpp: Implementation of the Seed class
*/

#include "seed.hpp"

Seed::Seed()
{

}

int Seed::getSeed()
{
	return this->seed;
}

void Seed::setSeed(int seed)
{
	this->seed=seed;
}
