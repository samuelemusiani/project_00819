#include "events.hpp"

Events::Events() : _time(0), _to_draw(nullptr) {}

void Events::make_ability_happen(Ability ability, Manager &manager,
                                 phy::Point player_pos) {
  switch (ability.get_type()) {
  case 0: { // Shild
    this->_to_draw =
        head_insert(this->_to_draw, '!', player_pos - phy::Point(1, 0));
    this->_to_draw =
        head_insert(this->_to_draw, '!', player_pos + phy::Point(1, 0));
    break;
  }
  default:
    break;
  }
}

void Events::refresh() { this->_time++; }

void Events::draw(Draw *screen) {
  drawable *d = this->_to_draw;
  while (d != nullptr) {
    screen->drawText(OFFSET - d->pos.get_yPosition(),
                     d->pos.get_xPosition() + 1, d->val);
    d = d->next;
  }
}

drawable *Events::head_insert(drawable *head, char val, phy::Point pos) {
  drawable *tmp = new drawable;
  tmp->val = val;
  tmp->pos = pos;
  tmp->next = this->_to_draw;
  return tmp;
}
