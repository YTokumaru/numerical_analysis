#include"numerical_analysis.hpp"
#include"matrix.hpp"

int main(int argc, char* argv[])
{
    double x[2][2] = {{1.0,2.0},{3.0,4.0}};
    MatDouble a(2,2, *x);
    for (int i = 0; i < a.nrows(); i++)
    {
        for (int j = 0; j < a.ncols(); j++)
        {
            std::cout << a[i][j] << " ";
        }
        std::cout << "\n";
    } 

    return 0;
}