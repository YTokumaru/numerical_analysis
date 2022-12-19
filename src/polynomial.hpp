#ifndef POLYNOMIAL
#define POLYNOMIAL

#include "numerical_analysis.hpp"

namespace polynomial
{
    namespace root
    // Various methods to calculate the root of a ploynomial
    {
        double bisection(double (*f)(double), double a, double b);          // TODO
        /* 
         * An implementation of the bisection method
         * Calculates one of the root that reside between a and b. 
         * Based on the intermediate value theorem. 
         */
    }
}

#endif // POLYNOMIAL