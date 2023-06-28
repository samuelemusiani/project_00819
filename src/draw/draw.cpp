#include "draw.hpp"
#include <cstring>


void Draw::drawText(int posY, int posX, nostd::string s) {
	mvwprintw(this->screen, posY, posX, s.c_str());
}

void Draw::drawUpperText(int posY, int posX, nostd::string s) {
	for (int i = 0; i < s.length(); i++)
		mvwaddch(this->screen, posY, posX + i, s[i] + 'A' - 'a');
}

void Draw::drawText(int posY, int posX, const char s) {
	mvwaddch(this->screen, posY, posX, s);
}

void Draw::drawText(int posY, int posX, const char t[]) {
	mvwprintw(this->screen, posY, posX, t);
}

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
    phy::Point pos = entity.get_position();
	mvwprintw(this->screen, OFFSET - pos.get_yPosition(), pos.get_xPosition() + 1, "entity");
}

void Draw::drawEntity(Coin coin) {
    phy::Point pos = coin.get_position();
	mvwprintw(this->screen, OFFSET - pos.get_yPosition(), pos.get_xPosition() + 1, "$");
}

void Draw::drawEntity(Bullet bullet) {
    phy::Point pos = bullet.get_position();

    char symbol[2];
    symbol[1] = '\0';

    if(bullet.get_type() == 0)
        symbol[0] = '-';
    else if(bullet.get_type() == 1)
    {
        if(bullet.get_direction())
            symbol[0] = ')';
        else
            symbol[0] = '(';
    }
	mvwprintw(this->screen, OFFSET - pos.get_yPosition(), pos.get_xPosition() + 1, symbol);
}

void Draw::drawEntity(Enemy enemy) {
    phy::Point pos = enemy.get_position();

    char symbol[2] = {(char) ('0' + enemy.get_type()), '\0'};
	mvwprintw(this->screen, OFFSET - pos.get_yPosition(), pos.get_xPosition() + 1, symbol);
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

int Draw::centerX(const char* text){
	int x = 75 - (strlen(text) / 2);
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


int Draw::center(nostd::string t){
	return (t.length()/2);
}

Draw Draw::newSubWindow(int height, int width, int posY, int posX) {
	Draw d;
	d.setWin(derwin(this->screen, height, width, posY, posX));
	keypad(d.getScreen(), true);
	return d;
}

Draw Draw::newWindow(int height, int width, int posY, int posX) {
	Draw d;
	d.setWin(newwin(height, width, posY, posX));
	keypad(d.getScreen(), true);
	return d;
}

void Draw::setWin(WINDOW *win) {
	this->screen = win;
}
