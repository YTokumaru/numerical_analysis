#include "linalg.hpp"

using namespace linalg;

MatDouble solve::gaussJ(MatDouble A, MatDouble B)
/* Implementation of Gauss-Jordan elimination
 * Applies the same elementary row operation to both A and B, until A becomes a identity matrix.
 * By then B will have become the solution vector (or a set of solution vectors).
 * 
 * Assumes that A is a square matrix
 */
{
#ifdef CHECKMATSHAPE
    if (A.ncols() != A.nrows())
    {
        throw unexpected_shape("Expected a square matrix, but did not.");
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
        throw unexpected_shape("Expected a square matrix, but did not.");
    }
    if (A.nrows() != B.nrows())
    {
        throw unexpected_shape("Expected A and B to have the same number of rows but they do not.");
    }
    
#endif // CHECKMATSHAPE

    int n = A.ncols();              // Beyond this line, n is the number of columns for A (and rows for A and B)

    for (int delcol = 0; delcol < n; delcol++)
    {
        /* Step 1: Find a suitable pivot for eliminating column 'delcol'. If all values withn a column is 0, throw error: unsolvable */
        // delcol is the column number of the column we are trying to eliminate.
        // all elements below delcol-th row must be 0 after the operation
        // a loop for finding the largest element below delcol th row
        double max = 0;                 // Variable storing the largest element found
        int pivrow = n;                 // Variable storing the row the largest element belong to
        for (int i = delcol; i < n; i++)
        {
            if (std::fabs(A[i][delcol]) > max)
            {
                max = A[i][delcol];
                pivrow = i;
            }
        }
        if (max == 0.0)
        {
            throw unsolvable("While Gauss-Jordan eliminaton, encountered a column whose elements are all 0: A is a singular matrix");
        }

        // Swap the pivrow with delcol-th row
        // Swap A
        for (int j = 0; j < n; j++)
        {
            swap(A[pivrow][j], A[delcol][j]);
        }
        // Swap B
        for (int j = 0; j < B.ncols(); j++)
        {
            swap(B[pivrow][j], B[delcol][j]);
        }
        
        /* Step 2: Apply the same elementary row opertation to both A and B to eliminate elements of delcol below the delcol-th row*/
        for (int row = delcol + 1; row < n; row++)
        {
            double ratio = A[row][delcol] / A[delcol][delcol];

            // Apply row operation to A
            for (int j = 0; j < n; j++)
            {
                A[row][j] -= A[delcol][j] * ratio;
            }
            // Apply row operation to B
            for (int j = 0; j < B.ncols(); j++)
            {
                B[row][j] -= B[delcol][j] * ratio;
            }
        }
    }
    /* Step 3: Backsubstitution */
    // solve for the unkowns from the bottom up

    for (int solverow = n-1; solverow >= 0; solverow--)
    {
        double coef = A[solverow][solverow];            // Coefficient of the unkown we want to solve for

        // From the unkowns we previously solved for, work out the constant value on the left hand side of the equation
        // and subtract it from the right
        for (int i = n-1; i > solverow; i--)        // Note that 'i' here can both mean row number and column number
        {
            for (int col = 0; col < B.ncols(); col++)
            {
                B[solverow][col] -= A[solverow][i] * B[i][col];
            }
        }

        // Divide solverow by coef to make B the solution
        for (int col = 0; col < B.ncols(); col++)
        {
            B[solverow][col] /= coef;
        }
    }
    return B;
}