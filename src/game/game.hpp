#include <ncurses.h>
#include <fstream>
#include <iostream>



class Game
{
	private:
		void init();

	public:
		Game();
		~Game();
		void doSelected(int x);
		void run();
		void credits();

};
