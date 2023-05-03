#include "coin.hpp"

Coin::Coin(nostd::string id, phy::Point p, int value):Entity(id, p) {

  this->init_coin(value);

}

Coin::Coin():Entity(){}

void Coin::init_coin(int value) {

  this->value = value;
  this->set_state(false);

}

int Coin::get_value() {

  return(this->value);

}

void Coin::set_state(bool s) {

  this->alredyCollected = s;

}
