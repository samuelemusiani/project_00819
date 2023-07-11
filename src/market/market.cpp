#include "market.hpp"
#include "../draw/draw.hpp"

Market::Market()
{

}

void Market::draw()
{
    Draw screen = Draw(SCREEN_HEIGHT, SCREEN_WIDTH);
    screen.nodel(false);

    int orizzontal_selection = 0;
    int vertical_selection = 0;

    bool exit = false;

    while(!exit)
    {
        screen.clearScreen();

        for(int i = 0; i < MARKET_MAX_SUBMENUS; i++)
        {
            if(i == orizzontal_selection)
                screen.attrOn(COLOR_PAIR(1));
                
            screen.drawSquareAround(this->summenues[i], 8, SCREEN_WIDTH/4 * (i + 1));

            if(i == orizzontal_selection)
                screen.attrOff(COLOR_PAIR(1));
        }

        if(orizzontal_selection == 0)
        {
            for(int i = 0; i < MARKET_MAX_GUN; i++)
            {
                if(i == vertical_selection)
                    screen.attrOn(COLOR_PAIR(1));

                screen.drawSquareAround(this->all_guns[i].get_name(), 3 * i + 16, 20);

                if(i == vertical_selection)
                    screen.attrOff(COLOR_PAIR(1));
            }
        }
        else if(orizzontal_selection == 1)
        {
            for(int i = 0; i < MARKET_MAX_ABILITY; i++)
            {
                if(i == vertical_selection)
                    screen.attrOn(COLOR_PAIR(1));

                screen.drawSquareAround(this->all_abilities[i].get_name(), 3 * i + 16, 20);

                if(i == vertical_selection)
                    screen.attrOff(COLOR_PAIR(1));
            }
        }
        else if(orizzontal_selection == 2)
        {
            // Print helth (that can be bougth)
        }

        switch(screen.getinput())
        {
            case KEY_RIGHT: {
                               orizzontal_selection = std::min(
                                       ++orizzontal_selection, MARKET_MAX_SUBMENUS - 1);
                               break;
                           }
            case KEY_LEFT: {
                               orizzontal_selection = std::max(--orizzontal_selection, 0);
                               break;
                           }
            case KEY_UP: {
                               vertical_selection = std::max(0, --vertical_selection);
                               break;
                           }
            case KEY_DOWN: {
                               int max_down;
                               if(orizzontal_selection == 0)
                                   max_down = MARKET_MAX_GUN;
                               else if(orizzontal_selection == 1)
                                   max_down = MARKET_MAX_ABILITY;
                               else
                                   max_down = 0;

                               vertical_selection = std::min(++vertical_selection, max_down - 1);
                               break;
                           }
            default:
                        break;
        }

        screen.refreshScreen();
        napms(5);
    }

    screen.nodel(true);
}
