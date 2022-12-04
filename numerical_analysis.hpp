#ifndef NUMERICAL_ANALYSIS
#define NUMERICAL_ANALYSIS

#define CHECKBOUNDS
#define CHECKMATSHAPE


#include <iostream>
#include <complex>
#include <cmath>

using std::abs;

/* Error and exception */
#define thorw(message) \
    {printf("ERROR: %s\n in file %s at line %d\n", \
            message, __FILE__,__LINE__); \
            exit(1);}



#endif // NUMERICAL_ANALYSIS