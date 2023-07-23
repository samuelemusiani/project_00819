#include "market.hpp"
#include "../../etc/logs/logs.hpp"
#include "../draw/draw.hpp"

Market::Market() : current_gun(0), current_ability(0), current_coins(0) {
  this->all_guns[0] = Gun("Basic", 0, 0, 5);
  this->all_guns[1] = Gun("Revolver", 10, 1, 10);
  this->all_guns[2] = Gun("Mitra", 25, 0, 1);
  this->all_guns[3] = Gun("Grenade Launcher", 40, 2, 15);

  this->all_abilities[0] = Ability("Invincibility", 4, 0);
  this->consumable_abilities[0] = 0;
  this->all_abilities[1] = Ability("Reduce enemies", 8, 1);
  this->consumable_abilities[1] = 1;
  this->all_abilities[2] = Ability("Stop time", 10, 2);
  this->consumable_abilities[2] = 1;

  this->all_health[0] = "1 Heart";
  this->all_health[1] = "Full life";

  this->guns_bought[0] = 1;
  for (int i = 1; i < MARKET_MAX_GUN; i++)
    this->guns_bought[i] = 0;

  this->abilities_bought[0] = 1;
  for (int i = 1; i < MARKET_MAX_ABILITY; i++)
    this->abilities_bought[i] = 0;
}

Gun Market::get_current_gun() { return this->all_guns[this->current_gun]; }

Ability Market::get_current_ability() {
  return this->all_abilities[this->current_ability];
}

void Market::make_ability_used() {
  if (this->consumable_abilities[this->current_ability]) {
    this->abilities_bought[this->current_ability] = 0;
    this->current_ability = 0; // I'm shure that it's free
  }
}

void Market::open(Statistics &stats) {
  this->current_coins = stats.getCoins();
  this->current_hearts = stats.getHearts();

  this->draw();

  stats.setHearts(this->current_hearts);
  stats.setCoins(this->current_coins);
}

nostd::string Market::get_save() {
  nostd::string save;
  save.push_back(this->current_gun + '0');
  save.push_back(this->current_ability + '0');

  for (int i = 0; i < MARKET_MAX_GUN; i++)
    save.push_back(this->guns_bought[i] + '0');

  for (int i = 0; i < MARKET_MAX_ABILITY; i++)
    save.push_back(this->abilities_bought[i] + '0');

  return save;
}

void Market::set_save(nostd::string save) {
  this->current_gun = save[0] - '0';
  this->current_ability = save[1] - '0';

  for (int i = 0; i < MARKET_MAX_GUN; i++)
    this->guns_bought[i] = save[2 + i] - '0';

  for (int i = 0; i < MARKET_MAX_ABILITY; i++)
    this->abilities_bought[i] = save[2 + MARKET_MAX_GUN + i] - '0';
}

void Market::draw() {
  Draw screen(SCREEN_HEIGHT, SCREEN_WIDTH);
  screen.nodel(false);

  int orizzontal_selection = 0;
  int vertical_selection = 0;

  bool exit = false;

  while (!exit) {
    screen.clearScreen();

    for (int i = 0; i < MARKET_MAX_SUBMENUS; i++) {
      if (i == orizzontal_selection)
        screen.attrOn(COLOR_PAIR(1));

      screen.drawSquareAround("  " + this->summenues[i] + "  ", 6,
                              SCREEN_WIDTH / 4 * (i + 1));

      if (i == orizzontal_selection)
        screen.attrOff(COLOR_PAIR(1));
    }

    screen.drawSquareAround(
        "  HEARTS: " + nostd::to_string(this->current_hearts) + "  ", 33, 20);
    screen.drawSquareAround(
        "  COINS: " + nostd::to_string(this->current_coins) + " $  ", 36, 20);

    int price = -1;
    if (orizzontal_selection == 0) {
      for (int i = 0; i < 6; i++)
        screen.drawText(34 + i, 50, this->gun_art[i]);

      for (int i = 0; i < MARKET_MAX_GUN; i++) {
        if (i == vertical_selection)
          screen.attrOn(COLOR_PAIR(1));

        if (i == this->current_gun)
          screen.drawSquareAround(" * " + this->all_guns[i].get_name() + " ",
                                  3 * i + 16, 20);
        else
          screen.drawSquareAround(" " + this->all_guns[i].get_name() + " ",
                                  3 * i + 16, 20);

        screen.attrOff(COLOR_PAIR(1));
      }

      Gun gun = this->all_guns[vertical_selection];

      screen.drawText(16, 60, "Name: \t\t" + gun.get_name());
      screen.drawText(18, 60,
                      "Damage: \t\t" +
                          nostd::to_string(Bullet::get_bullet_damage(
                              gun.get_bullet_type())));
      screen.drawText(
          20, 60, "Bullet type: \t" + nostd::to_string(gun.get_bullet_type()));

      if (!this->guns_bought[vertical_selection]) {
        price = gun.get_price();
        screen.drawText(22, 60, "Price: \t\t" + nostd::to_string(price));
      } else
        screen.drawText(22, 60, "Price: \t\t You already have this gun!");
    } else if (orizzontal_selection == 1) {
      for (int i = 0; i < 8; i++)
        screen.drawText(32 + i, 60, this->book_art[i]);

      for (int i = 0; i < MARKET_MAX_ABILITY; i++) {
        if (i == vertical_selection)
          screen.attrOn(COLOR_PAIR(1));

        if (i == this->current_ability)
          screen.drawSquareAround(
              " * " + this->all_abilities[i].get_name() + " ", 3 * i + 16, 20);
        else
          screen.drawSquareAround(" " + this->all_abilities[i].get_name() + " ",
                                  3 * i + 16, 20);

        screen.attrOff(COLOR_PAIR(1));
      }

      Ability ability = this->all_abilities[vertical_selection];

      screen.drawText(16, 60, "Name: \t\t" + ability.get_name());

      if (!this->abilities_bought[vertical_selection]) {
        price = ability.get_price();
        screen.drawText(18, 60, "Price: \t\t" + nostd::to_string(price));
      } else
        screen.drawText(18, 60, "Price: \t\t You already have this ability!");
    } else if (orizzontal_selection == 2) {
      for (int i = 0; i < 11; i++)
        screen.drawText(30 + i, 66, this->poison_art[i]);

      for (int i = 0; i < 2; i++) {
        if (i == vertical_selection)
          screen.attrOn(COLOR_PAIR(1));

        screen.drawSquareAround(" " + this->all_health[i] + " ", 3 * i + 16,
                                20);

        screen.attrOff(COLOR_PAIR(1));
      }
      if (vertical_selection == 0)
        price = 2;
      else
        price = 8;

      screen.drawSquareAround("  PRICE: " + nostd::to_string(price) + " $  ",
                              36, 120);
    }
    if (price == -1)
      screen.drawSquareAround("  PRICE: You have it!  ", 36, 114);
    else
      screen.drawSquareAround("  PRICE: " + nostd::to_string(price) + " $  ",
                              36, 120);

    switch (screen.getinput()) {
    case KEY_RIGHT: {
      orizzontal_selection =
          std::min(++orizzontal_selection, MARKET_MAX_SUBMENUS - 1);
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
      if (orizzontal_selection == 0)
        max_down = MARKET_MAX_GUN;
      else if (orizzontal_selection == 1)
        max_down = MARKET_MAX_ABILITY;
      else if (orizzontal_selection == 2)
        max_down = 2;
      else
        max_down = 0;

      vertical_selection = std::min(++vertical_selection, max_down - 1);
      break;
    }
    case 10: {
      if (price <= this->current_coins) {

        if (orizzontal_selection == 0) {
          if (!this->guns_bought[vertical_selection])
            this->current_coins -= price;

          this->current_gun = vertical_selection;
          this->guns_bought[vertical_selection] = 1;
        } else if (orizzontal_selection == 1) {
          if (!this->abilities_bought[vertical_selection])
            this->current_coins -= price;

          this->current_ability = vertical_selection;
          this->abilities_bought[vertical_selection] = 1;
        } else {
          this->current_coins -= price;
          if (vertical_selection == 0) {
            this->current_hearts =
                std::min(++this->current_hearts, MAX_POSSIBLE_HEARTS);
          } else
            this->current_hearts = MAX_POSSIBLE_HEARTS;
        }
      } else {
        // Can't buy the item
        Draw win(SCREEN_HEIGHT / 4, SCREEN_WIDTH / 3);
        win.clearScreen();
        win.nodel(false);

        // This should probably go in draw to make it global
        win.attrOn(COLOR_PAIR(1));
        win.drawCenterText(3, "You can't buy this item, you are poor!");
        init_pair(21, COLOR_BLACK, COLOR_RED);
        win.attrOn(COLOR_PAIR(21));
        win.drawCenterText(7, "Ok...");
        win.attrOff(COLOR_PAIR(1));

        win.refreshScreen();

        int input;
        do {
          input = win.getinput();
        } while (input != 10);

        win.nodel(true);
        win.deleteWin();
      }
      break;
    }
    case 27: {
      exit = true;
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
