#include <algorithm>
#include <cstring>

#ifndef NOSTD_VECTOR
#define NOSTD_VECTOR

#ifndef USE_STD_VECTOR
namespace nostd
{
	template <typename T> class vector
	{
		private:
			T* _buffer; 
			size_t _size;
			size_t _capacity;

			void reallocate(size_t new_capaciy);
			void reallocate();

		public:
			vector();
			vector(int size);
			vector(const vector<T>& other);
			~vector();

			/* Element access */
			const T& at(const int pos) const;

			/* Capacity */
			size_t size() const;
			size_t capacity() const;

			/* Modifiers */
			void clear();
			void push_back(const T& data);
			void push_back(T&& data);
			void pop_back();
			void resize(const int size);

			/* Operator overloading */
			const T& operator [](size_t pos) const;
			T& operator [](size_t pos);
			vector<T>& operator=(const vector<T>& other);
	};

	/*
	   This function id used when the _size is equal to the _capacity.
	   In this case the array on the heap need to be reallocate beacause 
	   some elements need to be inserted. The strategy for a reallocation is 
	   simply to duplicate the array.
	*/

	template <typename T>
	void vector<T>::reallocate()
	{
		if (this->_capacity == 0) this->reallocate(1);
		else if (this->_capacity == 1) this->reallocate(2);
		else this->reallocate(this->_capacity * 1.5);
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
	template <typename T>
	void vector<T>::reallocate(size_t new_capaciy)
	{
		if (new_capaciy >= 0 && this->_capacity != new_capaciy)
		{
			//T* tmp = reinterpret_cast<T*> (::operator new (new_capaciy * sizeof(T)));
			T* tmp = new T[new_capaciy];
			
			
			this->_size = std::min(this->_size, new_capaciy);

			/*
			   In this case a for loop may help if T has no trivial copy constructor 
			   so we need to call it explicitly to avoid shallow copy.
			 */

			//std::copy(tmp, tmp + std::min(this->_capacity, new_capaciy), this->_buffer);
			std::memcpy(tmp, this->_buffer, std::min(this->_capacity, new_capaciy) * sizeof(T));

			// for(size_t i = 0; i < this->_size; i++)
				// 	new (&tmp[i]) T(std::move(this->_buffer[i]));

			
			for(size_t i = 0; i < this->_size; i++)
				this->_buffer[i].~T();

			delete[] this->_buffer;

			this->_buffer = tmp;
			this->_capacity = new_capaciy;
		}
	}

	template <typename T>
	vector<T>::vector() 
		: vector(0)
	{

	}

	template <typename T>
	vector<T>::vector(int size)
		: _buffer(nullptr), _size(0), _capacity(0)
	{
		this->resize(size);
	}

	template <typename T>
	vector<T>::vector(const vector<T>& other)
	{
		this->_size = other._size;
		this->_capacity = other._capacity;
		this->_buffer = new T[this->_capacity];
		std::copy(other._buffer, other._buffer + this->_size, this->_buffer);
	}

	template <typename T>
	vector<T>::~vector()
	{
		this->clear();
		//::operator delete(this->_buffer, this->_capacity * sizeof(T));
		delete[] this->_buffer;
	}

	template <typename T>
	const T& vector<T>::at(const int pos) const
	{
		return *(this->_buffer + std::min(pos, (int) this->_size - 1));
	}

	template <typename T>
	size_t vector<T>::size() const
	{
		return this->_size;
	}

	template <typename T>
	size_t vector<T>::capacity() const
	{
		return this->_capacity;
	}

	template <typename T>
	void vector<T>::clear()
	{
		for (size_t i = 0; i < this->_size; i++)
			this->_buffer[i].~T();

		this->_size = 0;
		this->reallocate(0);
	}

	template <typename T>
	void vector<T>::push_back(const T& data)
	{
		if(this->_size >= this->_capacity)
			this->reallocate();

		//Do I need to check if the reallocation has been done correctly?

		this->_buffer[this->_size] = data;
		this->_size++;
	}
	
	// rvalue reference to avoid creating and destroy when passing rvalues
	template <typename T>
	void vector<T>::push_back(T&& data)
	{
		if(this->_size >= this->_capacity)
			this->reallocate();

		//Do I need to check if the reallocation has been done correctly?

		// when entering a function data becomes an 
		// lvalue so we need to move it.
		this->_buffer[this->_size] = std::move(data);
		this->_size++;
	}

	template <typename T>
	void vector<T>::pop_back()
	{
		if (this->_size > 0)
		{
			this->_size--;

			//Distruggo l'ultimo elemento
			this->_buffer[this->_size].~T();
		}
	}

	template <typename T>
	void vector<T>::resize(const int size)
	{
		if (size >= 0 && size != this->_size)
		{
			if(size < this->_size)
			{
				this->_size = size;

				if (this->_size >= this->_capacity / 4 && this->_size <= this->_capacity / 3)
					reallocate(this->_capacity / 2);
				else if (this->_size <= this->_capacity / 4)
					reallocate(this->_size * 2);
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

	template <typename T>
	const T& vector<T>::operator [](size_t pos) const
	{
		return this->_buffer[pos];
	}

	template <typename T>
	T& vector<T>::operator [](size_t pos)
	{
		return this->_buffer[pos];
	}

	template <typename T>
	vector<T>& vector<T>::operator=(const vector<T>& other)
	{
		if (this != &other) {
			delete[] _buffer;
			this->_size = other._size;
			this->_capacity = other._capacity;
			this->_buffer = new T[this->_capacity];
			std::copy(other._buffer, other._buffer + this->_size, this->_buffer);
		}
		return *this;
	}
}
#else //USO STD COME SUPPORTO
#include <vector>

namespace nostd
{
	template <typename T> class vector : public std::vector<T>
	{

	};
}
#endif
#endif
