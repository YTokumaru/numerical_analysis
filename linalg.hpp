#ifndef LINALG
#define LINALG

#include "numerical_analysis.hpp"
#include "matrix.hpp"

namespace linalg
{
    namespace solve
    {
        // Methods to solve linear equations

        MatDouble gaussJ(MatDouble a, MatDouble b);             // Gauss-Jordan elimination

        MatDouble gaussJ_backsub(MatDouble a, MatDouble b);     // Gauss-Jordan elimination with back-substitution
    }

    namespace inverse
    {
        MatDouble gaussJ(MatDouble a);                          // Gaus-Jordan elimination
    }
}

#endif //LINALG