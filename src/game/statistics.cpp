#include "statistics.hpp"

Statistics::Statistics(Draw screen){
	int posY, posX;
	screen.size(posY, posX, 44, 150);
	this->stats_scr = screen.newWindow(3, 150, posY - 2, posX);
	// in realtà deve prenderli dal file di salvataggio
	this->level = 0;
	this->jump = 0;
	this->coins = 0;
	this->heart = 10;
}

/*Statistics::~Statistics() {
    this->stats_scr.deleteWin();
}*/

void Statistics::initStats(Draw screen){

}

void Statistics::updateStats(){
	this->stats_scr.clearwithoutbox();

	this->stats_scr.drawRectagle(1, 0 , 3, 149);

	this->stats_scr.drawText(2, 2, "Lives: " );
	for (int i = 0; i < this->heart; i++)
	{
		this->stats_scr.drawText(2, 10 + i*2, "♥");
	}
	this->stats_scr.drawText(2, 50, "Level: " + nostd::to_string(this->level));
	this->stats_scr.drawText(2, 70, "Jump: " + nostd::to_string(this->jump));
	this->stats_scr.drawText(2, 90, "Coins: " + nostd::to_string(this->coins));
	this->stats_scr.refreshScreen();
}

void Statistics::deleteStats(){
	this->stats_scr.clearwithoutbox();
	this->stats_scr.refreshScreen();
	//this->stats_scr.deleteWin();
}

void Statistics::setLevel(int level){
    this->level = level;
}

void Statistics::setJump(int jump){
    this->jump = jump;
}

void Statistics::incrementJump(){
    this->jump++;
}

void Statistics::setCoins(int coins){
    this->coins = coins;
}

void Statistics::setHeart(int heart){
    this->heart = heart;
}

int Statistics::getLevel(){
    return this->level;
}

int Statistics::getJump(){
    return this->jump;
}

int Statistics::getCoins(){
    return this->coins;
}

int Statistics::getHeart(){
    return this->heart;
}

void Statistics::redraw(){
    this->stats_scr.redraw();
}

void Statistics::noOutRefresh(){
	this->stats_scr.noOutRefresh();
}
