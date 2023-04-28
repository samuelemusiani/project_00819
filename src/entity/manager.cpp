#include "manager.hpp"

Manager::Manager ()
{
  this->Global_Entities = 0;

}

Manager::~Manager()
{
  //save everything somewhere
	this->Global_Entities = 0;
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

void add_entity(int Chunk, nostd::string id, phy::Point p, int hp, int ms, int damg) {
  if(id == '$') {
    Entity entity = Entity(id, p);
  } else {
    Entity entity = Entity(id, p, hp, ms, damg);
  }

  this->Entities[Chunk] = head_insert(Chunk, entity);

  this->Global_Entities++;
}

/*void kill_entity(int Chunk, Entity e) {//TBD
  plsita tmp = this->Entites[Chunk];
  delete_el(tmp, e);
  this->Global_Entities--;
}*/

plista head_insert(int Chunk, Entity e) {
  if(this->Entities[Chunk] == NULL) {
    plista p = new lista;
    p->next = NULL;
    p->val = e;
  } else {
    plista p = new lista;
    p->next = this->Entites[Chunk];
    p->val = e;
  }
  return(p);
}

plista delete_el(plista p, Entity e) {
  if(p == NULL) {
    return(p);
  } else if (this->Entites[Chunk]->val == e) {
    plista tmp = p->next;
    delete p;
    p = NULL;
    return(tmp);
  } else {
    p->next = delete_el(Chunk, p->val);
    return(p);
  }
}
