#include <ncurses.h>
#include "../draw/draw.hpp"

class Game
{
	private:
		Draw screen;
	public:
		Game();
		~Game();
		void run();
};
