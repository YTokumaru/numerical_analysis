#ifndef LINALG
#define LINALG

#include "numerical_analysis.hpp"
#include "matrix.hpp"
#include "vector.hpp"

namespace linalg
{
    namespace solve
    {
        // Methods to solve linear equations
        template<class T>
        void gaussJ(matrix<T> &a, matrix<T> &b);

        template<class T>
        matrix<T> gaussJ_backsub(matrix<T> a, matrix<T> b);
    }
}

#endif //LINALG