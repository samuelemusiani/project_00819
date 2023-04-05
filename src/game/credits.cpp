#include "credits.hpp"
#include "../draw/screen.hpp"




/*Credits::~Credits()
{
}*/

void Credits::drawCredits(){
    // Clear the screen using the clearScreen function from screen.cpp that is non static
    // so we need to create an instance of Screen
    Screen clear;
    clear.clearScreen();
    Draw credits;
    credits.drawText(22, 75 - 4, "Credits");
    
    

}
