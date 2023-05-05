#include "entity.hpp"
#include "../maps/chunk.hpp"

#ifndef ENTITY_ENEMY
#define ENTITY_ENEMY

enum DIRECTION_POSSIBILITY {dx, sx}; //da riverdere su chatGPT3.5

class Enemy : public Entity {
protected:

  int hp;
  double ms;
  int damg;
  DIRECTION_POSSIBILITY dir;
  bool isAlive;

public:

  Enemy(char id, phy::Point p, int hp, int ms, int damg) ;
  Enemy();

  void init_enemy(int hp, int ms, int damg);
  void set_hp(int hp);
  void got_hit(int damGot);
  void set_state(bool s);
  void set_direction(DIRECTION_POSSIBILITY dir);
  bool canMove(Chunk chunk);

};
#endif
