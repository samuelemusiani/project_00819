#include "types.hpp"

Enemy ENEMY_TYPE1 = Enemy('1', phy::Point(0, 0), 10, 10, 10);

Enemy ENEMY_TYPE2 = Enemy('2', phy::Point(0, 0), 20, 20, 20);

Enemy ENEMY_TYPE3 = Enemy('3', phy::Point(0, 0), 30, 30, 30);

Coin COIN_TYPE1 = Coin('$', phy::Point(0, 0), 10);

Coin COIN_TYPE2 = Coin('£', phy::Point(0, 0), 20);

Coin COIN_TYPE3 = Coin('€', phy::Point(0, 0), 50);

extern Enemy EnemyType[3] = {ENEMY_TYPE1, ENEMY_TYPE2, ENEMY_TYPE3};

extern Coin CoinType[3] = {COIN_TYPE1, COIN_TYPE2, COIN_TYPE3};
