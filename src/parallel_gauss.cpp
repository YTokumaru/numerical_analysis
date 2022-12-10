#include <mpi.h>
#include <iostream>
#include <cstdlib>

#include "numerical_analysis.hpp"
#include "matrix.hpp"
#include "vector.hpp"


int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of process
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    MatDouble A(3,3);
    A[0][0] = 3;
    A[0][1] = 1;
    A[0][2] = 2;
    A[1][0] = 5;
    A[1][1] = 1;
    A[1][2] = 3;
    A[2][0] = 4;
    A[2][1] = 2;
    A[2][2] = 1;

    MatDouble B(3,1);
    B[0][0] = 13;
    B[1][0] = 20;
    B[2][0] = 13;

    // std::cout << "Hello world from process " << my_rank << " out of " << world_size << std::endl;

    // Assign each column to processes
    int mycolnum = int(A.ncols() / world_size) + (my_rank!=0 ? int((A.ncols() % world_size) / my_rank):0);

    MatDouble mymat(A.nrows(), mycolnum);

    

    for (int i = 0; i < mycolnum; i++)
    {
        for (int row = 0; row < A.nrows(); row++)
        {
            mymat[row][i] = A[row][my_rank + i*world_size];
        }
    }
    
    // Debug:
    std::cout << "Process " << my_rank << " recieved vectors: \n" << mymat << std::endl;
    // Works!

    // Eliminate each row
    for (int delcol = 0; delcol < A.ncols(); delcol++)
    {
        double coef = 0;
        int pivrow = 0;
        VecDouble ratios(mymat.nrows() - delcol);


        // if the process has delrowth row, broadcast the information to other processes
        if (delcol % world_size == my_rank)
        {
            int mydelcol = delcol / world_size;    // mymat[mydelcol] is the row to delete
            
            // Fnid the largest element in mydelcol
            double max = 0.0;

            for (int i = delcol; i < mymat.nrows(); i++)
            {
                if (std::fabs(mymat[i][mydelcol]))
                {
                    max = mymat[i][delcol];
                    pivrow = i;
                }
                
            }
            if (max == 0.0)
            {
                // use MPI_Abort instead
                MPI_Abort(MPI_COMM_WORLD, 5);
                // throw unsolvable("While Gauss-Jordan eliminaton, encountered a column whose elements are all 0: A is a singular matrix");
            }

            // send to other processe:
            //  the row number of the pivot 
            //  the ratio of mymat[i][mydelcol] / mymat[pivrow][mydelcol]
            //  all the processes will pivot first, then will eliminate elements
            
            // Vector containing the ratios
            for (int i = 0; i < ratios.size(); i++)
            {
                ratios[i] = mymat[i][mydelcol] / mymat[pivrow][mydelcol];
            }

            coef = mymat[delcol][mydelcol];
            
            
        }
        MPI_Barrier(MPI_COMM_WORLD);
        MPI_Bcast(&coef, 1, MPI_DOUBLE, delcol % world_size, MPI_COMM_WORLD);
        MPI_Bcast(&pivrow, 1, MPI_INT, delcol % world_size, MPI_COMM_WORLD);
        MPI_Bcast(&ratios[0], ratios.size(), MPI_DOUBLE, delcol % world_size, MPI_COMM_WORLD);

        // eliminate elements using pivrow and ratios
        // first, swap the rows
        for (int col = 0; col < mymat.ncols(); col++)
        {
            swap(mymat[pivrow][col], mymat[delcol][col]);
        }
        for (int col = 0; col < B.ncols(); col++)
        {
            swap(B[pivrow][col], B[delcol][col]);
        }

        // Apply same elementary row operation
        for (int row = 0; row < A.nrows(); row++)
        {
            if (row==delcol)
            {
                continue;
            }

            for (int j = 0; j < mymat.ncols(); j++)
            {
                mymat[row][j] -= mymat[delcol][j] * ratios[j];
            }
            for (int j = 0; j < B.ncols(); j++)
            {
                B[row][j] -= B[delcol][j] * ratios[j];
            }
        }
        
        // divide by coef
        for (int col = 0; col < mymat.ncols(); col++)
        {
            mymat[delcol][col] /= coef;
        }
        //Divide B
        for (int col = 0; col < B.ncols(); col++)
        {
            B[delcol][col] /= coef;
        }
        
    }
    
    std::cout << B;

    MPI_Finalize();

    return EXIT_SUCCESS;
}