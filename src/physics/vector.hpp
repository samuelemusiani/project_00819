/*
* Alma Mater Studiorum - University of Bologna
* First cycle degree in Computer Science
* Computer Programming - 00819
*
* Author: Musiani Samuele #0001069143
*
* vector.hpp: Class for a physics vector stored
* in polar coordinate.
*/

#ifndef PHYSICS_VECTOR
#define PHYSICS_VECTOR

namespace phy
{
	class Vector
	{
		protected:

			/* 
			* L'idea è di implementare la direzione del vettore 
			* in coordinate polari in modo che sia relativamente 
			* facile fare calcoli successivi con la fisica
			*/

			double magnitude;
			int alpha;		// Usiamo i gradi e non i radianti per usare int	

		public:
			Vector();
			Vector(double magnitude);
			Vector(double magnitude, int alpha);
			Vector(bool magnitude) = delete;

			void set_magnitude(double magnitude);
			void set_direction(int alpha);	

			double get_magnitude();
			int get_direction();

			int get_xComponent();
			int get_yComponent();

			static phy::Vector sum(phy::Vector v1, phy::Vector v2);

			bool operator ==(const Vector &p);
			bool operator !=(const Vector &p);
			Vector operator +(const Vector &p);
	};
}
#endif
