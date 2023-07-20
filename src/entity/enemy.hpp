#include "../maps/chunk.hpp"
#include "entity.hpp"

#ifndef ENTITY_ENEMY
#define ENTITY_ENEMY

class Enemy : public Entity {
protected:
  int _damage;
  bool _direction;
  bool _alive;
  int _type;
  int _life;

public:
  Enemy(int type, phy::Point p, bool direction);

  int get_damage();
  int get_life();
  bool get_direction();
  int get_type();

  void set_direction(bool dir);
  void set_type(int type);

  bool can_move(Chunk chunk);
  bool is_alive();

  // Hit will decreases the life of the enemy
  void hit(int damage = 1);
  // Kill will instantly kills the enemy
  void kill();
  void move();
};
#endif
