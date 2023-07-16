#include <algorithm>

#include "statistics.hpp"

Statistics::Statistics()
    : _level(0), _jump(0), _coins(0), _heart(10)
{

}

Statistics::Statistics(int level, int coins, int jump, int heart)
    : _level(level), _jump(jump), _coins(coins), _heart(heart)
{

}

void Statistics::setLevel(int level){
    this->_level = level;
}

void Statistics::setCoins(int coins){
    this->_coins = coins;
}

void Statistics::setJumps(int jump){
    this->_jump = jump;
}

void Statistics::setHearts(int heart){
    this->_heart = std::min(heart, MAX_POSSIBLE_HEARTS);
}

int Statistics::getLevel(){
    return this->_level;
}

int Statistics::getCoins(){
    return this->_coins;
}

int Statistics::getJumps(){
    return this->_jump;
}

int Statistics::getHearts(){
    return this->_heart;
}

void Statistics::incrementJumps(int delta) {
    this->_jump += delta;
}

void Statistics::incrementCoins(int delta) {
    this->_coins += delta;
}

void Statistics::incrementLevel(int delta) {
    this->_level += delta;
}

void Statistics::incrementHearts(int delta) {
    this->_heart += delta;
}
