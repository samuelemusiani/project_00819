#include "manager.hpp"

Manager::Manager (Map map)
    : Global_Entities(0), Global_Coins(0), Global_Enemies(0), 
        current_chunk(-1), Bullets(nullptr)
{
    this->map = map;
    this->seed = map.getSeed();
}

void Manager::set_chunk(int Chunk, Map map)
{
    // For semplicity all bullets outside the current chunk despawn
    if (this->current_chunk != Chunk)
        this->Bullets = this->delete_all_bullets(this->Bullets);

    if(this->current_chunk < Chunk) {
        this->Enemies.push_back(nullptr);
        this->Coins.push_back(nullptr);

        int number_of_enemies = map.getEnemies(Chunk);
        for(int i = 0; i < number_of_enemies; i++) {
            this->add_enemy(Chunk, 
                    EnemyType[Random::generateEnemyType(this->seed, Chunk, i) - 1], 
                    Random::generateEnemyPosition(map, Chunk, 
                        this->get_all_entities_positions_in_chunk(Chunk)), i%2 == 0);
        }

        int number_of_coins = map.getCoins(Chunk);
        for(int i = 0; i < number_of_coins; i++)
            this->add_coin(Chunk, 
                    CoinType[Random::generateCoinType(this->seed, Chunk, i) - 1], 
                    Random::generateCoinPosition(map, Chunk, 
                        this->get_all_entities_positions_in_chunk(Chunk)));
    }
    this->current_chunk = Chunk;
}

void Manager::add_enemy(int Chunk, Enemy enemy, phy::Point p, bool dir)
{
    enemy.set_position(p);
    enemy.set_direction(dir);

    head_insert(Chunk, enemy);
    this->Global_Entities++;
    this->Global_Enemies++;
}

void Manager::add_coin(int Chunk, Coin coin, phy::Point p)
{
    coin.set_position(p);

    head_insert(Chunk, coin);
    this->Global_Entities++;
    this->Global_Coins++;
}

void Manager::head_insert(int Chunk, Enemy enemy)
{
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

void Manager::head_insert(int Chunk, Coin coin)
{
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

/* Da riguardare la meccanica di raccolta e uccisione */

// void Manager::kill_entity(int Chunk, Enemy enemy)
// {
//     pnemici tmp = this->Enemies[Chunk];
//     while (tmp != NULL || enemy.get_position() == tmp->val.get_position())
//         tmp->val.set_state(false);
//
//     this->Global_Enemies--;
//     this->Global_Entities--;
// }

void Manager::collect_coin(phy::Point player_position)
{
    pmonete tmp = this->Coins[this->current_chunk];
    while (tmp != NULL) {
        if(tmp->val.get_position() == player_position)
            tmp->val.make_collected();

        tmp = tmp->next;
    }

    this->Global_Coins--;
    this->Global_Entities--;
}

void Manager::make_player_shoot(phy::Point position, bool direction)
{
    position = position + (direction ? phy::Point(1, 0) : phy::Point(-1, 0));

    pbullets tmp = new bullets;
    tmp->val = Bullet("-", position, direction);
    tmp->next = this->Bullets;
    this->Bullets = tmp;
}

//time is in dec sec (sec*10^-1)
void Manager::move_entities(int& time)
{
    // Enemies
    if(time % 100 == 0) {
        pnemici tmp = this->Enemies[this->current_chunk];
        Chunk chunk = map.get_chunk(this->current_chunk);
        while(tmp != nullptr) {
            if(tmp->val.isItAlive()) {
                if(tmp->val.canMove(chunk)) {
                    if(tmp->val.get_direction()) 
                        tmp->val.set_position(tmp->val.get_position() + phy::Point(1,0));
                    else 
                        tmp->val.set_position(tmp->val.get_position() + phy::Point(-1,0));
                }
                else 
                    tmp->val.set_direction(!tmp->val.get_direction()); 
            }
            tmp = tmp->next;
        }
    } 

    // Bullets
    if(time % 25 == 0) {
        pbullets tmp = this->Bullets;

        while(tmp != nullptr) {
            phy::Point tmp_pos = tmp->val.get_position();
            tmp_pos = tmp_pos + (tmp->val.get_direction() ? phy::Point(1, 0) 
                    : phy::Point(-1, 0));
            tmp->val.set_position(tmp_pos);
            tmp = tmp->next;
        }

        //TODO: Delete bullets out of screen
    }
}

void Manager::draw_entities(Draw screen)
{
    pnemici p = this->Enemies[this->current_chunk];
    while(p != nullptr) {
        screen.drawEntity(p->val);
        p = p->next;
    }

    pmonete q = this->Coins[this->current_chunk];
    while(q != nullptr) {
        if(!q->val.is_collected())
            screen.drawEntity(q->val);

        q = q->next;
    }

    pbullets b = this->Bullets;
    while(b != nullptr) {
        screen.drawEntity(b->val);
        b = b->next;
    }
}


bool Manager::is_there_an_entity_in_platform(Map map, int Chunk, int plat)
{
    bool check = false;
    Platform platform = map.get_chunk(Chunk).get_platforms()[plat];

    int start = platform.get_position().get_xPosition();
    int end = platform.get_position().get_xPosition() + platform.get_length();
    pnemici p = get_all_enemies_in_chunk(Chunk);
    pmonete q = get_all_coins_in_chunk(Chunk);

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

bool Manager::is_there_an_entity_in_point(int Chunk, phy::Point point)
{
    bool check = false;

    pnemici p = get_all_enemies_in_chunk(Chunk);
    pmonete q = get_all_coins_in_chunk(Chunk);

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

pnemici Manager::get_all_enemies_in_chunk(int Chunk)
{
    pnemici p = this->Enemies[Chunk];
    return(p);
}

pmonete Manager::get_all_coins_in_chunk(int Chunk)
{
    pmonete p = this->Coins[Chunk];
    return(p);
}

nostd::vector<phy::Point> Manager::get_all_entities_positions_in_chunk(int Chunk)
{
    nostd::vector<phy::Point> v;
    pnemici p = this->Enemies[Chunk];
    pmonete q = this->Coins[Chunk];

    while (p != nullptr) {
        v.push_back(p->val.get_position());
        p = p->next;
    }

    while (q != nullptr) {
        v.push_back(q->val.get_position());
        q = q->next;
    }
    return(v);
}

pbullets Manager::delete_all_bullets(pbullets p)
{
    if(p != nullptr)
    {
        delete_all_bullets(p->next);
        delete p;
        p = nullptr;
    }
    return p;
}

//ONLY FOR DEBUGING
// void Manager::print_enemy_list()
// {
//     pnemici p = this->Enemies[this->current_chunk];
//     int c = 0;
//     while (p != nullptr) {
//         deb::debug(p->val.get_id(), "type");
//         deb::debug(p->val.get_position(), "current point");
//         p = p->next;
//         c++;
//     }
//     deb::debug(c, "number of enemies");
// }
