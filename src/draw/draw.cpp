#include "draw.hpp"
#include <cstring>


void Draw::drawText(int posY, int posX, nostd::string s) {
	mvwprintw(this->screen, posY, posX, s.c_str());
}

void Draw::drawText(int posY, int posX, std::string s) {
	mvwprintw(this->screen, posY, posX, s.c_str());
}

void Draw::drawText(int posY, int posX, const char t[]) {
	mvwprintw(this->screen, posY, posX, t);
}

//DA TOGLIERE SE NON SERVE PERCHE' CHAR* DOVREBBE ESSERE QUELLA SOPRA
/*void Draw::drawText(int posY, int posX, const char* t) {
	mvwprintw(this->screen, posY, posX, t);
}*/

void Draw::drawBox(){
	box(this->screen, 0, 0);
}

void Draw::attrOn(int c_pair) {
	wattron(this->screen, c_pair);
}

void Draw::attrOff(int c_pair) {
	wattroff(this->screen, c_pair);
}
//draw map
void Draw::drawMap(Map map, int nChunk) {
	//per adesso abbiamo solo il chunk 0
	this->drawPlatform(map.get_chunk(nChunk).get_platforms());
}

//draw a platform that display
void Draw::drawPlatform(nostd::vector<Platform> plat) {
	for(int i = 0; i < plat.size(); i++) {
		for(int j = 0; j < plat[i].get_length(); j++) {
			mvwprintw(this->screen, OFFSET-plat[i].get_position().get_yPosition(), plat[i].get_position().get_xPosition()+j+1, "=");
		}
	}
}

void Draw::drawPlayer(phy::Point p) {
	mvwprintw(this->screen, OFFSET - p.get_yPosition(), p.get_xPosition() + 1, "@");
}

void Draw::drawEntity(Entity entity) {
	this->drawText(OFFSET - entity.get_y(), entity.get_x(), std::to_string(entity.get_id()).c_str());
}


void Draw::drawSquareAround(nostd::string s, int posY, int posX) { //posizione del primo carattere
	this->drawText(posY, posX, s);

	//calcolo della lunghezza della stringa
	int x = strlen(s.c_str());

	//le coordinate posX e posY indicano la posizione dell'angolo in alto a sx
	posX--;
	posY--;

	//questo ciclo disegna i bordi orizzontali
	for(int i = 0; i < x+1; i++) {
		mvwaddch(this->screen, posY, posX+i, ACS_HLINE);
		mvwaddch(this->screen, posY+2, posX+i, ACS_HLINE);
	}

	//questi due comandi disegnano i bordi verticali (assumendo che il testo sia alto 1 quadrato)
	mvwaddch(this->screen, posY+1, posX, ACS_VLINE);
	mvwaddch(this->screen, posY+1, posX+x+1, ACS_VLINE);

	//corners of the rectangle
	mvwaddch(this->screen, posY, posX, ACS_ULCORNER);
	mvwaddch(this->screen, posY+2, posX, ACS_LLCORNER);
	mvwaddch(this->screen, posY, posX+x+1, ACS_URCORNER);
	mvwaddch(this->screen, posY+2, posX+x+1, ACS_LRCORNER);

}


int Draw::centerX(nostd::string text){
	int x = 75 - (strlen(text.c_str()) / 2);
	return x;
}

void Draw::drawRectagle(int posY, int posX, int length, int width) {
	for(int i = 0; i < length; i++) {
		mvwaddch(this->screen, posY+i, posX, ACS_VLINE);
		mvwaddch(this->screen, posY+i, posX+width, ACS_VLINE);
	}
	for(int i = 0; i < width; i++) {
		mvwaddch(this->screen, posY, posX+i, ACS_HLINE);
		mvwaddch(this->screen, posY+length, posX+i, ACS_HLINE);
	}
	//corners of the rectangle
	mvwaddch(this->screen, posY, posX, ACS_ULCORNER);
	mvwaddch(this->screen, posY+length, posX, ACS_LLCORNER);
	mvwaddch(this->screen, posY, posX+width, ACS_URCORNER);
	mvwaddch(this->screen, posY+length, posX+width, ACS_LRCORNER);
}

