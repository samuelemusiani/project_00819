#include "market.hpp"
#include "../draw/draw.hpp"

Market::Market()
    : current_gun(0), current_ability(0), current_coins(0)
{
    this->all_guns[0] = Gun("Basic", 1, 0);
    this->all_guns[1] = Gun("Revolver", 2, 10);
    this->all_guns[2] = Gun("Mitra", 1, 25);
    this->all_guns[3] = Gun("TOO MUCH", 4, 40);

    this->all_abilities[0] = Ability("Shield", 4);
    this->all_abilities[1] = Ability("Explosion", 8);
    this->all_abilities[2] = Ability("No gravity", 10);

    this->all_health[0] = "1 Heart";
    this->all_health[1] = "Full life";

}

Gun Market::get_current_gun()
{
    return this->all_guns[this->current_gun];
}

Ability Market::get_current_ability()
{
    return this->all_abilities[this->current_ability];
}

int Market::get_current_coins()
{
    return this->current_coins;
}

void Market::set_current_coins(int c)
{
    this->current_coins = c;
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
                
            screen.drawSquareAround("  " + this->summenues[i] + "  ", 6, SCREEN_WIDTH/4 * (i + 1));

            if(i == orizzontal_selection)
                screen.attrOff(COLOR_PAIR(1));
        }

        screen.drawSquareAround("  COINS: " + nostd::to_string(this->current_coins) + " $  ", 36, 20);


        if(orizzontal_selection == 0)
        {
            for(int i = 0; i < 6; i++)
                screen.drawText(34 + i, 50, this->gun_art[i]);

            for(int i = 0; i < MARKET_MAX_GUN; i++)
            {
                if(i == vertical_selection)
                    screen.attrOn(COLOR_PAIR(1));

                if(i == this->current_gun)
                    screen.drawSquareAround(" * " + this->all_guns[i].get_name() + " ", 3 * i + 16, 20);
                else
                    screen.drawSquareAround(" " + this->all_guns[i].get_name() + " ", 3 * i + 16, 20);

                screen.attrOff(COLOR_PAIR(1));
            }

            Gun gun = this->all_guns[vertical_selection];

            screen.drawSquareAround("  PRICE: " + nostd::to_string(gun.get_price()) + " $  ", 36, 120);
            screen.drawText(16, 60, "Name: \t\t" + gun.get_name());
            screen.drawText(18, 60, "Damage: \t\t" + nostd::to_string(gun.get_damage()));
            screen.drawText(20, 60, "Bullet type: \t" + nostd::to_string(2));
            screen.drawText(22, 60, "Price: \t\t" + nostd::to_string(gun.get_price()));
        }
        else if(orizzontal_selection == 1)
        {
            for(int i = 0; i < 8; i++)
                screen.drawText(32 + i, 60, this->book_art[i]);

            for(int i = 0; i < MARKET_MAX_ABILITY; i++)
            {
                if(i == vertical_selection)
                    screen.attrOn(COLOR_PAIR(1));

                if(i == this->current_ability)
                    screen.drawSquareAround(" * " + this->all_abilities[i].get_name() + " ", 3 * i + 16, 20);
                else
                    screen.drawSquareAround(" " + this->all_abilities[i].get_name() + " ", 3 * i + 16, 20);

                screen.attrOff(COLOR_PAIR(1));
            }
            Ability ability = this->all_abilities[vertical_selection];

            screen.drawSquareAround("  PRICE: " + nostd::to_string(ability.get_price()) + " $  ", 36, 120);
            screen.drawText(16, 60, "Name: \t\t" + ability.get_name());
            screen.drawText(18, 60, "Type : \t\tNot set");
            screen.drawText(20, 60, "Price: \t\t" + nostd::to_string(ability.get_price()));
        }
        else if(orizzontal_selection == 2)
        {
            for(int i = 0; i < 11; i++)
                screen.drawText(30 + i, 66, this->poison_art[i]);

            for(int i = 0; i < 2; i++)
            {
                if(i == vertical_selection)
                    screen.attrOn(COLOR_PAIR(1));

                screen.drawSquareAround(" " + this->all_health[i] + " ", 3 * i + 16, 20);

                screen.attrOff(COLOR_PAIR(1));
            }
            int price;
            if(vertical_selection == 0)
                price = 2;
            else
                price = 8;
                
            screen.drawSquareAround("  PRICE: " + nostd::to_string(price) + " $  ", 36, 120);
        }

        switch(screen.getinput())
        {
            case KEY_RIGHT: {
                               orizzontal_selection = std::min(
                                       ++orizzontal_selection, MARKET_MAX_SUBMENUS - 1);
                               vertical_selection = 0;
                               break;
                           }
            case KEY_LEFT: {
                               orizzontal_selection = std::max(--orizzontal_selection, 0);
                               vertical_selection = 0;
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
                               else if(orizzontal_selection == 2)
                                   max_down = 2;
                               else
                                   max_down = 0;

                               vertical_selection = std::min(++vertical_selection, max_down - 1);
                               break;
                           }
            case 10: {
                         // TODO: Make the selection buy the gun/ability with coins
                         if(orizzontal_selection == 0)
                             this->current_gun = vertical_selection;
                         else if(orizzontal_selection == 1)
                             this->current_ability = vertical_selection;

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
