#include "entity.hpp"

//#define TYPE_OF_ENTITIES {'A', 'B', 'C', 'D', 'E', '$'}

#ifndef ENTITY_MANAGER
#define ENTITY_MANAGER

struct lista {
  Entity val;
  lista* next;
};
typedef lista* plista;

class Manager {
private:
  nostd::vector<plista> Entities; //vettore di liste (puntatori alle teste delle liste)
  int Global_Entities;

protected:
  plista head_insert(int Chunk, Entity e); //TODO
  plista delete_el(plista p, Entity e);

public:

  Manager();
  void add_entity(int Chunk, char id, int p, int hp, int ms, int damg);
  //void kill_entity();//forse non serve

  //boh forse servono
  bool isThereSomethingHere(phy::Point p);
  nostd::vector<phy::Point> get_entities_by_id(nostd::string id); //non so se devo usare un vettore di punti

};
#endif
