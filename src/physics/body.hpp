/*
* Alma Mater Studiorum - University of Bologna
* First cycle degree in Computer Science
* Computer Programming - 00819
*
* Author: Musiani Samuele #0001069143
*
* body.hpp: Class to simulate a physics body with
* position, velocity and acelleration.
*/

#include "precisePoint.hpp"
#include "vector.hpp"

#ifndef PHYSICS_BODY
#define PHYSICS_BODY
namespace phy
{
	class Body
	{
		protected:
			phy::PrecisePoint position;
			phy::Vector velocity;
			phy::Vector acceleration;


		public:
			Body();
			Body(phy::PrecisePoint position, phy::Vector velocity, phy::Vector acceleration);
			Body(phy::Point position, phy::Vector velocity, phy::Vector acceleration);

			void set_position(phy::PrecisePoint position);
			void set_position(phy::Point position);
			void set_velocity(phy::Vector velocity);
			void set_acceleration(phy::Vector acceleration);


			phy::Point get_position();
			phy::PrecisePoint get_precisePosition();
			phy::Vector get_velocity();
			phy::Vector get_acceleration();

			void update(double time);
	};
};
#endif 
