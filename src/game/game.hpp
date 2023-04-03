#include <ncurses.h>


class Game
{
	private:
		void init();
		void credits();

	public:
		Game();
		~Game();
		void run();
};
