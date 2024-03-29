/*
 * Alma Mater Studiorum - University of Bologna
 * First cycle degree in Computer Science
 * Computer Programming - 00819
 *
 * Author: Ayache Omar #0001068895
 *
 * screen.hpp: Class that hides ncurses
 * and implements basic screen operations
 */

#include <ncurses.h>

#ifndef DRAW_SCREEN
#define DRAW_SCREEN

#define SCREEN_HEIGHT 46
#define SCREEN_WIDTH 150

class Screen {
protected:
  WINDOW *screen;
  bool is_screen_deleted;

public:
  Screen(int height, int width, int posY, int posX);
  ~Screen();

  Screen(const Screen &other) = delete;
  Screen &operator=(const Screen &) = delete;

  void init();
  void clearScreen();
  void eraseScreen();
  void nodel(bool value);
  void refreshScreen();
  int getinput();
  void clearwithoutbox();

  // Delete the y line starting from the x column
  void clearLine(int y, int x);

  void deleteWin();
  void size(int &posY, int &posX, int offsetY, int offsetX);

  /* Copy information from the current window to the virtual screen. In
   * this way the terminal refreshes only when update() is called
   */
  void noOutRefresh();
  void redraw();

  /* Update the temrminal without causing flicker. If we use the classic
   * refresh, the amount of time from the update of two separate windos
   * would cause flicker as experienced
   * The functions is 'static' because it does not depend on a WINDOW but
   * is general, even if the screen is not inizialized
   */
  static void update(); // Why static??
};

#endif
