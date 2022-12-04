#include "linalg.hpp"

using namespace linalg;

MatDouble solve::gaussJ(MatDouble A, MatDouble B)
/* Implementation of Gauss-Jordan elimination
 * Applies same elementary row operation to both A and B, until A becomes a identity matrix.
 * By then B will have become the solution vector (or a set of solution vectors).
 * 
 * Assumes that A is a square matrix
 */
{
#ifdef CHECKMATSHAPE
    if (A.ncols() != A.nrows())
    {
        thorw("Expected a square matrix");
    }
#endif // CHECKMATSHAPE

    // TODO
    
}

MatDouble solve::gaussJ_backsub(MatDouble A, MatDouble B)
/* Implementation of Gauss-Jordan elimination with back substitution
 * Applies same elemantary row operation to both A and B, until A becomes a triangular matrix.
 * Then the solution vector (matrix) is calculated from bottom up.
 * Multiple vectors can be put into B for simultaneous solving.
 * 
 * Assumes that A is a square matrix.
 */
{
#ifdef CHECKMATSHAPE
    if (A.ncols() != A.nrows())
    {
        thorw("Expected a square matrix");
    }
#endif // CHECKMATSHAPE

    // TODO

}