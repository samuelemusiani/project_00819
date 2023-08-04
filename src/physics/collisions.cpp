/*
 * Alma Mater Studiorum - University of Bologna
 * First cycle degree in Computer Science
 * Computer Programming - 00819
 *
 * Author: Musiani Samuele #0001069143
 *
 * collision.cpp: Implentation of the collision function.
 */

#include <math.h>

#include "../maps/chunk.hpp"
#include "body.hpp"
#include "collisions.hpp"
#include "constants.hpp"
#include "point.hpp"
#include "precisePoint.hpp"
#include "vector.hpp"

#include "../../etc/logs/logs.hpp"

static int detectCollision(int old_xPos, int old_yPos, int new_xPos,
                           int new_yPos, Chunk *chunk);
static void resetVelocityAcceleration(phy::Body &body);
static bool hasJumped(phy::Body &body);
static bool is_on_a_platform(phy::Body &body, Chunk *chunk);
static void borderCollision(phy::Body &body);

/*
   Le possibilità per implementare la funzione sono molte.
   L'idea è che prende un putatore a body e che lo aggiorna dopo 'time' tempo
   tenendo conto delle possibili collisioni che avvengono sul chunk.

   1) Posso vedere la velocità di body, la su accelerazione e il tempo in modo
   che abbia due possibili sottoscelte: se il corpo dopo lo spotamente dato da
   'time' si è spostato di un solo blocco mi basta controllare che quel blocco
   non sia una piattaforma e ho finito. Se invece si sposta di più di un blocco
   faccio aggiornamenti più piccoli suddividendo il tempo in maniera tale che
   si sposti sempre di un blocco e faccio sempre il check se ha toccato una
   piattaforma.

   2) Posso calcolare tutta la traiettoria del punto e poi a posteriore fare un
   check se ho fatto una collisione. Solo che non saprei quando finire di
   calcolare la traiettoria (visto che potrebbe anche andare in caduta libera)
   e sopratutto avrei fatto calcoli inutili se la collissione fosse all'inzio.
*/

void phy::updateWithCollisions(phy::Body &body, double time, Chunk chunk) {

  // Check collision with the map boders
  borderCollision(body);

  if (!hasJumped(body)) {
    if (is_on_a_platform(body, &chunk)) {
      resetVelocityAcceleration(body);
    } else {
      // FREE FALL

      // Devo continuare a settare l'accelerazione?
      body.set_acceleration(phy::Vector(phy::GRAVITY_ACCELERATION, -90));

      phy::Body old_body = body;
      body.update(time);

      int old_yPos = round(old_body.get_precisePosition().get_yPosition());
      int new_yPos = round(body.get_precisePosition().get_yPosition());
      int new_xPos = round(body.get_precisePosition().get_xPosition());

      if (old_yPos - new_yPos > 1) {
        bool found_a_platform = false;
        int tmp_pos = old_yPos;

        while (tmp_pos >= new_yPos && tmp_pos >= 0 && !found_a_platform) {

          if (chunk.is_there_a_platform(phy::Point(new_xPos, tmp_pos)))
            found_a_platform = true;
          else
            tmp_pos--;
        }
        if (found_a_platform) {
          tmp_pos += 1;
          resetVelocityAcceleration(body);
        }

        body.set_position(phy::Point(new_xPos, tmp_pos));
      }
    }
  } else {
    body.set_acceleration(phy::Vector(phy::GRAVITY_ACCELERATION, -90));

    phy::Body old_body = body;
    body.update(time);

    // Faccio tutto con int o metto i precisePoint?
    int old_xPos = round(old_body.get_precisePosition().get_xPosition());
    int old_yPos = round(old_body.get_precisePosition().get_yPosition());
    int new_xPos = round(body.get_precisePosition().get_xPosition());
    int new_yPos = round(body.get_precisePosition().get_yPosition());

    phy::Vector velocity = body.get_velocity();

    switch (detectCollision(old_xPos, old_yPos, new_xPos, new_yPos, &chunk)) {
    // no collision
    case 0:
      break;

    // 1 -> basic collision in the x direction
    // (the body moved only on one block)
    case 1:
      body.set_velocity(phy::Vector(0.0));
      body.set_position(phy::Point(old_xPos, new_yPos));
      break;

    // 2 -> basic collision in the y direction
    // (the body moved only on one block)
    case 2: {
      int direction = body.get_velocity().get_direction();
      if (10 < direction && direction < 90)
        body.set_velocity(phy::Vector(velocity.get_magnitude() / 3,
                                      velocity.get_direction() - 90));
      else if (90 < direction && direction < 170)
        body.set_velocity(phy::Vector(velocity.get_magnitude() / 3,
                                      velocity.get_direction() + 90));
      else
        body.set_velocity(phy::Vector(0.0));

      body.set_position(phy::Point(new_xPos, old_yPos));
      break;
    }

    // 3 -> complex collision
    // (the body moved one block in the x and
    // one block in the y direction)
    case 3:
      body.set_position(old_body.get_position());
      break;

    // 4 -> bad...really bad
    case 4:
      // I don't know what to do :)
      body.set_position(old_body.get_position());
      break;

    default:
      // Something went wrong...
      resetVelocityAcceleration(body);
      break;
    }
  }
}

void phy::updateWithCollisions(Bullet &bullet, double time, Chunk chunk) {
  phy::Body tmp(bullet.get_precise_position(), bullet.get_velocity(),
                phy::Vector(phy::GRAVITY_ACCELERATION, -90));

  updateWithCollisions(tmp, time, chunk);

  bullet.set_position(tmp.get_precisePosition());
  bullet.set_velocity(tmp.get_velocity());
}

// 0 -> no collision
// 1 -> basic collision in the x direction (the body moved only on one block)
// 2 -> basic collision in the y direction (the body moved only on one block)
// 3 -> complex collision (the body moved one block in the x and one block in
// the y direction) 4 -> bad...really bad

/* This function detect the type of collision that append base on the old and
 * the new position of the player.
 */
static int detectCollision(int old_xPos, int old_yPos, int new_xPos,
                           int new_yPos, Chunk *chunk) {
  int diff_x = abs(old_xPos - new_xPos);
  int diff_y = abs(old_yPos - new_yPos);

  if (diff_x == 0 && diff_y == 0)
    return 0;
  else if (diff_x == 0 && diff_y == 1) {
    if (chunk->is_there_a_platform(phy::Point(old_xPos, new_yPos)))
      return 2;
    else
      return 0;
  } else if (diff_x == 1 && diff_y == 0) {
    if (chunk->is_there_a_platform(phy::Point(new_xPos, old_yPos)))
      return 1;
    else
      return 0;
  } else if (diff_x == 1 & diff_y == 1) {

    // I need to check all possible path that the player could have taken
    // during the jump. If only one of these paths have a platform a
    // collision is detected

    if (chunk->is_there_a_platform(phy::Point(new_xPos, new_yPos)) ||
        chunk->is_there_a_platform(phy::Point(old_xPos, new_yPos)) ||
        chunk->is_there_a_platform(phy::Point(new_xPos, old_yPos)))
      return 3;
    else
      return 0;
  } else
    return 4;
}

static void resetVelocityAcceleration(phy::Body &body) {
  body.set_velocity(phy::Vector(0, 0));
  body.set_acceleration(phy::Vector(0, 0));
}

static bool hasJumped(phy::Body &body) {
  phy::Vector v = body.get_velocity();

  if (v.get_magnitude() < 0.1)
    return false;
  // Do this values make sense?
  else if (180 <= v.get_direction() && v.get_direction() <= 360)
    return false;

  return true;
}

static bool is_on_a_platform(phy::Body &body, Chunk *chunk) {
  return (chunk->is_there_a_platform(body.get_position() - phy::Point(0, 1)));
}

/* Check if the player had a collision with the map left and right borders.
 * If a collision happen the player fall immediately
 */
static void borderCollision(phy::Body &body) {
  phy::Point p = body.get_position();
  int x = p.get_xPosition();

  if (x < 0) {
    p.set_xPosition(0);
    body.set_position(p);

    // Make the player fall when he touches the wall
    body.set_velocity(phy::Vector(0.0));
  } else if (x > 147) {
    p.set_xPosition(147);
    body.set_position(p);

    // Make the player fall when he touches the wall
    body.set_velocity(phy::Vector(0.0));
  }
}
