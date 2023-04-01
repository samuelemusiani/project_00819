#include <iostream>

#ifndef TEST_FUNCTIONS
#define TEST_FUNCTIONS

#define TEST(X, Y, Z) if((X) != (Y)) {std::cerr << "\033[1;31m" << "TEST FALLITO! RIGA: " << __LINE__ << "\033[0m\n" << "\n"; (Z) = false;}

#define TEST_APPROX(X, Z) if(!(X)) {std::cerr << "\033[1;31m" << "TEST FALLITO! RIGA: " << __LINE__ << "\033[0m\n" << "\n"; (Z) = false;}

#define CERR_RED(x) std::cerr << "\033[1;31m" << (x) << "\033[0m\n"
#define CERR_GREEN(x) std::cerr << "\033[1;32m" << (x) << "\033[0m\n"
#define CERR_YELLOW(x) std::cerr << "\033[1;33m" << (x) << "\033[0m\n"

#endif

bool point_test();
bool vector_test();
