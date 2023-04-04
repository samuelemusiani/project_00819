#include <ncurses.h>
#include "screen.hpp"
#include <string>

#ifndef DRAW_DRAW
#define DRAW_DRAW
class Draw : public Screen{
	private: 
	public:
		void drawText(int posY, int posX, std::string options);
};

#endif