#include "enemy.hpp"

Enemy::Enemy (int hp, int ms, int damg) {

  this->init_enemy(hp, ms, damg);

};

void Enemy::Enemy (int hp, int ms, int ms)  {

  this->set_state(true);
  this->set_hp(hp);
  this->ms = ms;
  this->damg = damg;

}

void Enemy::set_hp(int hp)
{

  this->hp = hp;

}

void Enemy::got_hit(int damGot)
{

  //Draw::drawHit();  (prima o poi la faccio)
  this->set_hp(this->hp - damGot);

}

void set_state(bool s) {

  this->isAlive = s;

}
