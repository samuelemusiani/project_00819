/*
* Alma Mater Studiorum - University of Bologna
* First cycle degree in Computer Science
* Computer Programming - 00819
*
* Author: Peronese Lorenzo #0001081726
*
* random.cpp: Implementation of the Random class
*/

#include <ctime>
#include "random.hpp"
#define SCREEN_WIDTH 148
#define SCREEN_HEIGHT 42

Random::Random()
{

}

void Random::seedSrand(Seed seed, int chunk, int offset)
{
	srand(seed.getSeed() + chunk * offset);
}

int Random::generateEnemies(Seed seed, int chunk) {
	seedSrand(seed, chunk, 11);
	return (2 + rand() % 3); // enemies range: 2-4
}

int Random::generateCoins(Seed seed, int chunk) {
	seedSrand(seed, chunk, 13);
	return (3 + rand() % 4); // coins range: 3-6
}

int Random::generateChunk(Seed seed, int chunk) {
	if(chunk == 0)
	{
		seedSrand(seed, chunk);
		return (rand() % 2);
	}
	else
	{
		int previous = generateChunk(seed,chunk-1);
		seedSrand(seed,chunk);
		int random = rand() % 2;
		if(random == previous)
			return (random + 1) % 2;
		else
			return random;
	}
}

int Random::generateEnemyType(Seed seed,int chunk)
{
	seedSrand(seed,chunk,23);
    int random = rand() % 100;
    if(random < (60 - chunk*2))
        return 1;
    else if(random < 85 - chunk)
        return 2;
    else
        return 3;
}

int Random::generateCoinType(Seed seed,int chunk)
{
	seedSrand(seed,chunk,29);
    int random = rand() % 100;
    if(random < (60 - chunk*2))
        return 1;
    else if(random < 85 - chunk)
        return 2;
    else
        return 3;
}

phy::Point Random::generateEnemyPosition(Map map, int chunk)
{
	phy::Point point;
	seedSrand(map.getSeed(),chunk,17);
	nostd::vector<Platform> p = map.get_chunk(chunk).get_platforms();
	int random;
	do {
		random = rand() % p.size();
	} while(false); // is_there_an_entity_in_platform(map.getSeed(),chunk,random { platform number })
	point.set_xPosition(p.at(random).get_position().get_xPosition() + rand() % p.at(random).get_length());
	point.set_yPosition(p.at(random).get_position().get_yPosition() + 1);
	return point;
}

phy::Point Random::generateCoinPosition(Map map, int chunk)
{
	phy::Point point;
	seedSrand(map.getSeed(),chunk,21);
	do {
		point.set_xPosition(rand() % SCREEN_WIDTH);
		point.set_yPosition(rand() % SCREEN_HEIGHT);
	}while(map.get_chunk(chunk).is_there_a_platform(point) /* || !is_there_an_entity_in_point(map.getSeed(),chunk,point)*/);
	return point;
}
