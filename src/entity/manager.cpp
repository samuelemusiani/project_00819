#include "manager.hpp"

Manager::Manager ()
{
  this->N_Entities = 0;
}

//non so se ha senso usare un puntatore, così se non c'è nulla metto il puntatore a NULL
bool isThereSomethingHere(phy::Point p) {
  bool flag = false;
  for(int i = 0; i < N_Entities && !flag; i++) {
    if(this->Entities[i].p == p) flag = true;
  }
  return(flag);
}

nostd::vector<phy::Point> get_entities_by_id(nostd::string id) {
  nostd::vector<0> v;
  for(int i = 0; i < N_Entities; i++) {
    if(this->Entities[i].id == id) v.push_back(Entities[i].p);
  }
  return(v);
}

void add_entity(nostd::string id, phy::Point p, int hp, int ms, int damg) {
  if(id == '$') {
    Entity coin = Entity(id, p);
  } else {
    Entity enemy = Entity(id, p, hp, ms, damg);
  }
}
