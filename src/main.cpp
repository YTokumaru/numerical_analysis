#include "numerical_analysis.hpp"
#include "matrix.hpp"
#include "vector.hpp"
#include "linalg.hpp"

int main(int argc, char* argv[])
{
    
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

    MatDouble C = linalg::solve::gaussJ_backsub(A,B);

    std::cout << C;

    return 0;
}