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
#include <chrono>
#include <ctime>
#include <string>

#ifndef MAPS_MAP
#define MAPS_MAP

#define NUM_MAPS 10

class Map
{
    private:
        Chunk possible_chunks[NUM_MAPS];
        void initialize_chunks();
		int seed;
    public:
        Map();
		Map(int seed);
        Chunk get_chunk(int n);
		int getCoins(int n);
		int getEnemies(int n);
		int getSeed();
};

#endif
