#include <ostream>

#ifndef NOSTD_STRING
#define NOSTD_STRING

#ifndef USE_STD_STRING

namespace nostd
{
	class string;
}

std::ostream& operator << (std::ostream& out, const nostd::string& s);

namespace nostd {
	class string {
		private:
			size_t _size;
			char* _buffer;
			void clear();

		public:
			string();
			string(const char *str);
			string(const string& other);
			~string();

			/* Capacity */
			size_t length() const;
			bool empty() const;

			/* Modifiers */
			void push_back(const char data);
			void pop_back();

			/* String operations */
			const char* c_str() const;

			/* Operator overloading */
			string& operator= (const char *s);
			string& operator= (const nostd::string& other);
			string& operator+ (const nostd::string& s1);
			const char& operator [](size_t pos) const;
			char& operator [](size_t pos);
			friend std::ostream& (::operator <<) (std::ostream& out, const nostd::string& s);

	};
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
