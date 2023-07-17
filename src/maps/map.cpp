/*
* Alma Mater Studiorum - University of Bologna
* First cycle degree in Computer Science
* Computer Programming - 00819
*
* Author: Peronese Lorenzo #0001081726
*
* map.cpp: Implementation of the Map class
*/

#include "map.hpp"
#include "../engine/random.hpp"

// A chunk is 148x42

Map::Map() {
	srand(time(nullptr));
	this->seed.setSeed(rand());
	initialize_chunks();
}

Map::Map(int seed) {
	this->seed.setSeed(seed);
	initialize_chunks();
}

void Map::initialize_chunks() {
	// 1st chunk
	this->possible_chunks[0].add_platform(phy::Point(46, 39), 11);
	this->possible_chunks[0].add_platform(phy::Point(112, 39), 15);
	this->possible_chunks[0].add_platform(phy::Point(21, 34), 23);
	this->possible_chunks[0].add_platform(phy::Point(86, 34), 21);
	this->possible_chunks[0].add_platform(phy::Point(130, 34), 9);
	this->possible_chunks[0].add_platform(phy::Point(2, 30), 11);
	this->possible_chunks[0].add_platform(phy::Point(110, 28), 24);
	this->possible_chunks[0].add_platform(phy::Point(23, 26), 10);
	this->possible_chunks[0].add_platform(phy::Point(39, 23), 10);
	this->possible_chunks[0].add_platform(phy::Point(85, 23), 26);
	this->possible_chunks[0].add_platform(phy::Point(56, 19), 13);
	this->possible_chunks[0].add_platform(phy::Point(80, 15), 19);
	this->possible_chunks[0].add_platform(phy::Point(20, 13), 33);
	this->possible_chunks[0].add_platform(phy::Point(95, 10), 22);
	this->possible_chunks[0].add_platform(phy::Point(0, 6), 28);
	this->possible_chunks[0].add_platform(phy::Point(97, 5), 31);

	// 2nd chunk
	this->possible_chunks[1].add_platform(phy::Point(60, 40), 12);
	this->possible_chunks[1].add_platform(phy::Point(24, 36), 28);
	this->possible_chunks[1].add_platform(phy::Point(80, 34), 22);
	this->possible_chunks[1].add_platform(phy::Point(0, 27), 11);
	this->possible_chunks[1].add_platform(phy::Point(114, 25), 6);
	this->possible_chunks[1].add_platform(phy::Point(29, 21), 24);
	this->possible_chunks[1].add_platform(phy::Point(77, 18), 33);
	this->possible_chunks[1].add_platform(phy::Point(38, 12), 23);
	this->possible_chunks[1].add_platform(phy::Point(77, 6), 15);
}

Chunk Map::get_chunk(int n) {
	if(n==0) {
		Chunk c = this->possible_chunks[Random::generateChunk(this->seed, n)];
		c.add_platform(phy::Point(0,0),148);
		return c;
	}
	if (n > 0)
		return this->possible_chunks[Random::generateChunk(this->seed, n)];
	else
		return this->possible_chunks[Random::generateChunk(this->seed, -n)]; // this shouldn't happen
}

int Map::getCoins(int n) {
	return Random::generateCoins(this->seed, n);
}

int Map::getEnemies(int n) {
	return Random::generateEnemies(this->seed, n);
}

Seed Map::getSeed()
{
	return this->seed;
}
