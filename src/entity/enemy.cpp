#include "enemy.hpp"

Enemy::Enemy(int type, phy::Point p, bool dir)
    : Entity(p), _alive(true), _type(type), _direction(dir)
{
    this->_damage = (type + 1) * 10;
};

int Enemy::get_damage()
{
    return this->_damage;
}

bool Enemy::get_direction()
{
    return this->_direction;
}

int Enemy::get_type()
{
    return this->_type;
}

void Enemy::set_direction(bool dir)
{
    this->_direction = dir;
}

bool Enemy::can_move(Chunk chunk)
{
    phy::Point next_pos = this->_direction ? phy::Point(1, -1) : phy::Point(-1, -1);
    return chunk.is_there_a_platform(this->_position + next_pos);
}

bool Enemy::is_alive()
{
    return this->_alive;
}

void Enemy::kill()
{
    this->_alive = false;
}

void Enemy::move()
{
    if(this->_direction) 
        this->set_position(this->get_position() + phy::Point(1,0));
    else 
        this->set_position(this->get_position() + phy::Point(-1,0));
}
