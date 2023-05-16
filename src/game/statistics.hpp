#include "../draw/draw.hpp"
#include "game.hpp"

#ifndef STATISTICS_HPP
#define STATISTICS_HPP

class Statistics {
    private:
        int level = 0;
        int jump = 0;
        int coins = 0;
        int heart = 10;
        Draw stats_scr;
    public:
        Statistics(Draw screen);
       // ~Statistics();
        void updateStats();
        void initStats(Draw screen);
        void deleteStats();
        void setStats(int level, int jump, int coins, int heart);
        int getLevel();
        int getJump();
        int getCoins();
        int getHeart();
        void setLevel(int level);
        void setJump(int jump);
        void incrementJump();
        void setCoins(int coins);
        void setHeart(int heart);
        
        // Queste due funzioni andranno cambiate ma per ora servono per far funzionare Stats nel pause menu
        void redraw();
        void noOutRefresh();
};

#endif
