#include "body.hpp"

#ifndef PHYSICS_WEIGHTEDBODY
#define PHYSICS_WEIGHTEDBODY

namespace phy
{
	//Ha senso come nome?
	class WeightedBody : Body
	{
		protected:
			double mass;

		public:
			WeightedBody();
			WeightedBody(phy::Point position, phy::Vector velocity, phy::Vector acceleration, double mass);

			void set_mass(double mass);
			double get_mass();


			//Tutta la parte sull'energia?
			double get_kineticEnergy();
			double get_potentialEnergy();
			double get_energy();
	};
}
#endif
