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
	this->possible_chunks[0].add_platform(phy::Point(39, 38), 24);
	this->possible_chunks[0].add_platform(phy::Point(72, 33), 25);
	this->possible_chunks[0].add_platform(phy::Point(0, 31), 14);
	this->possible_chunks[0].add_platform(phy::Point(30, 26), 20);
	this->possible_chunks[0].add_platform(phy::Point(110, 26), 17);
	this->possible_chunks[0].add_platform(phy::Point(78, 21), 17);
	this->possible_chunks[0].add_platform(phy::Point(45, 13), 50);
	this->possible_chunks[0].add_platform(phy::Point(9, 4), 30);

	// 2nd chunk
	this->possible_chunks[1].add_platform(phy::Point(60, 40), 12);
	this->possible_chunks[1].add_platform(phy::Point(24, 36), 28);
	this->possible_chunks[1].add_platform(phy::Point(80, 34), 22);
	this->possible_chunks[1].add_platform(phy::Point(0, 27), 11);
	this->possible_chunks[1].add_platform(phy::Point(114, 25), 6);
	this->possible_chunks[1].add_platform(phy::Point(29, 21), 24);
	this->possible_chunks[1].add_platform(phy::Point(77, 18), 33);
	this->possible_chunks[1].add_platform(phy::Point(38, 12), 23);
	this->possible_chunks[1].add_platform(phy::Point(77, 6), 25);

	//3rd chunk
	this->possible_chunks[2].add_platform(phy::Point(54, 38), 22);
	this->possible_chunks[2].add_platform(phy::Point(21, 29), 14);
	this->possible_chunks[2].add_platform(phy::Point(0, 21), 7);
	this->possible_chunks[2].add_platform(phy::Point(10, 18), 106);
	this->possible_chunks[2].add_platform(phy::Point(122, 14), 12);
	this->possible_chunks[2].add_platform(phy::Point(22, 11), 98);
	this->possible_chunks[2].add_platform(phy::Point(2, 2), 25);

	//4th chunk
	this->possible_chunks[3].add_platform(phy::Point(58, 38), 14);
	this->possible_chunks[3].add_platform(phy::Point(34, 35), 14);
	this->possible_chunks[3].add_platform(phy::Point(0, 31), 8);
	this->possible_chunks[3].add_platform(phy::Point(13, 27), 101);
	this->possible_chunks[3].add_platform(phy::Point(122, 23), 12);
	this->possible_chunks[3].add_platform(phy::Point(13, 19), 102);
	this->possible_chunks[3].add_platform(phy::Point(1, 14), 8);
	this->possible_chunks[3].add_platform(phy::Point(14, 10), 100);
	this->possible_chunks[3].add_platform(phy::Point(107, 3), 25);
	this->possible_chunks[3].add_platform(phy::Point(10, 3), 25);

	//5th chunk
	this->possible_chunks[4].add_platform(phy::Point(47, 36), 55);
	this->possible_chunks[4].add_platform(phy::Point(0, 27), 7);
	this->possible_chunks[4].add_platform(phy::Point(138, 27), 7);
	this->possible_chunks[4].add_platform(phy::Point(47, 22), 55);
	this->possible_chunks[4].add_platform(phy::Point(0, 13), 9);
	this->possible_chunks[4].add_platform(phy::Point(139, 13), 7);
	this->possible_chunks[4].add_platform(phy::Point(10, 4), 29);
	this->possible_chunks[4].add_platform(phy::Point(106, 4), 29);

	//6th chunk
	this->possible_chunks[5].add_platform(phy::Point(70, 39), 14);
	this->possible_chunks[5].add_platform(phy::Point(45, 33), 33);
	this->possible_chunks[5].add_platform(phy::Point(0, 26), 11);
	this->possible_chunks[5].add_platform(phy::Point(87, 22), 22);
	this->possible_chunks[5].add_platform(phy::Point(1, 18), 37);
	this->possible_chunks[5].add_platform(phy::Point(121, 14), 15);
	this->possible_chunks[5].add_platform(phy::Point(59, 10), 26);
	this->possible_chunks[5].add_platform(phy::Point(96, 3), 13);

	//7th chunk
	this->possible_chunks[6].add_platform(phy::Point(48, 39), 43);
	this->possible_chunks[6].add_platform(phy::Point(22, 33), 21);
	this->possible_chunks[6].add_platform(phy::Point(96, 33), 15);
	this->possible_chunks[6].add_platform(phy::Point(127, 29), 14);
	this->possible_chunks[6].add_platform(phy::Point(1, 27), 14);
	this->possible_chunks[6].add_platform(phy::Point(96, 24), 15);
	this->possible_chunks[6].add_platform(phy::Point(20, 21), 19);
	this->possible_chunks[6].add_platform(phy::Point(128, 19), 14);
	this->possible_chunks[6].add_platform(phy::Point(1, 16), 12);
	this->possible_chunks[6].add_platform(phy::Point(97, 13), 15);
	this->possible_chunks[6].add_platform(phy::Point(21, 11), 15);
	this->possible_chunks[6].add_platform(phy::Point(127, 8), 12);
	this->possible_chunks[6].add_platform(phy::Point(1, 5), 13);
	this->possible_chunks[6].add_platform(phy::Point(0, 1), 40);
	this->possible_chunks[6].add_platform(phy::Point(96, 1), 43);

	//8th chunk
	this->possible_chunks[7].add_platform(phy::Point(59, 38), 31);
	this->possible_chunks[7].add_platform(phy::Point(102, 33), 35);
	this->possible_chunks[7].add_platform(phy::Point(75, 30), 24);
	this->possible_chunks[7].add_platform(phy::Point(48, 27), 27);
	this->possible_chunks[7].add_platform(phy::Point(22, 25), 25);
	this->possible_chunks[7].add_platform(phy::Point(0, 20), 22);
	this->possible_chunks[7].add_platform(phy::Point(23, 18), 24);
	this->possible_chunks[7].add_platform(phy::Point(48, 15), 25);
	this->possible_chunks[7].add_platform(phy::Point(74, 12), 24);
	this->possible_chunks[7].add_platform(phy::Point(104, 4), 34);

	//9th chunk
	this->possible_chunks[8].add_platform(phy::Point(56, 39), 30);
	this->possible_chunks[8].add_platform(phy::Point(26, 35), 19);
	this->possible_chunks[8].add_platform(phy::Point(49, 32), 21);
	this->possible_chunks[8].add_platform(phy::Point(73, 29), 18);
	this->possible_chunks[8].add_platform(phy::Point(95, 26), 20);
	this->possible_chunks[8].add_platform(phy::Point(118, 20), 18);
	this->possible_chunks[8].add_platform(phy::Point(96, 18), 17);
	this->possible_chunks[8].add_platform(phy::Point(73, 15), 20);
	this->possible_chunks[8].add_platform(phy::Point(49, 12), 19);
	this->possible_chunks[8].add_platform(phy::Point(23, 10), 20);
	this->possible_chunks[8].add_platform(phy::Point(0, 3), 19);

	//10th chunk
	this->possible_chunks[9].add_platform(phy::Point(57, 39), 28);
	this->possible_chunks[9].add_platform(phy::Point(44, 31), 51);
	this->possible_chunks[9].add_platform(phy::Point(29, 26), 17);
	this->possible_chunks[9].add_platform(phy::Point(91, 26), 18);
	this->possible_chunks[9].add_platform(phy::Point(29, 19), 79);
	this->possible_chunks[9].add_platform(phy::Point(0, 9), 18);
	this->possible_chunks[9].add_platform(phy::Point(121, 9), 15);
	this->possible_chunks[9].add_platform(phy::Point(22, 3), 17);
	this->possible_chunks[9].add_platform(phy::Point(96, 3), 23);

}

Chunk Map::get_chunk(int n) {
	Chunk c;
	if(n==0) {
		c = this->possible_chunks[Random::generateChunk(this->seed, n)];
		c.add_platform(phy::Point(0,0),148);
	}
	else if (n > 0)
		c = this->possible_chunks[Random::generateChunk(this->seed, n)];
	else
		c = this->possible_chunks[Random::generateChunk(this->seed, -n)]; // this shouldn't happen
	return c;
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
