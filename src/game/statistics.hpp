#ifndef STATISTICS_HPP
#define STATISTICS_HPP

class Statistics {
    private:
        int _level = 0;
        int _jump = 0;
        int _coins = 0;
        int _heart = 10;
    public:
        Statistics();
        Statistics(int level, int coins, int jump, int heart);

        void setLevel(int level);
        void setCoins(int coins);
        void setJumps(int jump);
        void setHearts(int heart);

        int getLevel();
        int getCoins();
        int getJumps();
        int getHearts();

        void incrementJumps(int delta = 1);
        void incrementCoins(int delta = 1);
        void incrementLevel(int delta = 1);
        void incrementHearts(int delta = 1);
};

#endif
