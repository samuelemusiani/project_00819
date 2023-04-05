#include "credits.hpp"
#include "../draw/screen.hpp"
#include <unistd.h>
#include <string.h>





/*Credits::~Credits()
{
}*/

void Credits::drawCredits(){
    // Clear the screen using the clearScreen function from screen.cpp that is non static
    // so we need to create an instance of Screen
    Screen screen;
    screen.clearScreen();
    Draw credits;
    // Create an animated text that moves from the top of the screen to the bottom of the screen
    // using the drawText function from draw.cpp and a for loop
    for(int i = 45; i > -2; i = i-1){

        screen.clearScreen();
        if(i - 6 > 0)
            credits.drawText(i - 6, 75 - (strlen("JumpKing Game")/2), "JumpKing Game");
	    if(i - 5 > 0)
            credits.drawText(i - 5, 75 - (strlen("Alma Mater Studiorum Bologna University: project-00819")/2), "Alma Mater Studiorum Bologna University: project-00819");
        if(i - 4 > 0)
            credits.drawText(i - 4, 75 - (strlen("This game has been developed")/2), "This game has been developed");
        if(i - 3 > 0)
            credits.drawText(i - 3, 75 - (strlen("in the year 2023 by")/2), "in the year 2023 by");
	    if(i - 2 > 0)
            credits.drawText(i - 2, 75 - (strlen("Argonni Emanuele, Musiani Samuele")/2),  "Argonni Emanuele, Musiani Samuele");
        if(i - 1 > 0)
            credits.drawText(i - 1, 75 - (strlen("Peronese Lorenzo, Ayache Omar")/2), "Peronese Lorenzo, Ayache Omar");
        if(i > 0)
            credits.drawText(i, 75 - (strlen("Hope you enjoy it!")/2), "Hope you enjoy it!");
        wrefresh(win);
        usleep(100000);
    }
    credits.drawText(22, 75 - 4, "Credits");
    
    

}
