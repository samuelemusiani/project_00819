#include <ncurses.h>
#include <string>


class Draw {
    public:
        static void drawText(int posY, int posX, std::string options);
};
