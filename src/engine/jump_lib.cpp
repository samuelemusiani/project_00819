#include <cmath>

double m_exp(double d) {
	if (d >= 0) return exp(d);
	else return 1/exp(-d);
}

double jump_function(int n) {
    return (1/(1+m_exp(-0.18 * (n - 8)))*5);
}
