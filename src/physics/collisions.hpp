/*
* Alma Mater Studiorum - University of Bologna
* First cycle degree in Computer Science
* Computer Programming - 00819
*
* Author: Musiani Samuele #0001069143
*
* collision.hpp: Class to simulate a physics collision from a body and a Chunk.
* The time is used to calculate the trajectory with an update on the velocity
* and acceleration.
*/

#include "body.hpp"
#include "../maps/chunk.hpp"

#ifndef PHYSICS_COLLISIONS
#define PHYSICS_COLLISIONS
namespace phy
{
void updateWithCollisions(phy::Body &body, double time, Chunk chunk);
}
#endif
