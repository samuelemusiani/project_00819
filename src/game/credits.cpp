#include "credits.hpp"
#include <string.h>



int Credits::drawCredits(Draw* screen){

	screen->clearScreen();	
	
	nostd::string developers[4] = {"@SuperMitic", "@musianisamuele", "@lorenzoperonese", "@Jabbar03"};
	nostd::string creditstext[6] = {"JumpKing Game", "Alma Mater Studiorum Bologna University: project-00819", "This game has been developed", "in the year 2023 by", "Argonni Emanuele, Musiani Samuele", "Peronese Lorenzo, Ayache Omar"};
	int selectedOption = 0;
	bool selected = false; 
	screen->nodel(true);

	const int TIME_UPDATE_CREDITS = 100;
	int CYCLES = 0;
	bool NEED_TO_REDRAW = true;

	for(int i = 42; i > -6 && !selected; i = i-1) {
		if (i == -5) i = 42;

		screen->eraseScreen();
	
		screen->drawText(8, 15, "Who we are?");

		// for loop to draw the developers
		for(int j = 0; j < 4; j++){
			screen->drawText(10 + 2*j, 20 - (developers[j].length()/2), developers[j]);
		}

		if(!NEED_TO_REDRAW) i++;

		//for loop to draw the credits
		for (int j = 0; j < 6; j++){
			if(i + j > 0 && i + j < 43)
				screen->drawCenterText(i + j, creditstext[j]);
		}

		bool EXIT = false;
		
		screen->attrOn(A_UNDERLINE);
		screen->drawText(10 + 2*selectedOption, 20 - (developers[selectedOption].length()/2), developers[selectedOption]);
		screen->attrOff(A_UNDERLINE);

		screen->refreshScreen();
		NEED_TO_REDRAW = false;

		for(int j = 0; j < 50 && !selected && !EXIT; j++) {

			napms(20);
			CYCLES++;

			if(CYCLES == 40)
			{
				NEED_TO_REDRAW = true;
				CYCLES = 0;
				break;
			}
			
			switch (screen->getinput()) {
				case KEY_UP:
					if (selectedOption > 0) {
						selectedOption--;
					}
					else if (selectedOption == 0) {
						selectedOption = 4 - 1;
					}
					EXIT = true;
					break;
				case KEY_DOWN:
					if (selectedOption < 4 - 1) {
						selectedOption++; 
					}
					else if (selectedOption == 4 - 1) {
						selectedOption = 0;
					}
					EXIT = true;
					break;
				case 27:
					selectedOption = -1;
					selected = true; 
					break;
				case 10: 
					selected = true; 
					break;
				default:
					break;
			}
		}
		   
		
	}
	
	return selectedOption;

}

void Credits::openGithub(int developer){
	switch(developer){
		case 0:
			#ifdef __APPLE__
				system("open https://github.com/SuperMitic");
			#elif __linux__
				system("xdg-open https://github.com/SuperMitic");
			#endif
			break;
		case 1:
			#ifdef __APPLE__
				system("open https://github.com/musianisamuele");
			#elif __linux__
				system("xdg-open https://github.com/musianisamuele");
			#endif
			break;
		case 2:
			#ifdef __APPLE__
				system("open https://github.com/lorenzoperonese");
			#elif __linux__
				system("xdg-open https://github.com/lorenzoperonese");
			#endif
			break;
		case 3:
			#ifdef __APPLE__
				system("open https://github.com/Jabbar03");
			#elif __linux__
				system("xdg-open https://github.com/Jabbar03");
			#endif
			break;
		default:
			break;
	}   
}
