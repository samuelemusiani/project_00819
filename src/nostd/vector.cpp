#include <cstdlib>
#include <cstring>
#include <algorithm>
#include "vector.hpp"

using namespace nostd;

/*
   This function id used when the _size is equal to the _capacity.
   In this case the array on the heap need to be reallocate beacause 
   some elements need to be inserted. The strategy for a reallocation is 
   simply to duplicate the array.
*/

void vector::reallocate()
{
	if (this->_capacity == 0) this->reallocate(1);
	else if (this->_capacity == 1) this->reallocate(2);
	else this->reallocate(this->_capacity * 2);
}

/*
   This is the more advance version of reallocate in which there is a 
   a input arguments to use to specify the capacity of the new vector.
   There are three cases:
	   1) The new capacity is LARGER than the previous capacity: 
	   In this case a new array will be created and all the old values are
	   copied in to the new array.

	   2) The new_capaciy is SMALLER than the previous capacity:
	   In this case there is a reduction of the old array (but i can not 
	   perform a reduction with realloc() so i simply create a new array):

	   3) In the case of new_capaciy == previus capacity the function 
	   does simply nothing.
*/

void vector::reallocate(int new_capaciy)
{
	if (new_capaciy >= 0 && this->_capacity != new_capaciy)
	{
		int* tmp = new int[new_capaciy];
		std::memcpy(tmp, this->_A, std::min((int) this->_capacity, new_capaciy) * sizeof(int));

		if(this->_A != nullptr)
			delete[] this->_A;

		this->_A = tmp;
		this->_capacity = new_capaciy;
	}
}

vector::vector() : vector(0)
{

}

vector::vector(int size)
{
	this->_A = nullptr;
	this->_size = 0;
	this->_capacity = 0;

	this->resize(size);
}

vector::~vector()
{
	this->clear();
}

int vector::at(int pos)
{
	return *(this->_A + std::min(pos, (int) this->_size - 1));
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

	//Do I need to check if the reallocation has been done correctly?

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

void vector::resize(int size)
{
	if (size >= 0 && size != this->_size)
	{
		if(size < this->_size)
		{
			this->_size = size;

			if (this->_size < this->_capacity / 3)
				reallocate(this->_capacity / 2);
		}
		else
		{
			if (size <= this->_capacity)
				this->_size = size;
			else {
				//I need more space
				this->reallocate(size);
				this->_size = size;
			}
		}
	}
}
