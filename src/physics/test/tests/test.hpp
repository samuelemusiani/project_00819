/*
* Alma Mater Studiorum - University of Bologna
* First cycle degree in Computer Science
* Computer Programming - 00819
*
* Author: Musiani Samuele #0001069143
*
* test.hpp: All the defines used to print tests results.
*/

#include <iostream>

#ifndef TEST_FUNCTIONS
#define TEST_FUNCTIONS

#define TEST(X, Y, Z) if((X) != (Y)) {std::cerr << "\033[1;31m" << "TEST FALLITO! RIGA: " << __LINE__ << ". Il valore aspettato era: " << (X) << ", il valore ottenuto e'" << (Y) << "\033[0m\n" << "\n"; (Z) = false;}

#define TEST_APPROX(X, Z) if(!(X)) {std::cerr << "\033[1;31m" << "TEST FALLITO! RIGA: " << __LINE__ << "\033[0m\n" << "\n"; (Z) = false;}

#define CERR_RED(x) std::cerr << "\033[1;31m" << (x) << "\033[0m\n"
#define CERR_GREEN(x) std::cerr << "\033[1;32m" << (x) << "\033[0m\n"
#define CERR_YELLOW(x) std::cerr << "\033[1;33m" << (x) << "\033[0m\n"

#endif

bool point_test();
bool vector_test();
bool body_test();
