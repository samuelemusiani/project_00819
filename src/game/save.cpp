#include "save.hpp"

void Save::saveGame(Draw screen){
    screen.clearScreen();
    screen.drawText(16, 65, "Insert the name of the file: ");
    screen.drawRectagle(19, 64, 2, 30);
    screen.refreshScreen();
    std::string nome;
    int ch;
    
    while ((ch = screen.getinput()) != 10) {

        if (ch == 127) { // backspace key
            if (!nome.empty()) {
                nome.pop_back();
                screen.eraseScreen();
                screen.drawText(16, 65, "Insert the name of the file: ");
                screen.drawRectagle(19, 64, 2, 30);
                screen.drawText(20, 66, nome.c_str());
                screen.refreshScreen();
            }
        } 
        else if (nome.length() == 27) {
            screen.clearLine(23, 0);
            screen.drawText(23, Draw::centerX("Max length reached"),  "Max length reached");
            screen.refreshScreen();
        }
        else {
            if (isalnum(ch) && ch != KEY_DOWN && ch != KEY_UP && ch != KEY_LEFT && ch != KEY_RIGHT || ch == 32){
                nome += ch;
                screen.drawText(20, 66, nome.c_str());
                screen.refreshScreen();
            }
            else 
                {screen.drawText(23, Draw::centerX("Only alphanumeric characters"),  "Only alphanumeric characters");}
        }

        if (nome.length() > 0 && nome.length() < 27) {
            screen.attrOn(COLOR_PAIR(1));
            screen.drawText(23, Draw::centerX("Press enter to confirm"), "Press enter to confirm");
            screen.attrOff(COLOR_PAIR(1));
            screen.refreshScreen();
        }
    }
     
}