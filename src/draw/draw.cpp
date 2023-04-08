#include "draw.hpp"

void Draw::drawText(int posY, int posX, std::string s) {
	mvwprintw(this->screen, posY, posX, s.c_str());
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

//draw map
void Draw::drawMap(Map map, int nChunk) {
	nChunk = 0; //per adesso abbiamo solo il chunk 0
	std::vector<Platform> plat = *map.get_chunk(nChunk).get_platforms();
	this->drawPlatform(plat);
}

//draw a platform that display
void Draw::drawPlatform(std::vector<Platform> plat) {
	for(int i = 0; i < plat.size(); i++) {
		for(int j = 0; j < plat[i].get_length(); j++) {
			mvwprintw(this->screen, plat[i].get_position().get_yPosition(), plat[i].get_position().get_yPosition()+j, "=");
		}
	}
}

void Draw::drawPlayer(phy::Point p) {
	mvwprintw(this->screen, p.get_yPosition(), p.get_xPosition(), "@");
}

void Draw::centerX(std::string s, int posY, int posX) { //posizione del primo carattere
	this->drawText(3, 75 - s.length(), s);

	//calcolo della lunghezza della stringa
	int x = strlen(s.c_str());

	//le coordinate posX e posY indicano la posizione dell'angolo in alto a sx
	posX--;
	posY--;

	//questo ciclo disegna i bordi orizzontali
	for(int i = 0; i < x; i++) {
		mvwaddch(this->screen, posY, posX+i, 0);
		mvwaddch(this->screen, posY-2, posX+i, 0);
	}

	//questi due comandi disegnano i bordi verticali (assumendo che il testo sia alto 1 quadrato)
	mvwaddch(this->screen, posY+1, posX, 0);
	mvwaddch(this->screen, posY+1, posX+x+1, 0);

	//corners of the rectangle
	mvwaddch(this->screen, posY, posX, ACS_ULCORNER);
	mvwaddch(this->screen, posY+2, posX, ACS_LLCORNER);
	mvwaddch(this->screen, posY, posX+x+1, ACS_LLCORNER);
	mvwaddch(this->screen, posY+2, posX+x+1, ACS_LRCORNER);

}
