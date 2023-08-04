/*
 * Alma Mater Studiorum - University of Bologna
 * First cycle degree in Computer Science
 * Computer Programming - 00819
 *
 * Author: Musiani Samuele #0001069143
 *
 * point.hpp: Class for a point in a plane.
 */

#ifndef PHYSICS_POINT
#define PHYSICS_POINT

namespace phy {
class Point {
protected:
  int posX;
  int posY;

public:
  Point();
  Point(int posX, int posY);
  void set_xPosition(int posX);
  void set_yPosition(int posY);
  int get_xPosition();
  int get_yPosition();

  bool operator==(const Point &p);
  bool operator!=(const Point &p);
  Point operator+(const Point &p);
  Point operator-(const Point &p);
};
} // namespace phy
#endif
