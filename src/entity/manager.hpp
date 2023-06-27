//#include "enemy.hpp"
//#include "coin.hpp"
#include "types.hpp"
#include "bullet.hpp"
#include "../../etc/nostd/vector.hpp"
#include "../draw/draw.hpp"
#include "../maps/map.hpp"
#include "../engine/random.hpp"

#include "../../etc/logs/logs.hpp"

#ifndef ENTITY_MANAGER
#define ENTITY_MANAGER

struct nemici
{
    Enemy val;
    nemici* next;
};
typedef nemici* pnemici;

struct monete
{
    Coin val;
    monete* next;
};
typedef monete* pmonete;

struct bullets
{
    Bullet val;
    bullets* next;
};
typedef bullets* pbullets;

class Manager
{
    private:
        Map map;
        Seed seed;
        int current_chunk;

        nostd::vector<pnemici> Enemies;
        nostd::vector<pmonete> Coins;
        pbullets Bullets;

        int Global_Entities;
        int Global_Enemies;
        int Global_Coins;

        void add_enemy(int Chunk, Enemy enemy, phy::Point p, bool dir);
        void add_coin(int Chunk, Coin coin, phy::Point p);
        void head_insert(int Chunk, Enemy enemy);
        void head_insert(int Chunk, Coin coin);
        pbullets clean_out_of_screen_bullets(pbullets p);
        pbullets delete_all_bullets(pbullets p);

    public:
        Manager(Map map);

        void set_chunk(int Chunk, Map map);
        // void kill_entity(int Chunk, Enemy enemy);
        void collect_coin(phy::Point player_position);
        void make_player_shoot(phy::Point position, bool direction);
        void move_entities(int& time);
        void draw_entities(Draw screen); //This method must be called afther set_chunk()

        bool is_there_an_entity_in_platform(Map map, int Chunk, int plat);
        bool is_there_an_entity_in_point(int Chunk, phy::Point point);
        pnemici get_all_enemies_in_chunk(int Chunk);
        pmonete get_all_coins_in_chunk(int Chunk);
        nostd::vector<phy::Point> get_all_entities_positions_in_chunk(int Chunk);

        //ONLY FOR DEBUGING
        // void print_enemy_list();
};
#endif
