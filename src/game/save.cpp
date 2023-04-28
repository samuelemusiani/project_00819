#include "save.hpp"

void Save::saveNewGame(Draw screen, Map map, int chunk, phy::Point PlayerPos){
    if (File::isAlreadySaved(map)) {
        saveGame(screen);
    }
    else {
    screen.eraseScreen();
    screen.drawText(16, 65, "Insert the name of the file: ");
    screen.drawRectagle(19, 64, 2, 30);
    screen.refreshScreen();
    int ch;
    bool saved = false; 
    while (!saved) {
        ch = screen.getinput();
        if (ch == 127 || ch == KEY_BACKSPACE) { // 127 on mac, KEY_BACKSPACE on linux
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
        else if (nome.empty() == true && ch == 10) {
            screen.clearLine(23, 0);
            screen.drawText(23, Draw::centerX("Insert a name"),  "Insert a name");
            screen.refreshScreen();
        }
        else {
            if (isalnum(ch) && ch != KEY_DOWN && ch != KEY_UP && ch != KEY_LEFT && ch != KEY_RIGHT || ch == 32 ){ // 32 = space
                nome += ch;
                screen.drawText(20, 66, nome.c_str());
                screen.refreshScreen();
            }
            else 
                {   
                    screen.clearLine(23, 0);
                    screen.drawText(23, Draw::centerX("Only alphanumeric characters"),  "Only alphanumeric characters");
                    screen.refreshScreen();
                    }
        }

        if (nome.length() > 0 && nome.length() < 27) {
            
            if (isalnum(ch)){
                screen.clearLine(23, 0);
                screen.attrOn(COLOR_PAIR(1));
                screen.drawText(23, Draw::centerX("Press enter to confirm"), "Press enter to confirm");
                screen.attrOff(COLOR_PAIR(1));
                screen.refreshScreen();
            }
            if (ch == 10)  {
                
                screen.clearLine(23, 0);
                screen.refreshScreen();
                // Qui chiamare la funziona per salvare e se salvato con successo printare File saved
                // se ci sono errori ritornati dalla funzione per salvare printare Error saving file
                
                // controllare se non esiste già un file con lo stesso nome
                if (File::nameAlreadyInUse(nome)) screen.drawText(23, Draw::centerX("Name already in use"), "Name already in use");
                else {
                    saved = true;
                screen.drawText(23, Draw::centerX("File saved"), "File saved");

                screen.attrOn(COLOR_PAIR(1));
                screen.drawText(25, Draw::centerX("Press enter to exit"), "Press enter to exit");
                screen.attrOff(COLOR_PAIR(1));
                screen.refreshScreen();
                screen.getinput();
                screen.eraseScreen();
                }
            }
        }
    }
    }
    File::saveMap(map, chunk, PlayerPos, nome);
    this->alreadySaved = true; // Forse ora è inutile perchè c'è già la funzione in file
}

void Save::saveGame(Draw screen){
    int xMaxSize, yMaxSize;
    getmaxyx(stdscr, yMaxSize, xMaxSize);
    int posY = (yMaxSize - 5) / 2;
    int posX = (xMaxSize - 20) / 2;
    
    Draw saved = screen.newWindow(5, 20, posY, posX);
    saved.eraseScreen();
    saved.drawBox();
    saved.drawText(2, 10 - (strlen("Game Saved") / 2), "Game Saved");
    saved.refreshScreen();
    saved.eraseScreen();
    saved.deleteWin();
    napms(700);
}

void Save::quitGame(Draw screen, Map map, int chunk, phy::Point PlayerPos){
    int xMaxSize, yMaxSize;
    getmaxyx(stdscr, yMaxSize, xMaxSize);
    int posY = (yMaxSize - 15) / 2;
    int posX = (xMaxSize - 55) / 2;
    
    Draw quit_scr = screen.newWindow(15, 55, posY, posX);
    quit_scr.eraseScreen();
    quit_scr.drawBox();
    keypad(quit_scr.getScreen(), true);
    quit_scr.drawText(2, 27 - (strlen("Quit wihout saving?") / 2), "Quit without saving?");
    // creare due buttoni yes e no
    bool choose = false;
    int selected = 0;
    nostd::string options[2] = {"Yes", "Save Now"};
    while (!choose){
        for (int i = 0; i < 2; i++){
            quit_scr.drawText(8, 18 + 10*i, options[i].c_str());
        }
        quit_scr.attrOn(COLOR_PAIR(1));
        quit_scr.drawText(8, 18 + 10*selected, options[selected].c_str());
        quit_scr.attrOff(COLOR_PAIR(1));
        quit_scr.refreshScreen();
        switch (quit_scr.getinput()){
            case KEY_LEFT:
                if (selected == 0) selected = 1;
                else selected--;
                break;
            case KEY_RIGHT:
                if (selected == 1) selected = 0;
                else selected++;
                break;
            case 10:
                choose = true;
                break;
        }
    
    } 
    if (selected == 1) { // Se l'utente vuole salvare prima di uscire
            int xMaxSize, yMaxSize;
			getmaxyx(stdscr, yMaxSize, xMaxSize);
			int posY = (yMaxSize - 44) / 2;
			int posX = (xMaxSize - 150) / 2;
			
			Draw save_scr = quit_scr.newWindow(44, 150, posY, posX);

			
            saveNewGame(save_scr, map, chunk, PlayerPos);
			save_scr.eraseScreen();
			save_scr.deleteWin();
    }
    quit_scr.eraseScreen();
    quit_scr.deleteWin();


}