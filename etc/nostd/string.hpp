/*
 * Alma Mater Studiorum - University of Bologna
 * First cycle degree in Computer Science
 * Computer Programming - 00819
 *
 * Author: Musiani Samuele #0001069143
 * Author: Peronese Lorenzo #0001081726
 *
 * string.hpp: Personal implementation of
 * the C++ standard library's string
 */

#include <istream>
#include <ostream>

#ifndef NOSTD_STRING
#define NOSTD_STRING
namespace nostd {
class string;
}

bool operator==(const nostd::string &lhs, const nostd::string &rhs);
std::ostream &operator<<(std::ostream &out, const nostd::string &s);
nostd::string operator+(nostd::string lhs, const nostd::string &rhs);

namespace nostd {
class string {
private:
  size_t _size;
  size_t _capacity;
  char *_buffer;
  void clear();
  void reallocate(size_t new_capaciy);

public:
  string();
  string(const char *str);
  string(const string &other);
  ~string();

  /* Capacity */
  size_t length() const;
  size_t capacity() const;
  bool empty() const;

  /* Modifiers */
  void push_back(const char data);
  void pop_back();

  /* String operations */
  const char *c_str() const;
  string substr(size_t pos = 0) const;
  string substr(size_t pos, size_t len) const;

  size_t find(const nostd::string &str, size_t pos = 0) const;
  size_t find(const char *s, size_t pos = 0) const;
  size_t find(const char *s, size_t pos, size_t n) const;
  size_t find(char c, size_t pos = 0) const;

  /* Operator overloading */
  string &operator=(const char *s);
  string &operator=(const nostd::string &other);
  const char &operator[](size_t pos) const;
  char &operator[](size_t pos);
  string &operator+=(const nostd::string &rhs);

  // friend string (::operator+) (const nostd::string& s);
  friend bool(::operator==)(const string &lhs, const string &rhs);
  friend string(::operator+)(string lhs, const string &rhs);
  friend std::ostream &(::operator<<)(std::ostream &out,
                                      const nostd::string &s);
};

string to_string(int data);
string to_string(double data);
string to_string(char data);

int stoi(nostd::string s);
double stod(nostd::string s);

/* Should I put this here? */
std::istream &getline(std::istream &is, nostd::string &str, char delim = '\n');
} // namespace nostd
#endif
