#include <ncurses.h>

#ifndef DRAW_SCREEN 
#define DRAW_SCREEN

class Screen
{
    private:
        int max_x;
        int max_y;

    public:
        WINDOW *win;
        Screen();
        void init(); // Inzializza lo schermo e la WINDOW al centro del terminale
        int get_maxX();
        int get_maxY();

};

#endif