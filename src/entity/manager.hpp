//#include "enemy.hpp"
//#include "coin.hpp"
#include "types.hpp"
#include "../../etc/nostd/vector.hpp"
#include "../draw/draw.hpp"
#include "../maps/map.hpp"
#include "../engine/random.hpp"

#include "../../etc/logs/logs.hpp"

#ifndef ENTITY_MANAGER
#define ENTITY_MANAGER

struct nemici {
  Enemy val;
  nemici* next;
};
typedef nemici* pnemici;

struct monete {
  Coin val;
  monete* next;
};
typedef monete* pmonete;

class Manager {
private:
  Map map;
  Seed seed;
  int current_chunk;
  nostd::vector<pnemici> Enemies;
  nostd::vector<pmonete> Coins;
  int Global_Entities;
  int Global_Enemies;
  int Global_Coins;

protected:
  //pnemici getAllEnemiesInChunk(int Chunk);
  //pmonete getAllCoinsInChunk(int Chunk);

public:

  Manager(Map map);
  ~Manager();

  void add_enemy(int Chunk, Enemy enemy, phy::Point p, bool dir);
  //void add_enemy(int Chunk, Enemy enemy, phy::Point p, DIRECTION_POSSIBILITY dir);
  void add_coin(int Chunk, Coin coin, phy::Point p);

  void head_insert(int Chunk, Enemy enemy);
  void head_insert(int Chunk, Coin coin);
  void set_chunk(int Chunk, Map map);
  void collect_coin(int Chunk, Coin coin);
  void kill_entity(int Chunk, Enemy enemy);
  void move_enemies(int& time);
  void print_entity(Draw screen); //la print enemy va chiamata dopo la chiamata del chunk
  bool is_there_an_entity_in_platform(Map map, int Chunk, int plat); //check se c'è un nemico sulla piattaforma
  bool is_there_an_entity_in_point(int Chunk, phy::Point point);
  pnemici getAllEnemiesInChunk(int Chunk);
  pmonete getAllCoinsInChunk(int Chunk);

  void print_enemy_list();

};
#endif
