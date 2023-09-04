/*
 * Alma Mater Studiorum - University of Bologna
 * First cycle degree in Computer Science
 * Computer Programming - 00819
 *
 * Author: Ayache Omar #0001068895
 *
 * draw.hpp: Class to extend Screen and
 * implement all the methods needed in
 * order to draw on the screen
 */

#include <ncurses.h>

#include "screen.hpp"

#include "../entity/bullet.hpp"
#include "../entity/coin.hpp"
#include "../entity/enemy.hpp"
#include "../entity/entity.hpp"
#include "../game/statistics.hpp"
#include "../maps/chunk.hpp"
#include "../maps/map.hpp"
#include "../maps/platform.hpp"
#include "../physics/point.hpp"

#include "../../etc/nostd/string.hpp"
#include "../../etc/nostd/vector.hpp"

#define OFFSET 44 // SCREEN_HEIGHT - STATS_HEIGHT

#ifndef DRAW_DRAW
#define DRAW_DRAW

class Draw : public Screen {
private: 
  int playerColor = 0;
  void drawPlatform(nostd::vector<Platform> plat);

public:
  Draw(int height, int width, int posY = 0, int posX = 0);

  Draw(const Draw &other) = delete;
  Draw &operator=(const Draw &) = delete;

  void drawText(int posY, int posX, nostd::string s);
  void drawText(int posY, int posX, const char *s);
  void drawText(int posY, int posX, const char s);
  void drawCenterText(int posY, nostd::string s);
  void drawCenterText(int posY, const char *t);
  void drawUpperText(int posY, int posX, nostd::string s);
  void drawUpperText(int posY, int posX, const char s);
  void drawUpperText(int posY, int posX, const char *s);

  void attrOn(int c_pair);
  void attrOff(int c_pair);

  void drawBox();
  void drawSquareAround(nostd::string s, int posY, int posX);
  void drawSquareAround(const char s, int posY, int posX);
  void drawSquareAround(const char *s, int posY, int posX);
  void drawCenterSquareAround(nostd::string s, int posY);
  void drawRectagle(int posY, int posX, int length, int width);

  // Draw a vertical line in the x column delimited by y1 and y2
  void drawVerticalLine(int x, int y1, int y2);

  void drawMap(Map map, int nChunck);
  void drawPlayer(phy::Point p);
  void drawEntity(Entity entity);
  void drawEntity(Enemy enemy);
  void drawEntity(Coin coint);
  void drawEntity(Bullet bullet);

  void setPlayerColor(int color);
  void drawStats(Statistics stats);
  void deleteStats();
};
#endif
