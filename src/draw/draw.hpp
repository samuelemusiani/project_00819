#include <ncurses.h>
#include "../maps/map.hpp"
#include "../maps/chunk.hpp"
#include "../maps/platform.hpp"
#include "../physics/point.hpp"
#include "screen.hpp"
#include "../../etc/nostd/vector.hpp"
#include "../../etc/nostd/string.hpp"

#define OFFSET 42

#ifndef DRAW_DRAW
#define DRAW_DRAW

class Draw : public Screen{
	private:
		void drawPlatform(nostd::vector<Platform> &plat);
		
	public:
		void drawText(int posY, int posX, nostd::string s);
		void drawText(int posY, int posX, std::string s);
		void drawText(int posY, int posX, const char t[]);
		void drawText(int posY, int posX, const char s);
		void drawUpperText(int posY, int posX, std::string s);
		void attrOff(int c_pair);
		void drawBox();
		void attrOn(int c_pair);
		void clearWindow();
		void drawMap(Map map, int nChunck);
		void drawPlayer(phy::Point p);
		void drawSquareAround(std::string s, int posY, int posX);
		static int centerX(nostd::string text);
		void drawRectagle(int posY, int posX, int length, int width);
		int center(nostd::string t);
		Draw newSubWindow(int height, int width, int posY, int posX);
		Draw newWindow(int height, int width, int posY, int posX);
		void setWin(WINDOW *win);
		
};
#endif
