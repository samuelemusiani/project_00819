#include "draw.hpp"

void Draw::drawText(int posY, int posX, std::string options) {
	mvprintw(posY, posX, options.c_str());
}