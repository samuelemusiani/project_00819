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

    if(this->current_chunk < Chunk && Enemies.size() < Chunk + 1) {
        this->Enemies.push_back(nullptr);
        this->Coins.push_back(nullptr);

        int number_of_enemies = map.getEnemies(Chunk);
        for(int i = 0; i < number_of_enemies; i++) {
            this->add_enemy(Chunk, 
                    EnemyType[Random::generateEnemyType(this->seed, Chunk, i) - 1], 
                    Random::generateEnemyPosition(map, Chunk, 
                        this->get_all_entities_positions_in_chunk(Chunk)), 
                            i % 2 == 0);
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
    if(this->Enemies[Chunk] == nullptr) {
        pnemici p = new nemici;
        p->next = nullptr;
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
    if(this->Coins[Chunk] == nullptr) {
        pmonete p = new monete;
        p->next = nullptr;
        p->val = coin;
        this->Coins[Chunk] = p;
    } else {
        pmonete p = new monete;
        p->next = this->Coins[Chunk];
        p->val = coin;
        this->Coins[Chunk] = p;
    }
}

void Manager::collect_coin(phy::Point player_position)
{
    pmonete tmp = this->Coins[this->current_chunk];
    while (tmp != nullptr) {
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

void Manager::move_entities(int& time)
{
    // Enemies
    if(time % 100 == 0) {
        pnemici tmp = this->Enemies[this->current_chunk];
        Chunk chunk = map.get_chunk(this->current_chunk);
        while(tmp != nullptr) {
            if(tmp->val.is_alive()) {
                if(tmp->val.can_move(chunk)) {
                    if(tmp->val.get_direction()) 
                        tmp->val.set_position(tmp->val.get_position() 
                                + phy::Point(1,0));
                    else 
                        tmp->val.set_position(tmp->val.get_position() 
                                + phy::Point(-1,0));
                }
                else 
                    tmp->val.set_direction(!tmp->val.get_direction()); 
            }
            tmp = tmp->next;
        }
    } 

    // Bullets
    if(time % 20 == 0) {
        pbullets tmp = this->Bullets;

        while(tmp != nullptr) {
            phy::Point tmp_pos = tmp->val.get_position();
            tmp_pos = tmp_pos + (tmp->val.get_direction() ? phy::Point(1, 0) 
                    : phy::Point(-1, 0));
            tmp->val.set_position(tmp_pos);
            tmp = tmp->next;
        }

        this->Bullets = bullets_collisions(this->Bullets);
    }
}

pbullets Manager::bullets_collisions(pbullets p)
{
    if(p != nullptr) {
        phy::Point pos = p->val.get_position();

        bool have_to_go = false;
       //Bullets out of screen
        have_to_go |= (pos.get_xPosition() < 0 || pos.get_xPosition() > 147);
        //Platform collision
        have_to_go |= this->map.get_chunk(this->current_chunk)
            .is_there_a_platform(pos);
        //EnemyEnemie collision
        {
            pnemici tmp = get_all_enemies_in_chunk(this->current_chunk);
            bool found = false;
            while(tmp != nullptr && !found) {
                if(tmp->val.get_position() == pos && tmp->val.is_alive()) {
                    tmp->val.kill();
                    found = true;
                }
                tmp = tmp->next;
            }

            have_to_go |= found;
        }
        
        if(have_to_go) {
            pbullets tmp = p->next;
            delete p;
            return this->bullets_collisions(tmp);
        } 
        else {
            p->next = this->bullets_collisions(p->next);
            return p;
        }
    }

    return p;
}

void Manager::draw_entities(Draw screen)
{
    pnemici p = this->Enemies[this->current_chunk];
    while(p != nullptr) {
        if(p->val.is_alive())
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

    while(p != nullptr && !check) {
        if(p->val.get_y() == platform.get_position().get_yPosition()) {
            if(p->val.get_x() >= start && p->val.get_x() <= end) {
                check = true;
            }
        }
        p = p->next;
    }

    while(q != nullptr && !check) {
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

    while(p != nullptr && !check) {
        if(p->val.get_y() == point.get_yPosition() && 
                p->val.get_x() == point.get_xPosition()) {
            check = true;
        }
        p = p->next;
    }

    while(q != nullptr && !check) {
        if(q->val.get_y() == point.get_yPosition() && 
                q->val.get_x() == point.get_xPosition()) {
            check = true;
        }
        q = q->next;
    }

    return(check);
}

pnemici Manager::get_all_enemies_in_chunk(int Chunk)
{
    return this->Enemies[Chunk];
}

pmonete Manager::get_all_coins_in_chunk(int Chunk)
{
    return this->Coins[Chunk];
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
    return v;
}

pbullets Manager::delete_all_bullets(pbullets p)
{
    if(p != nullptr) {
        delete_all_bullets(p->next);
        delete p;
        p = nullptr;
    }
    return p;
}
