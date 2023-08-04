/*
 * Alma Mater Studiorum - University of Bologna
 * First cycle degree in Computer Science
 * Computer Programming - 00819
 *
 * Author: Argonni Emanuele #0001078626
 *
 * credits.hpp: Class that draws the credits
 * id selected from the menu
 */

#include "../draw/draw.hpp"
#include <ncurses.h>

class Credits {
private:
public:
  int drawCredits(Draw *screen);
  void openGithub(int developer);
};
