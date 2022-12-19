#ifndef LINALG
#define LINALG

#include "numerical_analysis.hpp"
#include "matrix.hpp"
#include "vector.hpp"

namespace linalg
{
    // template <class T>
    MatInt matmul(MatInt A, MatInt B);             // TODO
    // TODO make sure that this works for complex numbers as well
    /*
     * A function that calculates the multiplication two matricies
     *
     * Can be called both in serial and parallel
     */

    namespace solve
    {
        // Methods to solve linear equations
        MatDouble gaussJ(MatDouble a, MatDouble b);
        /* 
         * Implementation of Gauss-Jordan Elimination
         * not the optimal algorithm to solve sets of linear equations,
         * but is simple and applicable to other problems
         * 
         * Can be called both in serial and in parallel             // TODO
         */

        MatDouble gaussJ_backsub(MatDouble a, MatDouble b);
        /*
         * Implementation of Gauss-Jordan Elimination with back substitution
         * Has the potential to solve sets of linear equations faster than
         * normal Gauss-Jordan Elimination, but difficlut to solve other problems
         */

    }

    namespace inverse
    {
        MatDouble gaussJ(MatDouble a);                          // Gaus-Jordan elimination
    }
}

#endif //LINALG