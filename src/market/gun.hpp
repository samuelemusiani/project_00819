#include "../../etc/nostd/string.hpp"

#ifndef MARKET_GUN
#define MARKET_GUN

class Gun
{
    private:
        nostd::string _name;

        // We should probably point to a specific bullets type, but we don't
        // have the classes right now
        int _damage;
        int _price;

    public:
        Gun();
        Gun(nostd::string n);
        Gun(nostd::string n, int d);
        Gun(nostd::string n, int d, int p);

        nostd::string get_name();
        int get_damage();
        int get_price();
};

#endif
