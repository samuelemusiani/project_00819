/*
* Alma Mater Studiorum - University of Bologna
* First cycle degree in Computer Science
* Computer Programming - 00819
*
* Author: Musiani Samuele #0001069143
*
* main.cpp: Main file for all the computation tests.
*/

#include "../test.hpp"

int main()
{
	bool generale = true;

	generale &= point_test();
	generale &= vector_test();
	generale &= body_test();

	if (generale)
		CERR_GREEN("TUTTO OK");
	else
		CERR_RED("ALCUNI TEST SONO FALLITI" );
	return 0;
}
