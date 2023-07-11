#ifndef MARKET_ABILITY
#define MARKET_ABILITY

class Ability
{
    private:
        char _name[30];

    public:
        Ability();
        Ability(const char* n);

        const char* get_name();
};

#endif
