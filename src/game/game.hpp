#ifndef GAME_HPP
#define GAME_HPP

#include <ncurses.h>

#include "statistics.hpp"
#include "settings.hpp"

#include "../draw/draw.hpp"
#include "../physics/body.hpp"
#include "../physics/point.hpp"
#include "../physics/vector.hpp"
#include "../engine/manager.hpp"
#include "../market/market.hpp"


class Game
{
	private:
		Draw* screen;
        Settings settings;

#ifdef USE_HACK
		bool fly = false;
		void hack(int& current_chunk, Statistics& stats);
		int setCustom(Draw* hack);
#endif

        void play(Map& map, int& current_chunk, phy::Body& player, Statistics& stats, Manager& manager, Market& market);
        void resume();
        bool exitGame();
        void over();

        bool pauseGame(Map& map, int& current_chunk, phy::Body& player, 
                Statistics& stats, Manager& manager, Market& market); 

	public:
		Game();
		~Game();
		void run();
};

#endif
