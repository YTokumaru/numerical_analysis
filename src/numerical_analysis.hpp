#ifndef NUMERICAL_ANALYSIS
#define NUMERICAL_ANALYSIS

/* Compile-time options: */

#define CHECKBOUNDS
#define CHECKMATSHAPE
#define PARALLEL        // Turn of or off according to your needs

#ifdef PARALLEL
#include <mpi.h>
#endif // PARALLEL



#include <iostream>
#include <complex>
#include <string.h>
#include <cmath>
#include <assert.h>
#include <iomanip>
#include <chrono>

using std::swap;

/* Global Constants */
const unsigned int OUTPRECISION = 16;       // precision used to output matrix / vector values to stream
const int INDEX_OUT_OF_BOUNDS = 1;
const int UNSOLVABLE = 2;
const int UNEXPECTED_SHAPE = 3; 

/* Macro-like inline functions */


/* Base exception class to handle errors */
class exception
{
    private:
    const std::string what;
    const int error_no;
    public:
    exception(const std::string &__what, const int _error_no): what(__what), error_no(_error_no) {}
    // ~exception()

    std::string message(void) const {return what;}
};

/* Scenario-specific errors */
class index_out_of_bounds: public exception
{
    public:
    index_out_of_bounds(const std::string &__what): exception(__what, INDEX_OUT_OF_BOUNDS) {}
    // ~out_of_bounds
};

class unexpected_shape: public exception
{
    public:
    unexpected_shape(const std::string &__what): exception(__what, UNEXPECTED_SHAPE) {}
    // ~unexpected shape
};

class unsolvable: public exception
{
public:
    unsolvable(const std::string &__what): exception(__what, UNSOLVABLE) {};
    // ~unsolvable();
};


#endif // NUMERICAL_ANALYSIS