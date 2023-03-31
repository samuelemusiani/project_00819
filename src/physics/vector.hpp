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

			void set_magnitude(double magnitude);
			void set_direction(int alpha);	

			double get_magnitude();
			int get_direction();
	};
}
