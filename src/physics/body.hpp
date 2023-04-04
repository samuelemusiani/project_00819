#include "point.hpp"
#include "vector.hpp"

#ifndef PHYSICS_BODY
#define PHYSICS_BODY
namespace phy
{
	class Body
	{
		protected:
			phy::Point position;
			phy::Vector velocity;
			phy::Vector acceleration;


		public:
			Body();
			Body(phy::Point position, phy::Vector velocity, phy::Vector acceleration);

			void set_position(phy::Point position);
			void set_velocity(phy::Vector velocity);
			void set_acceleration(phy::Vector acceleration);


			phy::Point get_position();
			phy::Vector get_velocity();
			phy::Vector get_acceleration();

			void update(int time);
	};
};
#endif 
