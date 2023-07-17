#include "entity.hpp"

#ifndef ENTITY_BULLET
#define ENTITY_BULLET

class Bullet : public Entity {
private:
  bool _direction;
  int _type;

public:
  Bullet(phy::Point p, bool direction, int type);

  bool get_direction();
  int get_type();

  // This is orrible but I don't see another SIMPLE way of doin it
  static int get_bullet_damage(int bullet_type);
};

#endif
