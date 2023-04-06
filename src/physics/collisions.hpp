#include "body.hpp"
#include "../maps/chunk.hpp"

#ifndef PHYSICS_COLLISIONS
#define PHYSICS_COLLISIONS

void updateWithCollisions(phy::Body *body, double time, Chunk *chunk);

#endif
