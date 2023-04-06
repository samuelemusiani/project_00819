#include <ncurses.h>
#include "../maps/map.hpp"
#include "../maps/chunk.hpp"
#include "../maps/platform.hpp"
#include "../physics/point.hpp"
#include "screen.hpp"
#include <string>


#ifndef DRAW_DRAW
#define DRAW_DRAW
class Draw : public Screen{
	private:
		void drawChunk(Chuck c);
		void drawPlatform(Platform plat);
	public:
		void drawText(int posY, int posX, std::string options);
		void clearWindow();
		void drawMap(Map map, int nChunck);
		void drawPlayer(Point p);

};

#endif
