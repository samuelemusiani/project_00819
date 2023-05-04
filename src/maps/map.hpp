/*
* Alma Mater Studiorum - University of Bologna
* First cycle degree in Computer Science
* Computer Programming - 00819
*
* Author: Peronese Lorenzo #0001081726
*
* map.hpp: Class that initializes the map and everything related
*/

#include "chunk.hpp"
#include "../../etc/nostd/string.hpp"
#include "../engine/seed.hpp"
#include <chrono>
#include <ctime>
#include <string>

#ifndef MAPS_MAP
#define MAPS_MAP

#define NUM_MAPS 20

class Map
{
    private:
        Chunk possible_chunks[NUM_MAPS];
        void initialize_chunks();
		Seed seed;
		nostd::string coinsAndEnemies;
    public:
        Map();
		Map(int seed,nostd::string coinsAndEnemies);
        Chunk get_chunk(int n);
		int getCoins(int n);
		int getEnemies(int n);
		nostd::string getCoinsAndEnemies();
		Seed getSeed();
};

#endif
