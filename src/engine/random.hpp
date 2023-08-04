/*
 * Alma Mater Studiorum - University of Bologna
 * First cycle degree in Computer Science
 * Computer Programming - 00819
 *
 * Author: Peronese Lorenzo #0001081726
 *
 * random.hpp: class that generates random numbers for the map
 */

#include "../maps/map.hpp"
#include <cstdlib>

#ifndef ENGINE_RANDOM
#define ENGINE_RANDOM

#define MAX_COINS_IN_CHUNK 10
#define MAX_ENEMIES_IN_CHUNK 8

class Random {
public:
  Random();
  static void seedSrand(int seed, int chunk, int offset = 1);
  static int generateEnemies(int seed, int chunk);
  static int generateCoins(int seed, int chunk);
  static int generateChunk(int seed, int chunk);
  static int generateEnemyType(int seed, int chunk, int num);
  static phy::Point generateEnemyPosition(Map map, int chunk,
                                          nostd::vector<phy::Point> entityPos);
  static phy::Point generateCoinPosition(Map map, int chunk,
                                         nostd::vector<phy::Point> entityPos);
  static bool is_there_an_entity(nostd::vector<phy::Point> entityPos,
                                 phy::Point pos);
};
#endif
