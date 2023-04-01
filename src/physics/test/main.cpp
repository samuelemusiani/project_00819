#include "test.hpp"

int main()
{
	bool generale = true;

	generale &= point_test();
	generale &= vector_test();

	if (generale)
		CERR_GREEN("TUTTO OK");
	else
		CERR_RED("ALCUNI TEST SONO FALLITI" );
	return 0;
}
