#include "enemy.hpp"

Enemy::Enemy (nostd::string id, phy::Point p, int hp, int ms, int damg):Entity(id, p) {

  this->init_enemy(hp, ms, damg);

};

Enemy::Enemy():Entity(){};

void Enemy::init_enemy (int hp, int ms, int damg)  {

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

void Enemy::set_state(bool s) {

  this->isAlive = s;

}
