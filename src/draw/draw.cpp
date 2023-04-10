#include "draw.hpp"

void Draw::drawText(int posY, int posX, std::string s) {
	mvwprintw(win, posY, posX, s.c_str());
}

void Draw::drawBox(){
	box(win, 0, 0);
}

void Draw::clearWindow() {
	wclear(win);
}

void Draw::attrOn(int c_pair) {
	wattron(win, COLOR_PAIR(c_pair));
}

void Draw::attrOff(int c_pair) {
	wattroff(win, COLOR_PAIR(c_pair));
}

//draw map
void Draw::drawMap(Map map, int nChunk) {
	//per adesso abbiamo solo il chunk 0
	std::vector<Platform> plat = *map.get_chunk(nChunk).get_platforms();
	this->drawPlatform(plat);
}

//draw a platform that display
void Draw::drawPlatform(std::vector<Platform> plat) {
	for(int i = 0; i < plat.size(); i++) {
		for(int j = 0; j < plat[i].get_length(); j++) {
			mvwprintw(win, plat[i].get_position().get_yPosition(), plat[i].get_position().get_xPosition()+j, "=");
		}
	}
}

void Draw::drawPlayer(phy::Point p) {
	mvwprintw(win, p.get_yPosition(), p.get_xPosition(), "@");
}

void Draw::drawSquare(std::string s, int posY, int posX) { //posizione del primo carattere
	this->drawText(3, 75 - s.length()/2, s);

	//calcolo della lunghezza della stringa
	int x = strlen(s.c_str());

	//le coordinate posX e posY indicano la posizione dell'angolo in alto a sx
	posX--;
	posY--;

	//questo ciclo disegna i bordi orizzontali
	for(int i = 0; i < x+1; i++) {
		mvwaddch(win, posY, posX+i, ACS_HLINE);
		mvwaddch(win, posY+2, posX+i, ACS_HLINE);
	}

	//questi due comandi disegnano i bordi verticali (assumendo che il testo sia alto 1 quadrato)
	mvwaddch(win, posY+1, posX, ACS_VLINE);
	mvwaddch(win, posY+1, posX+x+1, ACS_VLINE);

	//corners of the rectangle
	mvwaddch(win, posY, posX, ACS_ULCORNER);
	mvwaddch(win, posY+2, posX, ACS_LLCORNER);
	mvwaddch(win, posY, posX+x+1, ACS_URCORNER);
	mvwaddch(win, posY+2, posX+x+1, ACS_LRCORNER);

}
