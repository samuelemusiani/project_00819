#include <iostream>
#include <cstring>

#define deb(x) std::cerr << #x << ": " << (x) << std::endl;

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

	void vector::reallocate()
	{
		if (this->_capacity == 0)
		{
			this->_A = (int*) malloc(1 * sizeof(int));
			this->_capacity = 1;
		}
		else if (this->_capacity == 1)
		{
			int* tmp = (int*) malloc(2 * sizeof(int));
			std::memcpy(tmp, this->_A, 1 * sizeof(int));
			delete this->_A;

			this->_A = tmp;
			this->_capacity = 2;
		} else
		{
			int new_capacity = (int) (this->_capacity * 2);
			int* tmp = (int*) malloc(new_capacity * sizeof(int));
			std::memcpy(tmp, this->_A, this->_capacity * sizeof(int));
			delete[] this->_A;

			this->_A = tmp;
			this->_capacity = new_capacity;
		}
	}

	vector::vector()
	{
		this->_A = nullptr;
		this->_size = 0;
		this->_capacity = 0;
	}
	
	vector::vector(int size)
	{
		this->_A = (int*) malloc(size * sizeof(int));
		this->_size = size;
		this->_capacity = size;
	}

	vector::~vector()
	{
		this->clear();
	}

	int vector::at(int pos)
	{
		if(pos >= this->_size)
			return *(this->_A + this->_size - 1);
		else
			return *(this->_A + pos);
	}

	int vector::size()
	{
		return (int) this->_size;
	}

	int vector::capacity()
	{
		return (int) this->_capacity;
	}

	void vector::push_back(int data)
	{
		if(this->_size == this->_capacity)
			this->reallocate();

		//Devo fare dei check?

		*(this->_A + this->_size) = data;
		this->_size++;
	}

	void vector::clear()
	{
		delete[] this->_A;
		this-> _A = nullptr;
		this->_size = 0;
		this->_capacity = 0;
	}
}

int main()
{
	std::cout << "Hello world\n";
	nostd::vector v = nostd::vector(100);
	for (int i = 0; i < 100; i++)
	{
		v.push_back(i);
		deb(v.size());
		deb(v.capacity());
	}


	for (int i = 0; i < v.size(); i++)
		std::cout << v.at(i) << " ";
	// v.print();
	return 0;
}
