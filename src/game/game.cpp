#include "game.hpp"

Game::Game()
{
	this->init();
}

Game::~Game()
{
	endwin();
}

void Game::run()
{
	//Menu::start();
}

bool Game::init()
{
	initscr();
}


