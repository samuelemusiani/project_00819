/*
* Alma Mater Studiorum - University of Bologna
* First cycle degree in Computer Science
* Computer Programming - 00819
*
* Author: Peronese Lorenzo #0001081726
*
* random.hpp: class that generates random numbers for the map
*/

#include "seed.hpp"
#include "../maps/map.hpp"
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
        static int generateEntityType(int chunk);
		static phy::Point generateEnemyPosition(Map map,int chunk);
		static phy::Point generateCoinPosition(Map map,int chunk);
};
#endif
