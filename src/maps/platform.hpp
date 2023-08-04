/*
 * Alma Mater Studiorum - University of Bologna
 * First cycle degree in Computer Science
 * Computer Programming - 00819
 *
 * Author: Peronese Lorenzo #0001081726
 *
 * platform.hpp: Class for each platform, with position and length
 */

#include "../physics/point.hpp"

#ifndef MAPS_PLATFORM
#define MAPS_PLATFORM

class Platform {
private:
  phy::Point position;
  int length;

public:
  Platform();
  Platform(phy::Point pos, int len);

  void set_position(phy::Point x);
  void set_length(int len);

  phy::Point get_position() const;
  int get_length() const;
};

#endif
