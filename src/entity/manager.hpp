#include "enemy.hpp"
#include "coin.hpp"
#include "../../etc/nostd/vector.hpp"

//#define TYPE_OF_ENTITIES {'A', 'B', 'C', 'D', 'E', '$'}

//IDEE DIVERSE PER FARE LA STRUTTURA DATI PER I NEMICI/MONETE:
/*
LORENZO'S ADVICE: una lista per nemici e una per monete
per sapere in che chunk sono chiedere alla classe random (o quello che genera le robe nel chuck)
di darti quanti nemici/monete ci sono in quel chunk così da sapere nella lista dove andare a cercare
IO FAREI UNA PICCOLA MODIFICA:
non è necessario fare una richiesta della classe random, basta mettere un campo in ogni entità (oltre a id e p)
che identifichi il chunk di generazione
SE A SAMMY NON VA BENE:
dobbiamo fixare il problema della doppia struttura, o modificare come si gestiscono le entità
*/

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
  nostd::vector<pnemici> Enemies;
  nostd::vector<pmonete> Coins;
  int Global_Entities;
  int Global_Enemies;
  int Global_Coins;

public:

  Manager();
  ~Manager();

  void add_enemy(int Chunk, nostd::string id, phy::Point p, int hp, int ms, int damg);
  void add_coin(int Chunk, nostd::string id, phy::Point p, int value);
  //void kill_entity();//forse non serve

  pnemici getAllEnemiesInChunk(int Chunk);
  pmonete getAllCoinsInChunk(int Chunk);
  void head_insert(int Chunk, Enemy enemy);
  void head_insert(int Chunk, Coin coin);
  pnemici delete_el(pnemici p, Enemy enemy);
  pmonete delete_el(pmonete p, Coin coin);

};
#endif
