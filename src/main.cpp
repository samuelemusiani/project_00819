<<<<<<< HEAD
#include "game/game.hpp"

int main()
{	
	Game game = Game();
	game.run();
=======
#include <ncurses.h>

int main()
{	
	initscr();			/* Start curses mode 		  */
	printw("Hello World !!!");	/* Print Hello World		  */
	refresh();			/* Print it on to the real screen */
	getch();			/* Wait for user input */
	endwin();			/* End curses mode		  */

>>>>>>> main
	return 0;
}
