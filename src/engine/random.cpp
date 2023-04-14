#include "random.hpp"

Random::Random()
{

}

void Random::seedSrand(Seed seed, int offset)
{
	srand(seed.getSeed()*offset);
}

int Random::generateEnemies(Seed seed) {
	seedSrand(seed);
	return (2 + rand() % 3);
}

int Random::generateCoins(Seed seed) {
	seedSrand(seed);
	return (3 + rand() % 4);
}

int Random::generateChunk(Seed seed) {
	seedSrand(seed);
	return (rand() % 20);
}
