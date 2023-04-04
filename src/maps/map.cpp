#include "map.hpp"
// A chunk is 148x42
void Map::initialize_chunks()
{
    // 1st chunk
    this->possible_chunks[0].add_platform(46, 3, 11);
    this->possible_chunks[0].add_platform(112, 3, 15);
    this->possible_chunks[0].add_platform(21, 8, 23);
    this->possible_chunks[0].add_platform(86, 8, 21);
    this->possible_chunks[0].add_platform(130, 8, 9);
    this->possible_chunks[0].add_platform(2, 12, 11);
    this->possible_chunks[0].add_platform(110, 14, 24);
    this->possible_chunks[0].add_platform(23, 16, 10);
    this->possible_chunks[0].add_platform(39, 19, 10);
    this->possible_chunks[0].add_platform(85, 19, 26);
    this->possible_chunks[0].add_platform(56, 23, 13);
    this->possible_chunks[0].add_platform(80, 27, 19);
    this->possible_chunks[0].add_platform(20, 29, 33);
    this->possible_chunks[0].add_platform(95, 32, 22);
    this->possible_chunks[0].add_platform(0, 36, 28);
    this->possible_chunks[0].add_platform(97, 37, 31);
}

Chunk Map::get_chunk(int n)
{
    //da randomizzare
    return this->possible_chunks[0];
}
