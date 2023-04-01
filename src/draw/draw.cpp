#include "draw.hpp"

void Draw::drawText(int posY, int posX, std::string s) {
	mvprintw(posY, posX, s.c_str());
}
