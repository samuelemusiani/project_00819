#include "string.hpp"

#ifndef USE_STD
nostd::string::string() : string(nullptr)
{

}

nostd::string::string(const char *str)
{
    this->buffer = nullptr;
    this->size = 0;
    if(str != nullptr)
        while (str[this->size] != '\0')
            this->size++;
    if(this->size >= 0)
        this->buffer = new char[this->size + 1];
    for (int i = 0; i < this->size; i++)
        this->buffer[i] = str[i];
    this->buffer[this->size] = '\0';
}

nostd::string::~string()
{
    this->clear();
}

nostd::string& nostd::string::operator=(const char* s) {
    if (this->buffer != nullptr)
        this->clear();
    while (s[this->size] != '\0')
        this->size++;
    this->buffer = new char[this->size + 1];
    for (int i = 0; i < this->size; i++)
        this->buffer[i] = s[i];
    this->buffer[this->size] = '\0';
    return *this;
}

namespace nostd { /* it doesn't work without this line, idk why */
    std::ostream &operator<<(std::ostream &out, const nostd::string &s) {
        out << s.buffer;
        return out;
    }
}

int nostd::string::length()
{
    return this->size;
}

int nostd::string::stoi()
{
    int result = 0;
    bool negative = false;
    int i = 0;
    if (this->buffer[0] == '-')
    {
        negative = true;
        i = 1;
    }
    for (; i < this->size; i++)
    {
        result *= 10;
        result += (int)this->buffer[i] - 48; /* 48 is the ASCII code for number 0 */
    }
    if(negative)
        result *= -1;
    return result;
}

double nostd::string::stod()
{
    double result = 0.0;
    double decimal = 1.0;
    bool negative = false;
    int i = 0;
    if (this->buffer[0] == '-')
    {
        negative = true;
        i++;
    }
    while(i<this->size && this->buffer[i] != '.')
    {
        result *= 10.0;
        result += (double)this->buffer[i] - 48;
        i++;
    }
    if(this->buffer[i] == '.')
        i++;
    while(i < this->size)
    {
        decimal *= 10.0;
        result += (double)((this->buffer[i] - 48) / decimal);
        i++;
    }
    if(negative)
        result *= -1.0;
    return result;
}

const char* nostd::string::c_str()
{
    return this->buffer;
}

void nostd::string::clear()
{
    delete[] this->buffer;
    this->buffer = nullptr;
    this->size = 0;
}

bool nostd::string::is_empty()
{
    return (this->size == 0);
}
#else

nostd::string::string() : string(nullptr)
{

}

nostd::string::string(const char *str)
{
	this->s = str;
}

nostd::string& nostd::string::operator=(const char* s) {
	this->s = s;
	return *this;
}

namespace nostd { /* it doesn't work without this line, idk why */
    std::ostream &operator<<(std::ostream &out, const nostd::string &s) {
        out << s.s;
        return out;
    }
}

int nostd::string::length()
{
    return this->s.length();
}

const char* nostd::string::c_str()
{
    return this->s.c_str();
}

bool nostd::string::is_empty()
{
    return this->s.empty();
}
#endif
