#include "draw.hpp"

void Draw::drawText(int posY, int posX, std::string s) {
	mvprintw(posY, posX, s.c_str());
}

void Draw::clearWindow(WINDOW* win) {
	wclear(win);
}

void Draw::attribute_on(WINDOW* win, int attrs) {
	wattron(win, attrs);
}

void Draw::attribute_off(WINDOW* win, int attrs) {
	wattroff(win, attrs);
}
