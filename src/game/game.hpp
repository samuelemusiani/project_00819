#ifndef GAME_HPP
#define GAME_HPP

#include <ncurses.h>
#include "../draw/draw.hpp"
#include "../physics/body.hpp"
#include "../physics/point.hpp"
#include "../physics/vector.hpp"


class Game
{
	private:
		Draw screen;
		Draw stats_scr;
		int current_chunk;
		int jump = 0;
		int coins = 0;
		int heart = 10;
		Map map;
		phy::Body player;
		int current_chunk = 0;
	public:
		Game();
		~Game();
		void run();
		void start();
		void play();
		void resume();
		bool exitGame();

		// Funzione che chiede all'utente di scegliere la dificoltà e ritorna: 0 per facile, 1 per medio, 2 per difficile
		int setDifficulty();
		void stats();

		bool pauseGame();

};

#endif
