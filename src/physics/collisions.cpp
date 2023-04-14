#include <math.h>
#include "collisions.hpp"

#include "constants.hpp"
#include "point.hpp"
#include "precisePoint.hpp"
#include "vector.hpp"
#include "body.hpp"
#include "../maps/chunk.hpp"


static int detectCollision(int old_xPos, int old_yPos, int new_xPos, int new_yPos, Chunk *chunk);
static void resetVelocityAcceleration(phy::Body *body);
static bool hasJumped(phy::Body *body);
static bool is_on_a_platform(phy::Body *body, Chunk *chunk);
/*
   Le possibilità per implementare la funzione sono molte.
   L'idea è che prende un putatore a body e che lo aggiorna dopo 'time' tempo tenendo
conto delle possibili collisioni che avvengono sul chunk.

   1) Posso vedere la velocità di body, la su accelerazione e il tempo in modo che abbia 
   due possibili sottoscelte: se il corpo dopo lo spotamente dato da 'time' si è spostato 
   di un solo blocco mi basta controllare che quel blocco non sia una piattaforma e ho finito. 
   Se invece si sposta di più di un blocco faccio aggiornamenti più piccoli suddividendo 
   il tempo in maniera tale che si sposti sempre di un blocco e faccio sempre il check se  
   ha toccato una piattaforma.
 
   2) Posso calcolare tutta la traiettoria del punto e poi a posteriore fare un check se ho 
   fatto una collisione. Solo che non saprei quando finire di calcolare la traiettoria (visto 
   che potrebbe anche andare in caduta libera) e sopratutto avrei fatto calcoli inutili se 
   la collissione fosse all'inzio.
*/


// Basandomi sull'euristica che il body del player verrà aggiornato per brevissimi intervalli
// di tempo inzio ad implementare la prima possibilità
void phy::updateWithCollisions(phy::Body *body, double time, Chunk *chunk)
{

	if(!hasJumped(body))
	{
		if (is_on_a_platform(body, chunk))
			resetVelocityAcceleration(body);
		else
		{
			body->set_acceleration(phy::Vector(phy::GRAVITY_ACCELERATION, 270));
			//STA CADENDO :)
		}
	}
	else
	{
		phy::Body old_body = *body;
		body->update(time);

		//Faccio tutto con int o metto i precisePoint?
		int old_xPos = old_body.get_position().get_xPosition();
		int old_yPos = old_body.get_position().get_yPosition();
		int new_xPos = body->get_position().get_xPosition();
		int new_yPos = body->get_position().get_yPosition();

		switch (detectCollision(old_xPos, old_yPos, new_xPos, new_yPos, chunk))
		{
			case 0:
				break;

			case 1:
				body->set_position(phy::Point(old_xPos, new_yPos));
				break;

			case 2:
				body->set_position(phy::Point(new_xPos, old_yPos));
				break;

			case 3:
				//NON SO COSA FARE :)
				break;
		}
	}
}


// 0 -> no collision
// 1 -> basic collision in the x direction (the body moved only on one block)
// 2 -> basic collision in the y direction (the body moved only on one block)
// 3 -> complex collision (the body moved on more than one block)

/* DA RISCRIVERE :) */
static int detectCollision(int old_xPos, int old_yPos, int new_xPos, int new_yPos, Chunk *chunk)
{
	int diff_x = old_xPos - new_xPos;
	int diff_y = old_yPos - new_yPos;

	if ( diff_x == 0 &&  diff_y == 0)
		return 0;
	else if (diff_x == 0)
	{
		for (int i = old_yPos; i <= new_yPos; i++)
			if (chunk->is_there_a_platform(old_xPos, i))
				return 2;

		return 0;
	}
	else if (diff_y == 0)
	{
		for (int i = old_xPos; i <= new_xPos; i++)
			if (chunk->is_there_a_platform(i, old_yPos))
				return 1;

		return 0;
	}
	else
	{
		//Come faccio in questo caso?
		// Devo trovare il momento della collisione e fare un rever della posizione
		// in modo da avere i vettori
		return 3;
	}

}

static void resetVelocityAcceleration(phy::Body *body)
{
	body->set_velocity(phy::Vector(0, 0));
	body->set_acceleration(phy::Vector(0, 0));
}

static bool hasJumped(phy::Body *body)
{
	phy::Vector v = body->get_velocity();
	
	if (v.get_magnitude() < 0.1)
		return false;
	else if (30 <= v.get_direction() && v.get_direction() <= 150) //Hanno senso questi valori?
	{
		return true;
	}

	return false;
}

static bool is_on_a_platform(phy::Body *body, Chunk *chunk)
{
	//DA SISTEMARE APPENA LORENZO FA IL PUSH CON LE FUNZIONI MODIFICATE

	phy::Point p = phy::Point(body->get_position());
	//p.set_yPosition(p.get_yPosition() - 1);
	return (chunk->is_there_a_platform(p.get_xPosition(), p.get_yPosition() - 1));
}