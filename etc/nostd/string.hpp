#include <ostream>

#ifndef NOSTD_STRING
#define NOSTD_STRING

namespace nostd {
    class string {
        private:
            int size;
            char *buffer;
            void clear();
        public:
            string();
            string(const char *str);
            ~string();
            string &operator=(const char *s);
            friend std::ostream& operator<<(std::ostream& out, const string& s);
            int length();
            char *c_str();
            int stoi();
            double stod();
            bool is_empty();
    };
}

#endif
