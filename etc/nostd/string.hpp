#ifndef NOSTD_STRING
#define NOSTD_STRING

namespace nostd {
    class string {
        private:
            int size;
            char* buffer;
            void clear();
    public:
            string();
            string(const char* str);
            ~string();
            string& operator= (const char* s);
            int length();
            char* c_str();
            int stoi();
            double stod();
            bool is_empty();
    };

    string::string() : string(nullptr)
    {

    }

    string::string(const char *str)
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

    string::~string()
    {
        this->clear();
    }

    string& string::operator=(const char* s) {
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

    int string::length()
    {
        return this->size;
    }

    int string::stoi()
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

    double string::stod()
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

    char* string::c_str()
    {
        return this->buffer;
    }

    void string::clear()
    {
        delete[] this->buffer;
        this->buffer = nullptr;
        this->size = 0;
    }

    bool string::is_empty()
    {
        if(this->size > 0)
            return false;
        else
            return true;
    }

}

#endif