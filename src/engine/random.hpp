#include "seed.hpp"
#include <cstdlib>


#ifndef ENGINE_RANDOM
#define ENGINE_RANDOM

class Random {
	public:
		Random();
		static void seedSrand(Seed seed, int chunk, int offset=1);
		static int generateEnemies(Seed seed, int chunk);
		static int generateCoins(Seed seed, int chunk);
		static int generateChunk(Seed seed, int chunk);
};
#endif