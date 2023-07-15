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
#include "../market/market.hpp"


class Game
{
	private:
		Draw* screen;
        Settings settings;
        Market market;

#ifdef USE_HACK
		bool fly = false;
		void hack(int& current_chunk, Statistics& stats);
		int setCustom(Draw* hack);
#endif

	public:
		Game();
		~Game();
		void run();
		void play(Map& map, int& current_chunk, phy::Body& player, Statistics& stats, Manager& manager, Market& market);
		void resume();
		bool exitGame();
        void over();

		// Funzione che chiede all'utente di scegliere la dificoltà e ritorna: 0 per facile, 1 per medio, 2 per difficile
		int setDifficulty();

		bool pauseGame(Map& map, int& current_chunk, 
                phy::Body& player, Statistics& stats, Manager& manager); 
};

#endif
