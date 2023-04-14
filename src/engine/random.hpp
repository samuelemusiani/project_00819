#include "seed.hpp"
#include <cstdlib>


#ifndef ENGINE_RANDOM
#define ENGINE_RANDOM

class Random {
	public:
		Random();
		static void seedSrand(Seed seed, int offset=1);
		static int generateEnemies(Seed seed);
		static int generateCoins(Seed seed);
		static int generateChunk(Seed seed);
};
#endif