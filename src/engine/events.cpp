#include "events.hpp"

Events::Events() : _time(0), _start(0), _to_draw(nullptr) {}

void Events::make_ability_happen(Ability ability, Manager &manager,
                                 phy::Point player_pos) {
  if (this->_start == 0) {
    switch (ability.get_type()) {
    case 0: { // Shild
      this->_to_draw =
          head_insert(this->_to_draw, '!', player_pos - phy::Point(1, 0), 0);
      this->_to_draw =
          head_insert(this->_to_draw, '!', player_pos + phy::Point(1, 0), 0);

      this->_ability_type = 0;
      this->_start = this->_time;
      break;
    }
    case 2:
      manager.stop_time();
      this->_ability_type = 2;
      this->_start = this->_time;
      break;
    default:
      break;
    }
  }
}

void Events::update(Manager &manager) {
  unsigned long long int diff = this->_time - this->_start;
  if (diff != 0) {
    switch (this->_ability_type) {
    case 0:
      if (diff >= 100) {
        this->_to_draw = this->delete_type(this->_to_draw, 0);
        this->_start = 0;
      }
      break;
    case 2:
      if (diff >= 1000) {
        manager.unstop_time();
        this->_start = 0;
      }
      break;
    default:
      break;
    }
  }

  this->_time++;
}

void Events::draw(Draw *screen) {
  drawable *d = this->_to_draw;
  int deb_counter = 0;
  while (d != nullptr) {
    screen->drawText(OFFSET - d->pos.get_yPosition(),
                     d->pos.get_xPosition() + 1, d->val);
    d = d->next;
    deb_counter++;
  }
}

drawable *Events::head_insert(drawable *head, char val, phy::Point pos,
                              int type) {
  drawable *tmp = new drawable;
  tmp->val = val;
  tmp->pos = pos;
  tmp->type = type;
  tmp->next = this->_to_draw;
  return tmp;
}

drawable *Events::delete_type(drawable *head, int type) {
  if (head == nullptr)
    return head;
  if (head->type == type) {
    drawable *tmp = this->delete_type(head->next, type);
    delete head;
    return tmp;
  } else {
    head->next = delete_type(head->next, type);
    return head;
  }
}
