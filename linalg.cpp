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

    // TODO

    int n = A.ncols();              // Beyond this line, n is the number of columns (and rows)

    VecInt track(n, n);           // Initialize the tracking vector with values n  
    // This vector keeps track of which row was used as a pivot. (row and column number start at 0)
    // When track[0] == 0, this means that the 0th row was used as a pivot to eliminate 0th column.
    // When track[3] == 1, this means that the 3th row was used as a pivot to eliminate 1th column.
    // When track[p] == q, this means that the pth row was used as a pivot to eliminate qth colums.

    for (int delcol = 0; delcol < n; delcol++)
    {
        /* Step 1: Find a suitable pivot for eliminating column 'delcol'. If all values withn a column is 0, throw error: unsolvable */
        // a loop for finding the largest element
        double max = 0;                 // Variable storing the largest element found
        int pivrow = n;               // Variable storing the row the largest element belong to
        for (int i = 0; i < n; i++)
        {
            // skip rows that are already used as pivots
            if (track[i] != n) {continue;}

            if (std::fabs(A[i][delcol]) > max)
            {
                max = A[i][delcol];
                pivrow = i;
            }
        }
        if (max == 0.0)
        {
            throw unsolvable("While Gauss-Jordan eliminaton, encountered a column whose elements are all 0.");
        }

        /* Step 2: Delete rows that are not already used as pivots */
        track[pivrow] = delcol;         // Record the fact that row pivrow is going to be used to eliminate column delcol
        for (int i = 0; i < n; i++)
        {
            // Eliminate rows that are not used as pivots
            if (track[i] == n)
            {
                // Work out how much multiplicaion is required
                double ratio = A[i][delcol]/A[pivrow][delcol];          // A[pivrow][delcol] can be computed outside the loop hence saving computing time

                for (int j = 0; j < n; j++)
                {
                    A[i][j] -= A[pivrow][j]*ratio;
                }
                // Do the same for the matrix on the right hand side
                for (int k = 0; k < B.ncols(); k++)         // this loop is unnecessary when B has the same shape as A (i.e when calculating the inverse) 
                {
                    B[i][k] -= B[pivrow][k]*ratio;
                }
            }
        }
    }
    
    /* Step 3: Begin backsubstitution */
    // now that A is reduced to a triangular matrix (though its rows are all mixed up), we can begin backsubstitution

    for (int pivorder = n-1; pivorder >= 0; pivorder--)
    {
        // Get the pivot row numbers in the reverse order
        int pivrow = track.find(pivorder);      // The row we want to solve for
        assert(pivrow == pivrow);               // Pivrow should not be NaN at any point in this loop, but just to make sure

        double coef = A[pivrow][pivorder];      // Coeffivient of the unknown that we want to solve for
        //Subtract constants
        for (int col_num = n-1; col_num > pivorder; col_num--)
        {
            // TODO: Something is going wrong here
            for (int checkrow = 0; checkrow < n; checkrow++)
            {
                if(track[checkrow] >= n)         // check if the row has already been solved
                {
                    for (int b_col_num = 0; b_col_num < B.ncols(); b_col_num++)
                    {
                        B[pivrow][b_col_num] -= A[pivrow][checkrow-n] * B[checkrow][b_col_num];   // Subtracting the known constants from previously earned results
                    }
                }
            }
            
        }
        // Divide the row with the coefficient
        for (int i = 0; i < B.ncols(); i++)
        {
            B[pivrow][i] = B[pivrow][i] / coef;
        }

        track[pivrow] += n;      // Record that 'pivrow' has been solved   
    }
    return B;

}