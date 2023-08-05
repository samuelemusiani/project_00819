/*
 * Alma Mater Studiorum - University of Bologna
 * First cycle degree in Computer Science
 * Computer Programming - 00819
 *
 * Author: Ayache Omar #0001068895
 *
 * enemy.cpp: Class that implements
 * an enemy extending Entity
 */

#include "enemy.hpp"

Enemy::Enemy(int type, phy::Point p, bool dir)
    : Entity(p), _alive(true), _type(type), _direction(dir) {
  this->_damage = (type + 1) * 10;
  this->_life = type == 2 ? 2 : 1;
};

int Enemy::get_damage() { return this->_damage; }

int Enemy::get_life() { return this->_life; }

bool Enemy::get_direction() { return this->_direction; }

int Enemy::get_type() { return this->_type; }

void Enemy::set_direction(bool dir) { this->_direction = dir; }

void Enemy::set_type(int type) { this->_type = type; }

bool Enemy::can_move(Chunk chunk) {
  phy::Point next_pos =
      this->_direction ? phy::Point(1, -1) : phy::Point(-1, -1);
  return chunk.is_there_a_platform(this->get_position() + next_pos);
}

bool Enemy::is_alive() { return this->_alive; }

void Enemy::hit(int damage) {
  this->_life -= damage;
  if (this->_life <= 0)
    this->kill();
}

void Enemy::kill() { this->_alive = false; }

void Enemy::move() {
  if (this->_direction)
    this->set_position(this->get_position() + phy::Point(1, 0));
  else
    this->set_position(this->get_position() + phy::Point(-1, 0));
}
