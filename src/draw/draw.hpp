#include <ncurses.h>
#include "../maps/map.hpp"
#include "../maps/chunk.hpp"
#include "../maps/platform.hpp"
#include "../physics/point.hpp"
#include "screen.hpp"
#include <cstring>
#include <string>
#include <vector>


#ifndef DRAW_DRAW
#define DRAW_DRAW
class Draw : public Screen{
	private:
		void drawPlatform(std::vector<Platform> plat);
	public:
		void drawText(int posY, int posX, std::string s);
		void attrOff(int c_pair);
		void drawBox();
		void attrOn(int c_pair);
		void clearWindow();
		void drawMap(Map map, int nChunck);
		void drawPlayer(phy::Point p);
		void drawSquare(std::string s, int posY, int posX);

};

#endif
