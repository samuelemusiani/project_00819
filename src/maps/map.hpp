#include "chunk.hpp"
#include "../engine/random.hpp"
#include <chrono>

#ifndef MAPS_MAP
#define MAPS_MAP

#define NUM_MAPS 20

class Map
{
    private:
        Chunk possible_chunks[NUM_MAPS];
        void initialize_chunks();
		Seed seed;
    public:
        Map();
		Map(int seed);
        Chunk get_chunk(int n);
};

#endif
