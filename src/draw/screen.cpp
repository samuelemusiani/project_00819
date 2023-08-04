#include "screen.hpp"
#include <locale.h>
#include <unistd.h>

#include "../../etc/logs/logs.hpp"

Screen::Screen(int height, int width, int posY, int posX)
    : is_screen_deleted(false) {
  this->init();

  if (LINES < 48 || COLS < 150) {
    printw("Your terminal is too small. Please resize it at least to 44x150");
    mvprintw(1, 0,
             "Please resize your terminal window or reduce the size with Ctrl- "
             "or CMD-");
    while (LINES < 48 || COLS < 150) {
      refresh();
      sleep(1); // attendo 1 secondo per non mandare la cpu a 100%
    }
  }
  int tmp_posY, tmp_posX;
  this->size(tmp_posY, tmp_posX, height, width);

  tmp_posY += -posY;
  tmp_posX += posX;

  this->screen = newwin(height, width, tmp_posY, tmp_posX);
  keypad(this->screen, true);
  set_escdelay(1);
  // Setto il background nero
  wbkgd(this->screen, COLOR_BLACK);
  wrefresh(this->screen);
}

Screen::~Screen() {
  if (!is_screen_deleted)
    delwin(this->screen);
  endwin();
}

void Screen::init() {
  setlocale(LC_ALL, "");
  initscr();
  start_color();
  cbreak();
  noecho();
  curs_set(0);
  start_color();
  // Ridefinisco il colore nero a 0,0,0 per alcuni terminali che mostrano un
  // colore diverso
  init_color(COLOR_BLACK, 0, 0, 0);
}

void Screen::clearScreen() {
  wclear(this->screen);
  box(this->screen, 0, 0);
}

void Screen::eraseScreen() {
  werase(this->screen);
  box(this->screen, 0, 0);
}

void Screen::nodel(bool value) { nodelay(this->screen, value); }

void Screen::refreshScreen() { wrefresh(this->screen); }

int Screen::getinput() { return wgetch(this->screen); }

void Screen::clearwithoutbox() { werase(this->screen); }

void Screen::clearLine(int y, int x) {
  wmove(this->screen, y, x);
  wrefresh(this->screen);
  wclrtoeol(this->screen);
  box(this->screen, 0, 0);
}

void Screen::deleteWin() {
  if (!is_screen_deleted)
    delwin(this->screen);

  is_screen_deleted = true;
}

void Screen::size(int &posY, int &posX, int offsetY, int offsetX) {
  int xMaxSize, yMaxSize;
  getmaxyx(stdscr, yMaxSize, xMaxSize);
  posY = ((yMaxSize - offsetY) / 2);
  posX = (xMaxSize - offsetX) / 2;
}

void Screen::noOutRefresh() { wnoutrefresh(this->screen); }

void Screen::redraw() { redrawwin(this->screen); }

void Screen::update() { doupdate(); }
