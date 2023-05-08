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
        static int generateEnemyType(Seed seed,int chunk,int num);
		static int generateCoinType(Seed seed,int chunk,int num);
		static phy::Point generateEnemyPosition(Map map,int chunk,nostd::vector<phy::Point> entityPos);
		static phy::Point generateCoinPosition(Map map,int chunk,nostd::vector<phy::Point> entityPos);
		static bool is_there_an_entity(nostd::vector<phy::Point> entityPos,phy::Point pos);
};
#endif
