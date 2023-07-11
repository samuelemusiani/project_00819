#ifndef MARKET_GUN
#define MARKET_GUN

class Gun
{
    private:
        char _name[30];

        // We should probably point to a specific bullets type, but we don't
        // have the classes right now
        int _damage;

    public:
        Gun();
        Gun(const char* n);
        Gun(const char* n, int d);

        const char* get_name();
        int get_damage();
};

#endif
