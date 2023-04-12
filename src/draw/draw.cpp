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

void Draw::drawSquare(std::string s, int posY, int posX) { //posizione del primo carattere
	this->drawText(posY, posX, s);

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
