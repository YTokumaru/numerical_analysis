#include "numerical_analysis.hpp"
#include "matrix.hpp"
#include "vector.hpp"
#include "linalg.hpp"

int main(int argc, char* argv[])
{
    /* Example code demonstrating Gauss-Jordan Elimination with back substitution */

    // Solving Ax = B

    constexpr int N = 5;        // The number of unknowns to solve for

    std::random_device devrand;     // Random number from hardware(seed)
    std::mt19937 gen(devrand());    // Give generator the seed
    std::uniform_int_distribution<> distr(-100,100);       // Range of the random number

    // Make the solution vector
    MatInt solvec(N,1);
    for (int i = 0; i < N; i++)
    {
        solvec[i][0] = distr(gen);
    }

    // Make the Matrix
    MatInt IntA(N,N);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            IntA[i][j] = distr(gen);
        }
    }

    // Calculte the vector on the right hand side
    MatInt IntB(N,1);

    IntB = linalg::matmul(IntA,solvec);

    // Now, convert IntA and IntB in to double
    MatDouble A(N,N);
    MatDouble B(N,1);
    A = IntA;
    B = IntB;

    // Solve the equation using A and B
    MatDouble calced_ans;

    // Solve the equation and time it
    auto start = std::chrono::high_resolution_clock::now();
    calced_ans = linalg::solve::gaussJ_backsub(A,B);
    auto stop = std::chrono::high_resolution_clock::now();
    
    // Output the answer to the console
    std::cout << "A is:\n" << IntA << "\n" << "B is:\n" << B << '\n';
    std::cout << "The expected solution was:\n " << solvec << "\nwhile the calculated solution was: \n" << calced_ans << '\n';

    // Output the time required to solve the calculation
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start);
    std::cout << "Elapsed time: " << duration.count() << " microseconds\n";


    return 0;
}