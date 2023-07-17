#include "../../etc/nostd/string.hpp"

#ifndef MARKET_GUN
#define MARKET_GUN

class Gun {
private:
  nostd::string _name;
  int _price;
  int _bullet_type;
  int _reloading_time;

public:
  Gun();
  Gun(nostd::string name, int price, int bullet_type, int reloading_time);

  nostd::string get_name();
  int get_price();
  int get_bullet_type();
  int get_reloading_time();
};

#endif
