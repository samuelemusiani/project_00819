/*
 * Alma Mater Studiorum - University of Bologna
 * First cycle degree in Computer Science
 * Computer Programming - 00819
 *
 * Author: Peronese Lorenzo #0001081726
 *
 * chunk.hpp: Class for each chunk, return the position of the platforms to draw
 * them
 */

#ifndef MAPS_CHUNK
#define MAPS_CHUNK

#include "../../etc/nostd/vector.hpp"
#include "platform.hpp"
#include <vector>

class Chunk {
private:
  nostd::vector<Platform> platforms;

public:
  void add_platform(phy::Point pos, int len);
  bool is_there_a_platform(phy::Point pos);
  nostd::vector<Platform> get_platforms();
};

#endif
