#include "draw.hpp"
#include <cstring>

Draw::Draw(int height, int width, int posY, int posX)
    : Screen(height, width, posY, posX)
{

}

void Draw::drawText(int posY, int posX, nostd::string s) {
	mvwprintw(this->screen, posY, posX, "%s", s.c_str());
}


void Draw::drawText(int posY, int posX, const char* s) {
    mvwprintw(this->screen, posY, posX, "%s", s);
}

void Draw::drawText(int posY, int posX, const char s) {
	mvwaddch(this->screen, posY, posX, s);
}

void Draw::drawCenterText(int posY, nostd::string s) {
	mvwprintw(this->screen, posY, this->centerX(s), "%s", s.c_str());
}


void Draw::drawCenterText(int posY, const char* s) {
    mvwprintw(this->screen, posY, this->centerX(s), "%s", s);
}

void Draw::drawUpperText(int posY, int posX, nostd::string s) {
    this->drawUpperText(posY, posX, s.c_str());
}

void Draw::drawUpperText(int posY, int posX, const char s) {
        mvwaddch(this->screen, posY, posX, s + 'A' - 'a');
}

void Draw::drawUpperText(int posY, int posX, const char* s) {
    int l = strlen(s);
    for (int i = 0; i < l; i++)
        mvwaddch(this->screen, posY, posX + i, s[i] + 'A' - 'a');
}

void Draw::attrOn(int c_pair) {
    wattron(this->screen, c_pair);
}

void Draw::attrOff(int c_pair) {
    wattroff(this->screen, c_pair);
}

void Draw::drawBox(){
	box(this->screen, 0, 0);
}

void Draw::drawSquareAround(nostd::string s, int posY, int posX)
{
    this->drawSquareAround(s.c_str(), posY, posX);
}

void Draw::drawSquareAround(const char s, int posY, int posX)
{
    char tmp[2] = "a";
    tmp[0] = s;
    this->drawSquareAround(tmp, posY, posX);
}
                                                                 //
void Draw::drawSquareAround(const char* s, int posY, int posX) { //posizione del primo carattere
	this->drawText(posY, posX, s);

	//calcolo della lunghezza della stringa
	int x = strlen(s);

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

void Draw::drawCenterSquareAround(nostd::string s, int posY) {
    int posX = this->centerX(s);
    this->drawSquareAround(s, posY, this->centerX(s));
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

void Draw::drawVerticalLine(int x, int y1, int y2)
{
	for (int i = y1; i < y2; i++)
	{
		mvwaddch(this->screen, i, x, ACS_VLINE);
	}
}

int Draw::center(nostd::string t){
	return (t.length()/2);
}

void Draw::drawMap(Map map, int nChunk) {
	this->drawPlatform(map.get_chunk(nChunk).get_platforms());
}

void Draw::drawPlayer(phy::Point p) {
	mvwprintw(this->screen, OFFSET - p.get_yPosition(), p.get_xPosition() + 1, "@");
}

void Draw::drawEntity(Entity entity) {
    phy::Point pos = entity.get_position();
	mvwprintw(this->screen, OFFSET - pos.get_yPosition(), pos.get_xPosition() + 1, "entity");
}

void Draw::drawEntity(Enemy enemy) {
    phy::Point pos = enemy.get_position();

    char symbol[2] = {(char) ('0' + enemy.get_type()), '\0'};
	mvwprintw(this->screen, OFFSET - pos.get_yPosition(), pos.get_xPosition() + 1, "%s", symbol);
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
	mvwprintw(this->screen, OFFSET - pos.get_yPosition(), pos.get_xPosition() + 1, "%s", symbol);
}

void Draw::updateStats(Statistics stats) {
    this->clearwithoutbox();

    drawRectagle(1, 0 , 3, 149);
    drawText(2, 2, "Lives: " );

    for (int i = 0; i < stats.getHearts(); i++) {
        drawText(2, 10 + i*2, "♥");
    }
    drawText(2, 50, "Level: " + nostd::to_string(stats.getLevel()));
    drawText(2, 70, "Jump: " + nostd::to_string(stats.getJumps()));
    drawText(2, 90, "Coins: " + nostd::to_string(stats.getCoins()));
    refreshScreen();
}

void Draw::deleteStats() {
	clearwithoutbox();
	refreshScreen();
}

void Draw::drawPlatform(nostd::vector<Platform> plat) {
    for(int i = 0; i < plat.size(); i++) {
        for(int j = 0; j < plat[i].get_length(); j++) {
            mvwprintw(this->screen, OFFSET-plat[i].get_position().get_yPosition(), 
                    plat[i].get_position().get_xPosition()+j+1, "=");
        }
    }
}

int Draw::centerX(nostd::string text){
	int x = 75 - (strlen(text.c_str()) / 2);
	return x;
}

int Draw::centerX(const char* text){
	int x = 75 - (strlen(text) / 2);
	return x;
}

