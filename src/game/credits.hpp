#include "../draw/draw.hpp"
#include <ncurses.h>

class Credits {
private:
public:
  int drawCredits(Draw *screen);
  void openGithub(int developer);
};
