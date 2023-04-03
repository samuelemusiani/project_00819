#include <ncurses.h>
#include <string>


class Draw {
	public:
		static void drawText(int posY, int posX, std::string options);
		static void clearWindow(WINDOW* win);
		static void attribute_on(WINDOW* win, int attrs);
		static void attribute_off(WINDOW* win, int attrs);
};
