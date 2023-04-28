#include "string.hpp"
#include <cstring>
#include <cmath>

#ifndef USE_STD_STRING

	/* PRIVATE */

void nostd::string::clear()
{
	delete[] this->_buffer;
	reallocate(1);
	this->_size = this->_capacity - 1;
	this->_buffer[0] = '\0';
}

void nostd::string::reallocate(size_t new_capaciy)
{
	if (new_capaciy >= 1 && this->_capacity != new_capaciy)
	{
		char* tmp = new char[new_capaciy];

		this->_size = std::min(this->_size, new_capaciy - 1);

		std::memcpy(tmp, this->_buffer, std::min(this->_capacity, new_capaciy) * sizeof(char));

		delete[] this->_buffer;

		this->_buffer = tmp;
		this->_capacity = new_capaciy;
	}
}

	/* PUBLIC */

nostd::string::string() 
	: string(nullptr)
{

}

nostd::string::string(const char *str)
	: _buffer(nullptr), _size(0), _capacity(0)
{
	if(str != nullptr)
	{
		reallocate(strlen(str) + 1);
		this->_size = this->_capacity - 1;
		std::memcpy(this->_buffer, str, this->_capacity * sizeof(char));
	}
	else
	{
		reallocate(1);
		this->_size = this->_capacity - 1;
	}

	this->_buffer[this->_size] = '\0';
}

nostd::string::string(const string& other)
{
	this->_size = other._size;
	this->_capacity = other._capacity;
	this->_buffer = new char[this->_capacity];
	std::memcpy(this->_buffer, other._buffer, this->_capacity * sizeof(char));
}

nostd::string::~string()
{
	delete[] this->_buffer;
}

size_t nostd::string::length() const
{
	return this->_size;
}

size_t nostd::string::capacity() const
{
	return this->_capacity;
}

bool nostd::string::empty() const
{
	return (this->_size == 0);
}


void nostd::string::push_back(const char data)
{
	this->_size++; 

	if(this->_size >= this->_capacity)
	{
		this->_capacity = this->_size + 5;
		reallocate(this->_capacity);
	}

	this->_buffer[this->_size - 1] = data;
	this->_buffer[this->_size] = '\0';
}

void nostd::string::pop_back()
{
	if(this->_size > 0)
	{
		this->_size--;
		if (this->_size + 20 < this->_capacity)
		{
			reallocate(this->_size + 5);
			this->_size;
		}
	}
}

const char* nostd::string::c_str() const
{
	return this->_buffer;
}

nostd::string nostd::string::substr(size_t pos) const
{
	return this->substr(pos, this->_size);
}

nostd::string nostd::string::substr(size_t pos, size_t len) const
{
	nostd::string s;

	int i = 0;
	while(pos + i < this->_size && i < len)
	{
		s.push_back(this->_buffer[pos + i]);
		i++;
	}
	
	return s;
}

const char* nostd::string::c_str() const
{
	return this->_buffer;
}

nostd::string& nostd::string::operator= (const char* s)
{
	reallocate(strlen(s) + 1);
	this->_size = this->_capacity - 1;

	std::memcpy(this->_buffer, s, this->_size * sizeof(char));
	this->_buffer[this->_size] = '\0';

	return *this;
}

nostd::string& nostd::string::operator= (const nostd::string& other)
{
	if(this != &other)
	{
		reallocate(other._capacity);
		this->_size = other._size;

		std::memcpy(this->_buffer, other._buffer, this->_capacity * sizeof(char));
	}

	return *this;
}

const char& nostd::string::operator [](size_t pos) const
{
	return this->_buffer[pos];
}

char& nostd::string::operator [](size_t pos)
{
	return this->_buffer[pos];
}

nostd::string& nostd::string::operator+= (const nostd::string& rhs)
{
	size_t tmp_size = this->_size + rhs._size;
	char* tmp_buffer = new char[tmp_size + 1];

	std::memcpy(tmp_buffer, this->_buffer, this->_size * sizeof(char));
	std::memcpy(tmp_buffer + this->_size * sizeof(char), rhs._buffer, rhs._size * sizeof(char));

	tmp_buffer[tmp_size] = '\0';

	delete[] this->_buffer;
	this->_buffer = tmp_buffer;
	this->_size += tmp_size;
	this->_capacity = this->_size + 1;
	return *this;
}

bool operator== (const nostd::string& lhs, const nostd::string& rhs)
{
	if(lhs._size != rhs._size)
		return false;
	else
	{
		int i = 0;
		bool notEqual = false;

		while(i < lhs._size && !notEqual)
		{
			if(lhs._buffer[i] != rhs._buffer[i])
				notEqual = true;
			i++;
		}

		return !notEqual;
	}
}

nostd::string operator+ (nostd::string lhs, const nostd::string& rhs)
{	
	lhs += rhs;
	return lhs;
}



std::ostream& operator<<(std::ostream &out, const nostd::string &s) {
	out << s._buffer;
	return out;
}

nostd::string nostd::to_string(int data)
{

	nostd::string s;

	if (data == 0)
		s.push_back('0');
	else
	{
		if (data < 0)
		{
			s.push_back('-');
			data = -data;
		}

		int size = ceil(log(data) / log(10));
		if(data % (int) pow(10, size) == 0) size++;

		int ipow = pow(10, size - 1);
		for(int i = 0; i < size; i++)
		{
			s.push_back(data / ipow + '0');
			data %= ipow;
			ipow /= 10;
		}
	}
	return s;
}

nostd::string nostd::to_string(double data)
{
	const int precision = 5;

	nostd::string s = nostd::to_string((int) data);
	data = data - (int) data;
	data = round(data * pow(10, precision));
	s.push_back('.');
	s += nostd::to_string((int) data);
	return s;
}

nostd::string nostd::to_string(char data)
{
	nostd::string s;
	s.push_back(data);
	return s;
}

int nostd::stoi(nostd::string s)
{
    int result = 0;
    bool negative = false;
    int i = 0;

    if (s[0] == '-')
    {
        negative = true;
        i = 1;
    }

    for (; i < s.length(); i++)
    {
        result *= 10;
        result += (int) (s[i] - '0');
    }

    if(negative)
        result = -result;

    return result;
}

double nostd::stod(nostd::string s)
{
    double result = 0.0;
    double decimal = 1.0;
    bool negative = false;
    int i = 0;

    if (s[0] == '-')
    {
        negative = true;
        i++;
    }

    while(i < s.length() && s[i] != '.')
    {
        result *= 10.0;
        result += (double) s[i] - '0';
        i++;
    }

    if(s[i] == '.')
        i++;

    while(i < s.length())
    {
        decimal *= 10.0;
        result += (double) ((s[i] - '0') / decimal);
        i++;
    }

    if(negative)
        result = -result;

    return result;
}

std::istream& nostd::getline(std::istream& is, nostd::string& str, char delim)
{
	const int MAX_DIM = 2048;
	char buff[MAX_DIM];

	is.getline(buff, MAX_DIM, delim);
	str = buff;

	return is;
}

#else

nostd::string::string(const char* pippo)
	: std::string(pippo)
{

}

#endif
