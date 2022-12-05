#ifndef NUMERICAL_ANALYSIS
#define NUMERICAL_ANALYSIS

#define CHECKBOUNDS
#define CHECKMATSHAPE


#include <iostream>
#include <complex>
#include <string.h>
#include <cmath>
#include <assert.h>
#include <iomanip>


/* Macro-like inline functions */
template<class T>
inline void swap(T &a, T &b)
{
    T dummy;
    dummy = a;
    a = b;
    b = dummy;
}

/* Base exception class to handle errors */
class exception
{
    private:
    const std::string what;
    public:
    exception(const std::string &__what): what(__what) {}
    // ~exception()

    std::string message(void) const {return what;}
};

/* Scenario-specific errors */
class index_out_of_bounds: public exception
{
    public:
    index_out_of_bounds(const std::string &__what): exception(__what) {}
    // ~out_of_bounds
};

class unexpected_shape: public exception
{
    public:
    unexpected_shape(const std::string &__what): exception(__what) {}
    // ~unexpected shape
};

class unsolvable: public exception
{
public:
    unsolvable(const std::string &__what): exception(__what) {};
    // ~unsolvable();
};


#endif // NUMERICAL_ANALYSIS