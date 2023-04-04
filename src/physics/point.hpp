#ifndef PHYSICS_POINT
#define PHYSICS_POINT

namespace phy
{
	class Point
	{
		protected:
			int posX;
			int posY;

		public:
			Point();
			Point(int posX, int posY);
			void set_xPosition(int posX);
			void set_yPosition(int posY);
			int get_xPosition();
			int get_yPosition();
	};
}
#endif
