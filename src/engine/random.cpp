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
    // return std::min(7, chunk / 2 + rand() % 3);
    return (5 + chunk);
}

int Random::generateCoins(Seed seed, int chunk) {
	seedSrand(seed, chunk, 13);
	return std::max(1, 3 + rand() % 4 - chunk / 3);
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

int Random::generateEnemyType(Seed seed,int chunk,int num)
{
	seedSrand(seed,chunk,27 + num);
    int random = rand() % 100;
    if(random < (60 - chunk*2))
        return 1;
    else if(random < 85 - chunk)
        return 2;
    else
        return 3;
}

int Random::generateCoinType(Seed seed,int chunk,int num)
{
	seedSrand(seed,chunk,23 + num);
    int random = rand() % 100;
    if(random < (60 - chunk*2))
        return 1;
    else if(random < 85 - chunk)
        return 2;
    else
        return 3;
}

phy::Point Random::generateEnemyPosition(Map map, int chunk,nostd::vector<phy::Point> entityPos)
{
	phy::Point point;
	seedSrand(map.getSeed(),chunk,17);
	nostd::vector<Platform> p = map.get_chunk(chunk).get_platforms();
	int random;
	bool found;
	phy::Point add;
	add.set_yPosition(1);

    // I can put all enemies on different platforms
    bool platform_are_not_enough = p.size() <= entityPos.size();
	do {
		found = true;
		if(chunk==0)
			random = rand() % (p.size() - 1); // in the first chunk, enemies cannot spawn on the lowest platform
		else
			random = rand() % p.size();
		for(int i=0;i<p[random].get_length();i++)
		{
			add.set_xPosition(i);
			if(is_there_an_entity(entityPos,p[random].get_position()+add) && !platform_are_not_enough)
				found = false;
		}
	} while(!found);
	point.set_xPosition(p.at(random).get_position().get_xPosition() + rand() % p.at(random).get_length());
	point.set_yPosition(p.at(random).get_position().get_yPosition() + 1);
	return point;
}

phy::Point Random::generateCoinPosition(Map map, int chunk,nostd::vector<phy::Point> entityPos)
{
	phy::Point point;
	Chunk c = map.get_chunk(chunk);
	seedSrand(map.getSeed(),chunk,21);
	do {
		point.set_xPosition(rand() % SCREEN_WIDTH);
		point.set_yPosition(rand() % SCREEN_HEIGHT);
	}while(c.is_there_a_platform(point) || is_there_an_entity(entityPos,point));
	return point;
}

bool Random::is_there_an_entity(nostd::vector<phy::Point> entityPos,phy::Point pos)
{
	bool found = false;
	int i = 0;
	while(i<entityPos.size() && !found)
	{
		if(entityPos[i] == pos)
			found = true;
		i++;
	}
	return found;
}

