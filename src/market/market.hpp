/*
 * Alma Mater Studiorum - University of Bologna
 * First cycle degree in Computer Science
 * Computer Programming - 00819
 *
 * Author: Ayache Omar #0001068895
 *
 * market.hpp: Class that implement
 * the game market
 */

#include "ability.hpp"
#include "gun.hpp"

#include "../game/statistics.hpp"

#ifndef MARKET_MARKET
#define MARKET_MARKET

const int MARKET_MAX_GUN = 4;
const int MARKET_MAX_ABILITY = 3;
const int MARKET_MAX_SUBMENUS = 3;

class Market {
private:
  int current_gun;
  int current_ability;
  int current_coins;
  int current_hearts;

  const nostd::string summenues[MARKET_MAX_SUBMENUS] = {"Guns", "Abilities",
                                                        "Health"};

  Gun all_guns[MARKET_MAX_GUN];
  bool guns_bought[MARKET_MAX_GUN];

  Ability all_abilities[MARKET_MAX_ABILITY];
  bool abilities_bought[MARKET_MAX_ABILITY];
  bool consumable_abilities[MARKET_MAX_ABILITY];
  nostd::string all_health[2];

  const nostd::string gun_art[6] = {
      "                           ______",
      "        |\\_______________ (_____\\______________",
      "HH======#H###############H#######################",
      "        ' ~\"\"\"\"\"\"\"\"\"\"\"\"\"\"`##(_))#H\\\"\"\"\"\"Y########",
      "                          ))    \\#H\\       `\"Y###",
      "                          \"      }#H)"};

  const nostd::string book_art[8] = {"(\\ ",
                                     "\\'\\ ",
                                     " \\'\\     __________  ",
                                     " / '|   ()_________)",
                                     " \\ '/    \\ ~~~~~~~~ \\",
                                     "   \\       \\ ~~~~~~   \\",
                                     "   ==).      \\__________\\",
                                     "  (__)       ()__________)"};

  const nostd::string poison_art[11] = {
      "     _____",        "    [IIIII]",       "     )\"\"\"(",
      "    /     \\",      "   /       \\",     "   |`-...-'|",
      "   |asprin |",      " _ |`-...-'j    _", "(\\)`-.___.(I) _(/)",
      "  (I)  (/)(I)(\\)", "     (I)        "

  };

  void set_current_gun();
  void set_current_ability();

  void draw();

public:
  Market();

  Gun get_current_gun();
  Ability get_current_ability();

  void make_ability_used();

  // The stats are for the hearts
  void open(Statistics &stats);

  nostd::string get_save();
  void set_save(nostd::string save);
};

#endif
