#include "../draw/draw.hpp"
#include "../engine/random.hpp"
#include "../game/statistics.hpp"
#include "../maps/map.hpp"
#include "../physics/body.hpp"
#include "bullet.hpp"

#include "../../etc/logs/logs.hpp"
#include "../../etc/nostd/vector.hpp"

#ifndef ENTITY_MANAGER
#define ENTITY_MANAGER

/* Per ora i diversi tipi di nemici e di bullets li ho gestiti
 * inserendo un campo ausiliario nella classe e facendo i chek
 * nelle funzioni in cui la differenza effettivamente conta.
 * Il modo corretto sarebbe usare l'ereditarieta' e nella lista
 * mettere dei puntatori alla classe padre. Con un metodo definito
 * nel padre, ma che poi nei figli e' necessario fare l'override, e
 * con un enum possiamo distinguere che tipo di classe specifico
 * e' l'oggetto e quindi fare un cast esplicito ed usare quello.
 *
 * A livello teorico e' piu' elegante come soluzione ma sicuramente
 * piu' complessa da gestire in quando si avrebbe una lista di puntatori
 * e non sarebbe semplice poi evitare errori es. memory leak.
 * Se ho tempo implemento la nostd::list cosi' parte del lavoro
 * si semplifica, ma per il momento mi basta che funzioni il tutto
 * e rimango cosi'
 */

struct node_enemy {
  // Avoid calling the default constructor
  Enemy val = Enemy(0, phy::Point(0, 0), false);
  node_enemy *next;
};
typedef node_enemy *list_enemies;

struct node_coin {
  // Avoid calling the default constructor
  Coin val = Coin(phy::Point(0, 0));
  node_coin *next;
};
typedef node_coin *list_coins;

struct node_bullet {
  // Avoid calling the default constructor
  Bullet val = Bullet(phy::Point(0, 0), false, 0);
  // Expiration if 0 make the bullets despawn
  int expiration = 300;
  node_bullet *next;
};
typedef node_bullet *list_bullets;

class Manager {
private:
  Map map;
  Seed seed;
  int current_chunk;

  nostd::vector<list_enemies> Enemies;
  nostd::vector<list_coins> Coins;
  list_bullets Bullets;

  int Global_Entities;
  int Global_Enemies;
  int Global_Coins;

  int reloading_gun;

  void add_enemy(int Chunk, Enemy enemy);
  void add_coin(int Chunk, Coin coin);
  void head_insert(int Chunk, Enemy enemy);
  void head_insert(int Chunk, Coin coin);
  list_bullets bullets_collisions(list_bullets p, phy::Body &player,
                                  Statistics &stats);
  list_bullets delete_all_bullets(list_bullets p);

public:
  Manager(Map map);
  ~Manager();

  void set_chunk(int Chunk);
  int collect_coin(phy::Point player_position);
  void shoot(phy::Point position, bool direction, int type);
  void update_entities(int time, phy::Body &player, Statistics &stats);
  void
  draw_entities(Draw *screen); // This method must be called afther set_chunk()

  bool is_there_an_entity_in_platform(int Chunk, int plat);
  bool is_there_an_entity_in_point(int Chunk, phy::Point point);
  list_enemies get_all_enemies_in_chunk(int Chunk);
  list_coins get_all_coins_in_chunk(int Chunk);
  nostd::vector<phy::Point> get_all_entities_positions_in_chunk(int Chunk);

  // Saving
  nostd::string get_entities_status();
  void set_entities_status(int number_of_chunks, nostd::string s);
};
#endif
