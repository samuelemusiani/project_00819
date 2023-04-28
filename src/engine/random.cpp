/*
* Alma Mater Studiorum - University of Bologna
* First cycle degree in Computer Science
* Computer Programming - 00819
*
* Author: Peronese Lorenzo #0001081726
*
* random.cpp: Implementation of the Random class
*/

#include "random.hpp"

Random::Random()
{

}

void Random::seedSrand(Seed seed, int chunk, int offset)
{
	srand(seed.getSeed() + chunk * offset);
}

int Random::generateEnemies(Seed seed, int chunk) {
	seedSrand(seed, chunk, 13);
	return (2 + rand() % 3); // enemies range: 2-4
}

int Random::generateCoins(Seed seed, int chunk) {
	seedSrand(seed, chunk, 17);
	return (3 + rand() % 4); // coins range: 3-6
}

int Random::generateChunk(Seed seed, int chunk) {
	if(chunk == 0)
	{
		seedSrand(seed, chunk);
		return (rand() % 2);
	}
	else
	{
		int previous = generateChunk(seed,chunk-1);
		seedSrand(seed,chunk);
		int random = rand() % 2;
		if(random == previous)
			return (random + 1) % 2;
		else
			return random;
	}
}
