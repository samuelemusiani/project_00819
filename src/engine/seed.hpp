/*
 * Alma Mater Studiorum - University of Bologna
 * First cycle degree in Computer Science
 * Computer Programming - 00819
 *
 * Author: Peronese Lorenzo #0001081726
 *
 * Seed.hpp: Class that affects the seed for chunks, enemies and coins
 */

#ifndef ENGINE_SEED
#define ENGINE_SEED

class Seed {
private:
  int seed;

public:
  Seed();
  int getSeed();
  void setSeed(int seed);
};

#endif
