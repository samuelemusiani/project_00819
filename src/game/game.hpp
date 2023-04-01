#include <ncurses.h>
#include <fstream>


class Game
{
	private:
		void init();

	public:
		Game();
		~Game();
		void run();
		void credits();

};
