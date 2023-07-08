#ifndef GAME_HPP
#define GAME_HPP

#include <ncurses.h>

#include "statistics.hpp"
#include "settings.hpp"

#include "../draw/draw.hpp"
#include "../physics/body.hpp"
#include "../physics/point.hpp"
#include "../physics/vector.hpp"
#include "../entity/manager.hpp"


class Game
{
	private:
		Draw* screen;
		Map map;
		int current_chunk = 0;
		phy::Body player;
        Statistics stats;
        Settings settings;

#ifdef USE_HACK
		bool fly = false;
		void hack();
		int setCustom(Draw hack);
#endif

	public:
		Game();
		~Game();
		void run();
		void start();
		void play();
		void resume();
		bool exitGame();
        void over();

		// Funzione che chiede all'utente di scegliere la dificoltà e ritorna: 0 per facile, 1 per medio, 2 per difficile
		int setDifficulty();

		bool pauseGame(Draw* stats_scr, Statistics stats); 
};

#endif
