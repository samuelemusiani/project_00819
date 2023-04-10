#ifndef GAME_HPP
#define GAME_HPP

#include <ncurses.h>
#include "../draw/draw.hpp"
#include "menu.hpp"



class Game
{
	private:
		Draw screen;
	public:
		Game();
		~Game();
		void run();
		void start();
		void resume();

};


#endif
