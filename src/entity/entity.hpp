#include "../../ect/nostd/string.hpp"
#include "../physics/point.hpp"

class Entity : public Manager {
protected:
  nostd::string id;
  phy::Point p;
public:

  Entity(nostd::string id, phy::Point p);
  void init_entity(nostd::string id, phy::Point p);
  void set_point(phy::Point p);

}
