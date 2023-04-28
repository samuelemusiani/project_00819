#include <ostream>
#include <istream>

#ifndef NOSTD_STRING
#define NOSTD_STRING

#ifndef USE_STD_STRING

namespace nostd
{
	class string;
}

bool operator== (const nostd::string& lhs, const nostd::string& rhs);
std::ostream& operator << (std::ostream& out, const nostd::string& s);
nostd::string operator+ (nostd::string lhs, const nostd::string& rhs);

namespace nostd {
	class string {
		private:
			size_t _size;
			size_t _capacity;
			char* _buffer;
			void clear();
			void reallocate(size_t new_capaciy);

		public:
			string();
			string(const char *str);
			string(const string& other);
			~string();

			/* Capacity */
			size_t length() const;
			size_t capacity() const;
			bool empty() const;

			/* Modifiers */
			void push_back(const char data);
			void pop_back();

			/* String operations */
			const char* c_str() const;
			string substr(size_t pos = 0) const;
			string substr(size_t pos, size_t len) const;

			/* Operator overloading */
			string& operator= (const char *s);
			string& operator= (const nostd::string& other);
			const char& operator[](size_t pos) const;
			char& operator[](size_t pos);
			string& operator+=(const nostd::string& rhs);

			// friend string (::operator+) (const nostd::string& s);
			friend bool (::operator==) (const string& lhs, const string& rhs);
			friend string (::operator+) (string lhs, const string& rhs);
			friend std::ostream& (::operator <<) (std::ostream& out, const nostd::string& s);

	};

	string to_string(int data);
	string to_string(double data);
	string to_string(char data);

	int stoi(nostd::string s);
	double stod(nostd::string s);

	/* Should I put this here? */
	std::istream& getline(std::istream& is, nostd::string& str, char delim = '\n');
}

#else //USO STD COME SUPPORTO

#include <string>

namespace nostd 
{
	class string : public std::string
	{
		public:
			string(const char* pippo); 
	};
}

#endif
#endif
