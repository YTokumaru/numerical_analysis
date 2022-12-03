#ifndef NUMERICAL_ANALYSIS
#define NUMERICAL_ANALYSIS

#define CHECKBOUNDS


#include <iostream>
#include <complex>
#include <cmath>

/* Error and exception */
#define thorw(message) \
    {printf("ERROR: %s\n in file %s at line %d\n", \
            message, __FILE__,__LINE__); \
            exit(1);}



#endif // NUMERICAL_ANALYSIS