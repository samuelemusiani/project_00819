#include "draw.hpp"

void Draw::drawText(int posY, int posX, std::string options) {
	mvwprintw(this->win, posY, posX, options.c_str());
}