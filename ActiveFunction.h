// ActiveFunction.h

#ifndef ACTIVEFUNCTION_H
#define ACTIVEFUNCTION_H 0

#include "Matrix.h"

inline double sigmod(double x)
{
	return 1.0 / (1.0 + exp(-x));
}

inline double sigmod_Derivative(double x)
{
	return sigmod(x) * (1 - sigmod(x));
}

inline double tanh(double x)
{
	return (exp(x) - exp(-x)) / (exp(x) + exp(-x));
}

inline double tanh_Derivative(double x)
{
	return (2. / (exp(x) + exp(-x))) * (2. / (exp(x) + exp(-x)));
}

#endif //ACTIVEFUNCTION_H