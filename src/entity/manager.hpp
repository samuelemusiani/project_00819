#include "entity.hpp"

#define TYPE_OF_ENTITIES {'A', 'B', 'C', 'D', 'E', '$'}

class Manager {
private:
  nostd::vector<Entity> Entities;
  int N_Entities;
public:

  Manager();
  int get_entities();//pensar a cosa ritorna l'entita come oggetto o cosa?
  void add_entity(char id, int p, int hp, int ms, int damg);
  void kill_entity();//forse non serve

  //boh forse servono
  bool isThereSomethingHere(phy::Point p);
  nostd::vector<phy::Point> get_entities_by_id(nostd::string id); //non so se devo usare un vettore di punti

}
