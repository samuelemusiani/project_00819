#include "draw.hpp"
#include <cstring>


void Draw::drawText(int posY, int posX, std::string options) {
	mvwprintw(win, posY, posX, options.c_str());
}

void Draw::drawBox(){
	box(win, 0, 0);
}

int Draw::centerX(std::string text){
	int x = strlen(text.c_str()) / 2;
	return x;
}

