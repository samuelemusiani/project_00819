#include "point.hpp"

#ifndef PHYSICS_PRECISEPOINT
#define PHYSICS_PRECISEPOINT

namespace phy
{
	class PrecisePoint
	{
		protected:
			double posX;
			double posY;

		public:
			PrecisePoint();
			PrecisePoint(double posX, double posY);
			void set_xPosition(double posX);
			void set_yPosition(double posY);
			double get_xPosition();
			double get_yPosition();

			phy::Point toPoint();
	};
}
#endif
