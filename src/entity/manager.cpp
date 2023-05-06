#include "manager.hpp"

Manager::Manager (Map map)
{
  this->map = map;
  this->set_chunk(-1, this->map);
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

void Manager::add_enemy(int Chunk, Enemy enemy, phy::Point p, bool dir) {
  enemy.set_point(p);
  enemy.set_direction(dir);

  if(Enemies.size() <= Chunk)
	  Enemies.push_back(nullptr);

  head_insert(Chunk, enemy);
  this->Global_Entities++;
  this->Global_Enemies++;
}

void Manager::add_coin(int Chunk, Coin coin, phy::Point p) {
  coin.set_point(p);

  if(Coins.size() <= Chunk)
	  Coins.push_back(nullptr);

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
    this->Enemies[Chunk] = p;
  } else {
    pnemici p = new nemici;
    p->next = this->Enemies[Chunk];
    p->val = enemy;
    this->Enemies[Chunk] = p;
  }
}

//override head_insert per coin
void Manager::head_insert(int Chunk, Coin coin) {
  if(this->Coins[Chunk] == NULL) {
    pmonete p = new monete;
    p->next = NULL;
    p->val = coin;
    this->Coins[Chunk] = p;
  } else {
    pmonete p = new monete;
    p->next = this->Coins[Chunk];
    p->val = coin;
    this->Coins[Chunk] = p;
  }
}

void Manager::kill_entity(int Chunk, Enemy enemy) {
  pnemici tmp = this->Enemies[Chunk];
  while (tmp != NULL || enemy.get_point() == tmp->val.get_point()) {
    tmp->val.set_state(false);
  }
  this->Global_Enemies--;
  this->Global_Entities--;
}

void Manager::collect_coin(int Chunk, Coin coin) {
  pmonete tmp = this->Coins[Chunk];
  while (tmp != NULL || coin.get_point() == tmp->val.get_point()) {
    tmp->val.set_state(true);
  }
  this->Global_Coins--;
  this->Global_Entities--;
}

void Manager::set_chunk(int Chunk, Map map) {
  if(this->current_chunk < Chunk) {
    this->current_chunk = Chunk;
  } else if (this->current_chunk > Chunk) {
    for(int i = 0; i < map.getEnemies(Chunk); i ++)
      this->add_enemy(this->current_chunk, ENEMY_TYPE1, phy::Point(10+i,10+i), true);//EnemyType[1/*Random::generateEnemyType()*/], phy::Point(i,i)/*Random::generateEnemyPosition(map)*/, i%2 == 0 ? true : false);
  	for(int i = 0; i < map.getCoins(Chunk); i ++)
      this->add_coin(this->current_chunk, COIN_TYPE1, phy::Point(5+i,5+i));//CoinType[1/*Random::generateCoinType()*/], phy::Point(2*i,2*i)/*Random::generateCoinPosition(map)*/);
    //bullets
  }
}

//time is in dec sec (sec*10^-1)
void Manager::move_enemies(int time) {
  pnemici tmp = this->Enemies[this->current_chunk];
  Chunk chunk = map.get_chunk(this->current_chunk);
  while(tmp != NULL) {
    if(tmp->val.isItAlive()) {
      if(tmp->val.canMove(chunk)) {
        if(tmp->val.get_direction() == true) tmp->val.set_point(tmp->val.get_point() + phy::Point(1,0)); //se non compila cambiare il +=
        else tmp->val.set_point(tmp->val.get_point() + phy::Point(-1,0));
      } else tmp->val.set_direction(tmp->val.get_direction() ==  true ? false : true);
    }
    tmp = tmp->next;
  }
}

void Manager::print_entity(Draw screen) {
  pnemici p = this->Enemies[this->current_chunk];
	while(p != NULL) {
		screen.drawEntity(p->val);
		p = p->next;
	}

  pmonete q = this->Coins[this->current_chunk];
	while(q != NULL) {
		screen.drawEntity(q->val);
		q = q->next;
	}
}


bool Manager::is_there_an_entity_in_platform(Map map, int Chunk, int plat) { //check se c'è un nemico sulla piattaforma
  bool check = false;
  Platform platform = map.get_chunk(Chunk).get_platforms()[plat];

  int start = platform.get_position().get_xPosition();
  int end = platform.get_position().get_xPosition() + platform.get_length();
  pnemici p = getAllEnemiesInChunk(Chunk);
  pmonete q = getAllCoinsInChunk(Chunk);

  while(p != NULL && !check) {
    if(p->val.get_y() == platform.get_position().get_yPosition()) {
      if(p->val.get_x() >= start && p->val.get_x() <= end) {
        check = true;
      }
    }
    p = p->next;
  }

  while(q != NULL && !check) {
    if(q->val.get_y() == platform.get_position().get_yPosition()) {
      if(q->val.get_x() >= start && q->val.get_x() <= end) {
        check = true;
      }
    }
    q = q->next;
  }

  return(check);
}

bool Manager::is_there_an_entity_in_point(int Chunk, phy::Point point) {
  bool check = false;

  pnemici p = getAllEnemiesInChunk(Chunk);
  pmonete q = getAllCoinsInChunk(Chunk);

  while(p != NULL && !check) {
    if(p->val.get_y() == point.get_yPosition() && p->val.get_x() == point.get_xPosition()) {
      check = true;
    }
    p = p->next;
  }

  while(q != NULL && !check) {
    if(q->val.get_y() == point.get_yPosition() && q->val.get_x() == point.get_xPosition()) {
      check = true;
    }
    q = q->next;
  }

  return(check);
}



/*
NON SERVE PER I NEMICI O MONETE MA FORSE SERVIRA' PER I BULLETS
pnemici Manager::delete_el(pproiettile p, Bullet bullet) {
  if(p == NULL) {
    return(p);
  } else if (p->val.get_id() == bullet.get_id() && p->val.get_point() == bullet.get_point()) { //controllo l'id e la pos dell'oggetto da eliminare
    pproiettile tmp = p->next;
    delete p;
    p = NULL;
    return(tmp);
  } else {
    p->next = delete_el(p->next, p->val);
    return(p);
  }
}
*/
