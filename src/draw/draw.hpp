#include <ncurses.h>

#include "screen.hpp"

#include "../game/statistics.hpp"
#include "../maps/map.hpp"
#include "../maps/chunk.hpp"
#include "../maps/platform.hpp"
#include "../physics/point.hpp"
#include "../entity/entity.hpp"
#include "../entity/enemy.hpp"
#include "../entity/coin.hpp"
#include "../entity/bullet.hpp"

#include "../../etc/nostd/vector.hpp"
#include "../../etc/nostd/string.hpp"


#define OFFSET 42

#ifndef DRAW_DRAW
#define DRAW_DRAW

class Draw : public Screen{
	private:
		void drawPlatform(nostd::vector<Platform> plat);

        int centerX(nostd::string text);
        int centerX(const char* text);

	public:
		void drawText(int posY, int posX, nostd::string s);
		void drawText(int posY, int posX, const char* s);
		void drawText(int posY, int posX, const char s);
		void drawCenterText(int posY, nostd::string s);
		void drawCenterText(int posY, const char* t);
		void drawUpperText(int posY, int posX, nostd::string s);

        void attrOn(int c_pair);
		void attrOff(int c_pair);

		void drawBox();
		void drawSquareAround(nostd::string s, int posY, int posX);
        void drawCenterSquareAround(nostd::string s, int posY);
		void drawRectagle(int posY, int posX, int length, int width);

        // Draw a vertical line in the x column delimited by y1 and y2
		void drawVerticalLine(int x, int y1, int y2);

        // I think this function can be deleted
		int center(nostd::string t);

		void drawMap(Map map, int nChunck);
		void drawPlayer(phy::Point p);
		void drawEntity(Entity entity);
		void drawEntity(Enemy enemy);
		void drawEntity(Coin coint);
		void drawEntity(Bullet bullet);

        void updateStats(Statistics stats);
        void deleteStats();

        // I dont't like this way of generation a new win. We should make a new
        // Draw object and the constructor would take care of everything
		Draw newSubWindow(int height, int width, int posY, int posX);
		Draw newWindow(int height, int width, int posY, int posX);
		void setWin(WINDOW *win);
};
#endif
