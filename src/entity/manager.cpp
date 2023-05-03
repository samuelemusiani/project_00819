#include "manager.hpp"

Manager::Manager ()
{

  this->Global_Entities = 0;
  this->Global_Coins = 0;
  this->Global_Enemies = 0;

}

Manager::~Manager()
{
  //save everything somewhere
	this->Global_Entities = 0;
  this->Global_Coins = 0;
  this->Global_Enemies = 0;

}

pnemici Manager::getAllEnemiesInChunk(int Chunk) {
  pnemici p = this->Enemies[Chunk];
  return(p);
}

pmonete Manager::getAllCoinsInChunk(int Chunk) {
  pmonete p = this->Coins[Chunk];
  return(p);
}

void Manager::add_enemy(int Chunk, nostd::string id, phy::Point p, int hp, int ms, int damg) {
  Enemy enemy = Enemy(id, p, hp, ms, damg);
  head_insert(Chunk, enemy);
  this->Global_Entities++;
  this->Global_Enemies++;
}

void Manager::add_coin(int Chunk, nostd::string id, phy::Point p, int value) {
  Coin coin = Coin(id, p, value);
  head_insert(Chunk, coin);
  this->Global_Entities++;
  this->Global_Coins++;
}

//override head_insert per enemy
void Manager::head_insert(int Chunk, Enemy enemy) {
  if(this->Enemies[Chunk] == NULL) {
    pnemici p = new nemici;
    p->next = NULL;
    p->val = enemy;
  } else {
    pnemici p = new nemici;
    p->next = this->Enemies[Chunk];
    p->val = enemy;
  }
}

//override head_insert per coin
void Manager::head_insert(int Chunk, Coin coin) {
  if(this->Coins[Chunk] == NULL) {
    pmonete p = new monete;
    p->next = NULL;
    p->val = coin;
  } else {
    pmonete p = new monete;
    p->next = this->Coins[Chunk];
    p->val = coin;
  }
}

//override delete_el per enemy
pnemici Manager::delete_el(pnemici p, Enemy enemy) {
  if(p == NULL) {
    return(p);
  } else if (p->val.get_id() == enemy.get_id() && p->val.get_pos() == enemy.get_pos()) { //controllo l'id e la pos dell'oggetto da eliminare
    pnemici tmp = p->next;
    delete p;
    p = NULL;
    return(tmp);
  } else {
    p->next = delete_el(p->next, p->val);
    return(p);
  }
}

//override delete_el per coin
pmonete Manager::delete_el(pmonete p, Coin coin) {
  if(p == NULL) {
    return(p);
  } else if (p->val.get_id() == coin.get_id() && p->val.get_pos() == coin.get_pos()) { //controllo l'id e la pos dell'oggetto da eliminare
    pmonete tmp = p->next;
    delete p;
    p = NULL;
    return(tmp);
  } else {
    p->next = delete_el(p->next, p->val);
    return(p);
  }
}

/*void kill_entity(int Chunk, Entity e) {//TBD
  plsita tmp = this->Entites[Chunk];
  delete_el(tmp, e);
  this->Global_Coins--;
}*/
