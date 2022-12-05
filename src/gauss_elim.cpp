#include "numerical_analysis.hpp"
#include "matrix.hpp"
#include "vector.hpp"
#include "linalg.hpp"

int main(int argc, char* argv[])
{
    /* Example code demonstrating Gauss-Jordan Elimination with back substitution */
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

    auto start = std::chrono::high_resolution_clock::now();

    MatDouble C = linalg::solve::gaussJ_backsub(A,B);

    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start);
    std::cout << C;
    std::cout << "Elapsed time: " << duration.count() << " microseconds\n";

    return 0;
}