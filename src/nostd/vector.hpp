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
			void reallocate(int dim);

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
			void clear();
			void push_back(int data);
			void resize(int size);


			/* Operator overloading */

			int& operator [](int pos);
	};
}
#endif
