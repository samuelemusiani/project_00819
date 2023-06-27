#include "enemy.hpp"

Enemy::Enemy(const char* id, phy::Point p, int damg)
    : Entity(id, p), _damage(damg), _alive(true)
{

};

Enemy::Enemy()
{

}

int Enemy::get_damage()
{
    return this->_damage;
}

bool Enemy::get_direction()
{
    return this->_direction;
}

void Enemy::set_direction(bool dir)
{
    this->_direction = dir;
}

bool Enemy::can_move(Chunk chunk)
{
    phy::Point next_pos = this->_direction ? phy::Point(1, -1) : phy::Point(-1, -1);
    return chunk.is_there_a_platform(this->p + next_pos);
}

bool Enemy::is_alive()
{
    return this->_alive;
}

void Enemy::kill()
{
    this->_alive = false;
}
