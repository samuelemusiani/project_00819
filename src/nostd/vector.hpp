#include <cstdlib>
#include <cstring>

#ifndef NOSTD_VECTOR
#define NOSTD_VECTOR

namespace nostd
{
	class vector
	{
		private:
			int *_A;
			unsigned int _size;
			unsigned int _capacity;

			void reallocate();

		public:
			vector();
			vector(int size);
			~vector();

			/* Element access */
			int at(int pos);


			/* Capacity */
			int size();
			int capacity();

			/* Modifiers */
			void push_back(int data);
			void clear();
	};
}
#endif
