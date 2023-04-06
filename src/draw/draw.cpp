#include "draw.hpp"
#include <cstring>


void Draw::drawText(int posY, int posX, std::string options) {
	mvwprintw(this->win, posY, posX, options.c_str());
}

void Draw::clearWindow() {
	wclear(this->screen);
}

void Draw::attrOn(int c_pair) {
	wattron(this->screen, COLOR_PAIR(c_pair));
}

void Draw::attrOff(int c_pair) {
	wattroff(this->screen, COLOR_PAIR(c_pair));
}

//implementazione della funzione box di ncurses non so se funziona
void Draw::drawBox(int ch1, int ch2) {
	box(this->screen, ch1, ch2);
}

//draw map (creato oggetto mappa)
void Draw::drawMap(Map map, int nChunck) {
	Chuck c = map.get_chunk();
	this->drawChunk(c);
}

void Draw::drawChunk(Chuck c) {
	//serve un metodo get_platforms() = platforms[] che devo disegnare con drawPlatform()
	Platform plat[] = c.get_platforms();
	for(int i = 0; i < plat.length; i++) {
		this->drawPlatform(plat[i]);
	}
}

//draw a platform that display
void Draw::drawPlatform(Platform plat) {
	for(int i = 0; i < plat.length; i++) {
		this->drawText(this->screen, plat.y_pos, plat.x_pox+i, "=");
	}
}

void Draw::drawPlayer(Point p) {
	this->drawText(this->screen, p.get_yPosition(), p.get_xPosition(), "@");
}
