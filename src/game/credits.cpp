#include "credits.hpp"
#include "../draw/screen.hpp"
#include <string.h>




/*Credits::~Credits()
{
}*/

int Credits::drawCredits(){
    // Clear the screen using the clearScreen function from screen.cpp that is non static
    // so we need to create an instance of Screen
    Screen screen;
    screen.clearScreen();
    Draw credits;
    // Create an animated text that moves from the top of the screen to the bottom of the screen
    // using the drawText function from draw.cpp and a for loop
    // Implementare con l'array
            
    
    std::string developers[4] = {"@SuperMitic", "@musianisamuele", "@lorenzoperonese", "@Jabbar03"};
    int selectedOption = 0;
    bool selected = false; 
    nodelay(win, TRUE);

    for(int i = 45; i > -2 && !selected; i = i-1) {
        for(int j = 0; j < 10 && !selected; j++) {
        
            screen.clearScreen();
            credits.drawText(8, 20 - (strlen("Who we are?")/2), "Who we are?");

            // for loop to draw the developers
            for(int j = 0; j < 4; j++){
                credits.drawText(10 + 2*j, 20 - (developers[j].length()/2), developers[j]);
            }

            wattron(win, A_UNDERLINE);
            credits.drawText(10 + 2*selectedOption, 20 - (developers[selectedOption].length()/2), developers[selectedOption]);
            wattroff(win, A_UNDERLINE);

            switch (wgetch(win)) {
                case KEY_UP:
                    if (selectedOption > 0) {
                        selectedOption--;
                    }
                    else if (selectedOption == 0) {
                        selectedOption = 4 - 1;
                    }
                    break;
                case KEY_DOWN:
                    if (selectedOption < 4 - 1) {
                        selectedOption++; 
                    }
                    else if (selectedOption == 4 - 1) {
                        selectedOption = 0;
                    }
                    break;
                case 27:
                    selectedOption = -1;
                    selected = true; 
                    break;
                case 10: 
                    selected = true; 
                    break;
                
            }




            // IMPLEMENTARE CON L'ARRAY


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
            napms(300/10);
        }
    }
    
    nodelay(win, FALSE);

    // stampa selectedOption per debug 
    credits.drawText(1, 1, std::to_string(selectedOption));
    
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

