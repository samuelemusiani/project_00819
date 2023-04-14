#include "map.hpp"
// A chunk is 148x42

Map::Map()
{
	srand(time(nullptr));
	this->seed.setSeed(rand());
    initialize_chunks();
}

Map::Map(int seed)
{
	this->seed.setSeed(seed);
	initialize_chunks();
}

void Map::initialize_chunks()
{
    // 1st chunk
    this->possible_chunks[0].add_platform(phy::Point(46,3), 11);
    this->possible_chunks[0].add_platform(phy::Point(112,3), 15);
    this->possible_chunks[0].add_platform(phy::Point(21,8), 23);
    this->possible_chunks[0].add_platform(phy::Point(86,8), 21);
    this->possible_chunks[0].add_platform(phy::Point(130,8), 9);
    this->possible_chunks[0].add_platform(phy::Point(2,12), 11);
    this->possible_chunks[0].add_platform(phy::Point(110,14), 24);
    this->possible_chunks[0].add_platform(phy::Point(23,16), 10);
    this->possible_chunks[0].add_platform(phy::Point(39,19), 10);
    this->possible_chunks[0].add_platform(phy::Point(85,19), 26);
    this->possible_chunks[0].add_platform(phy::Point(56,23), 13);
    this->possible_chunks[0].add_platform(phy::Point(80,27), 19);
    this->possible_chunks[0].add_platform(phy::Point(20,29), 33);
    this->possible_chunks[0].add_platform(phy::Point(95,32), 22);
    this->possible_chunks[0].add_platform(phy::Point(0,36), 28);
    this->possible_chunks[0].add_platform(phy::Point(97,37), 31);
}

Chunk Map::get_chunk(int n)
{
    if(n>=0)
        return this->possible_chunks[Random::generateChunk(this->seed)];
}
