#include "manager.hpp"

Manager::Manager (Map map)
    : Global_Entities(0), Global_Coins(0), Global_Enemies(0), 
        current_chunk(-1), Bullets(nullptr)
{
    this->map = map;
    this->seed = map.getSeed();
}

Manager::~Manager()
{
    for(int i = 0; i < this->Enemies.size(); i++)
    {
        list_enemies tmp = this->Enemies[i];

        while(tmp != nullptr)
        {
            list_enemies tmp2 = tmp->next;
            delete tmp; 
            tmp = tmp2;
        }
    }

    for(int i = 0; i < this->Coins.size(); i++)
    {
        list_coins tmp = this->Coins[i];

        while(tmp != nullptr)
        {
            list_coins tmp2 = tmp->next;
            delete tmp; 
            tmp = tmp2;
        }
    }

    while(this->Bullets != nullptr)
    {
        list_bullets tmp = this->Bullets->next;
        delete tmp; 
        this->Bullets = tmp;
    }
}

void Manager::set_chunk(int Chunk)
{
    // For semplicity all bullets outside the current chunk despawn
    if (this->current_chunk != Chunk)
        this->Bullets = this->delete_all_bullets(this->Bullets);

    while(this->current_chunk < Chunk && Enemies.size() < Chunk + 1) {
        this->current_chunk++;

        this->Enemies.push_back(nullptr);
        this->Coins.push_back(nullptr);

        int number_of_enemies = this->map.getEnemies(this->current_chunk);
        for(int i = 0; i < number_of_enemies; i++) {
            this->add_enemy(this->current_chunk, Enemy(
                    Random::generateEnemyType(this->seed, this->current_chunk, i) - 1, 
                    Random::generateEnemyPosition(this->map, this->current_chunk, 
                        this->get_all_entities_positions_in_chunk(this->current_chunk)), 
                            i % 2 == 0));
        }

        int number_of_coins = this->map.getCoins(this->current_chunk);
        for(int i = 0; i < number_of_coins; i++)
            this->add_coin(this->current_chunk, Coin(Random::generateCoinPosition(this->map, this->current_chunk, 
                            this->get_all_entities_positions_in_chunk(this->current_chunk))));
    }
    this->current_chunk = Chunk;
}

void Manager::add_enemy(int Chunk, Enemy enemy)
{
    head_insert(Chunk, enemy);
    this->Global_Entities++;
    this->Global_Enemies++;
}

void Manager::add_coin(int Chunk, Coin coin)
{
    head_insert(Chunk, coin);
    this->Global_Entities++;
    this->Global_Coins++;
}

void Manager::head_insert(int Chunk, Enemy enemy)
{
    if(this->Enemies[Chunk] == nullptr) {
        list_enemies p = new node_enemy;
        p->next = nullptr;
        p->val = enemy;
        this->Enemies[Chunk] = p;
    } else {
        list_enemies p = new node_enemy;
        p->next = this->Enemies[Chunk];
        p->val = enemy;
        this->Enemies[Chunk] = p;
    }
}

void Manager::head_insert(int Chunk, Coin coin)
{
    if(this->Coins[Chunk] == nullptr) {
        list_coins p = new node_coin;
        p->next = nullptr;
        p->val = coin;
        this->Coins[Chunk] = p;
    } else {
            list_coins p = new node_coin;
        p->next = this->Coins[Chunk];
        p->val = coin;
        this->Coins[Chunk] = p;
    }
}

int Manager::collect_coin(phy::Point player_position)
{
    bool collected_something = false;
    list_coins tmp = this->Coins[this->current_chunk];
    while (tmp != nullptr) {
        if(tmp->val.get_position() == player_position && 
                !tmp->val.is_collected())
        {
            tmp->val.make_collected();
            collected_something = true;
        }
        tmp = tmp->next;
    }

    this->Global_Coins--;
    this->Global_Entities--;

    return (collected_something ? 1 : 0);
}

void Manager::shoot(phy::Point position, bool direction, int type)
{
    position = position + (direction ? phy::Point(1, 0) : phy::Point(-1, 0));

    list_bullets tmp = new node_bullet;
    tmp->val = Bullet(position, direction, type);

    if(type == 1) 
        tmp->expiration = 10;

    tmp->next = this->Bullets;
    this->Bullets = tmp;
}

void Manager::update_entities(int time, phy::Body& player, Statistics& stats)
{
    /* Enemy 0: If the player body-hit it the the player take damage
     * Enemy 1: If the player is on his radious then he shoot at the player
     * Enemy 2: Follow the player and the explodes near him (like a creeper)
     */
    if(time % 100 == 0) {
        list_enemies tmp = this->Enemies[this->current_chunk];
        Chunk chunk = map.get_chunk(this->current_chunk);
        while(tmp != nullptr) {
            if(tmp->val.is_alive()) {
                if(tmp->val.get_type() == 0)
                {
                    if(tmp->val.can_move(chunk))
                        tmp->val.move();
                    else 
                        tmp->val.set_direction(!tmp->val.get_direction()); 


                    if(tmp->val.get_position() == player.get_position()) 
                        stats.incrementHearts(-1);
                }
                else if(tmp->val.get_type() == 1)
                {
                    const int SHOOTING_RADIOUS = 14;
                    phy::Point ppos = player.get_position();
                    phy::Point epos = tmp->val.get_position();

                    //the shooting for now is only orizzontal
                    int distance = epos.get_xPosition() - ppos.get_xPosition();
                    if(epos.get_yPosition() == ppos.get_yPosition() && 
                            abs(distance) <= SHOOTING_RADIOUS)
                    {
                            shoot(epos, distance < 0);
                    }
                    else
                    {
                        if(tmp->val.can_move(chunk))
                            tmp->val.move();
                        else 
                            tmp->val.set_direction(!tmp->val.get_direction()); 

                        if(tmp->val.get_position() == player.get_position()) 
                            stats.incrementHearts(-1);
                    }
                }
                else if(tmp->val.get_type() == 2)
                {
                    const int MOVING_RADIOUS = 24;
                    phy::Point ppos = player.get_position();
                    phy::Point epos = tmp->val.get_position();
                    int distance = epos.get_xPosition() - ppos.get_xPosition();

                    if(epos.get_yPosition() == ppos.get_yPosition() && 
                            distance <= MOVING_RADIOUS)
                    {
                        if(distance <= 3)
                        {
                            tmp->val.kill();
                            this->shoot(epos, true, 1);
                            this->shoot(epos, false, 1);
                        }
                        else
                        {
                            tmp->val.set_direction(distance < 0);

                            if(tmp->val.can_move(chunk))
                                tmp->val.move();
                        }
                    }
                    else
                    {
                        if(tmp->val.can_move(chunk))
                            tmp->val.move();
                        else 
                            tmp->val.set_direction(!tmp->val.get_direction()); 
                    }
                }
            }
            tmp = tmp->next;
        }
    } 

    if(time % 20 == 0) {
        list_bullets tmp = this->Bullets;

        while(tmp != nullptr) {
            phy::Point tmp_pos = tmp->val.get_position();
            tmp_pos = tmp_pos + (tmp->val.get_direction() ? phy::Point(1, 0) 
                    : phy::Point(-1, 0));
            tmp->val.set_position(tmp_pos);
            tmp->expiration--;
            tmp = tmp->next;
        }

        this->Bullets = bullets_collisions(this->Bullets, player, stats);
    }
}

list_bullets Manager::bullets_collisions(list_bullets p, phy::Body& player, Statistics& stats)
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
            list_enemies tmp = get_all_enemies_in_chunk(this->current_chunk);
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
        // Player collision
        if(pos == player.get_position()) {
            have_to_go = true;
            
            if(p->val.get_type() == 0)
                stats.incrementHearts(-1);
            else if(p->val.get_type() == 1)
                stats.incrementHearts(-2);
        }

        have_to_go |= p->expiration == 0;
        
        if(have_to_go) {
            list_bullets tmp = p->next;
            delete p;
            return this->bullets_collisions(tmp, player, stats);
        } 
        else {
            p->next = this->bullets_collisions(p->next, player, stats);
            return p;
        }
    }

    return p;
}

void Manager::draw_entities(Draw* screen)
{
    list_enemies p = this->Enemies[this->current_chunk];
    while(p != nullptr) {
        if(p->val.is_alive())
            screen->drawEntity(p->val);
        p = p->next;
    }

    list_coins q = this->Coins[this->current_chunk];
    while(q != nullptr) {
        if(!q->val.is_collected())
            screen->drawEntity(q->val);

        q = q->next;
    }

    list_bullets b = this->Bullets;
    while(b != nullptr) {
        screen->drawEntity(b->val);
        b = b->next;
    }
}


bool Manager::is_there_an_entity_in_platform(int Chunk, int plat)
{
    bool check = false;
    Platform platform = this->map.get_chunk(Chunk).get_platforms()[plat];

    int start = platform.get_position().get_xPosition();
    int end = platform.get_position().get_xPosition() + platform.get_length();
    list_enemies p = get_all_enemies_in_chunk(Chunk);
    list_coins q = get_all_coins_in_chunk(Chunk);

    while(p != nullptr && !check) {
        if(p->val.get_position().get_yPosition() == 
                platform.get_position().get_yPosition()) 
        {
            check = p->val.get_position().get_xPosition() >= start && 
                p->val.get_position().get_xPosition() <= end;
        }
        p = p->next;
    }

    while(q != nullptr && !check) {
        if(q->val.get_position().get_yPosition() == 
                platform.get_position().get_yPosition()) 
        {
            check = q->val.get_position().get_xPosition() >= start 
                && q->val.get_position().get_xPosition() <= end;
        }
        q = q->next;
    }

    return(check);
}

bool Manager::is_there_an_entity_in_point(int Chunk, phy::Point point)
{
    bool check = false;

    list_enemies p = get_all_enemies_in_chunk(Chunk);
    list_coins q = get_all_coins_in_chunk(Chunk);

    while(p != nullptr && !check) {
        if(p->val.get_position().get_yPosition() == point.get_yPosition() && 
                p->val.get_position().get_xPosition() == point.get_xPosition()) {
            check = true;
        }
        p = p->next;
    }

    while(q != nullptr && !check) {
        if(q->val.get_position().get_yPosition() == point.get_yPosition() && 
                q->val.get_position().get_xPosition() == point.get_xPosition()) {
            check = true;
        }
        q = q->next;
    }

    return(check);
}

list_enemies Manager::get_all_enemies_in_chunk(int Chunk)
{
    return this->Enemies[Chunk];
}

list_coins Manager::get_all_coins_in_chunk(int Chunk)
{
    return this->Coins[Chunk];
}

nostd::vector<phy::Point> Manager::get_all_entities_positions_in_chunk(int Chunk)
{
    nostd::vector<phy::Point> v;
    list_enemies p = this->Enemies[Chunk];
    list_coins q = this->Coins[Chunk];

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

list_bullets Manager::delete_all_bullets(list_bullets p)
{
    if(p != nullptr) {
        delete_all_bullets(p->next);
        delete p;
        p = nullptr;
    }
    return p;
}

/* All entities can be alive (1) or dead (0) so we use a bit (0 or 1) to tell 
 * if the entity is alive. For the coins alive means not collected by the player. 
 * Every time get_entities_status iterate through the Enemies and coins vector
 * and write who is alive.
 */

nostd::string Manager::get_entities_status()
{
    nostd::string save;
    //Enemies and Coins should have the same size
    for(int i = 0; i < this->Enemies.size(); i++)
    {
        list_enemies tmp = this->Enemies[i];
        while(tmp != nullptr)
        {
            if(tmp->val.is_alive())
                save.push_back('1');
            else
                save.push_back('0');

            tmp = tmp->next;
        }

        list_coins tmp2 = this->Coins[i];
        while(tmp2 != nullptr)
        {
            if(tmp2->val.is_collected())
                save.push_back('0');
            else
                save.push_back('1');

            tmp2 = tmp2->next;
        }
    }
    return save;
}

void Manager::set_entities_status(int number_of_chunks, nostd::string s)
{
    this->set_chunk(number_of_chunks);

    int global_index = 0;
    for(int i = 0; i < this->Enemies.size(); i++)
    {
        list_enemies tmp = this->Enemies[i];
        while(tmp != nullptr)
        {
            if(s[global_index] == '0')
                tmp->val.kill();

            tmp = tmp->next;
            global_index++;
        }

        list_coins tmp2 = this->Coins[i];
        while(tmp2 != nullptr)
        {
            if(s[global_index] == '0')
                tmp2->val.make_collected();

            tmp2 = tmp2->next;
            global_index++;
        }
    }
}
