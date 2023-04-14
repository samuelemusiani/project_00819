#include "body.hpp"
#include "../maps/chunk.hpp"

#ifndef PHYSICS_COLLISIONS
#define PHYSICS_COLLISIONS
namespace phy
{
void updateWithCollisions(phy::Body &body, double time, Chunk chunk);
}
#endif
