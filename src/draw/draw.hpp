#include <ncurses.h>
#include "screen.hpp"
#include <string>


#ifndef DRAW_DRAW
#define DRAW_DRAW
class Draw : public Screen{
	private: 
	public:
		void drawText(int posY, int posX, std::string options);
		static void drawBox();
		static int centerX(std::string text);
		void drawSquare(std::string s, int posY, int posX);
};	

#endif