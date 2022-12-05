#ifndef MATRIX
#define MATRIX

#include "numerical_analysis.hpp"

template<class T>
class matrix
{
private:
    int _nrow;                                      // Number of rows
    int _ncol;                                      // Number of columns
    T **_elems;                                     // Pointer to the data
public:
    /* Initializing the matrix */
    matrix();                                       // Default constructor
    matrix(int n, int m);                           // Construct (n x m) matrix
    matrix(int n, int m, const T &a);               // Initialize the matrix to constant value of a
    matrix(int n, int m, const T *a);               // Initialize to a C-style array
    matrix(const matrix<T> &othermatrix);           // Copy constructor
    matrix & operator=(const matrix &othermatrix);  // Assignment operator

    /* Adressing rows */
    inline T* operator[](const int i);              // Return pointer to i th row
    inline const T* operator[](const int i) const;      // const version. Called when vector is declared const. Look up on "const correctness"

    /* Information about the matrix */
    typedef T value_type;                           // Make T available
    inline int nrows(void) const;                   // Return the number of rows
    inline int ncols(void) const;                   // Return the number of columns

    /* Manipulating the matrix */
    void resize(int newn, int newm);                // Resize the matrix
    void assign(int newn, int newm, const T &a);    // Resize and assign 'a'


    ~matrix();
};


/* Adressing rows */
template<class T>
inline T* matrix<T>::operator[](const int i)
{
    // Checks wheter index is in bounds
#ifdef CHECKBOUNDS
    if (i < 0 || i >= _nrow)
    {
        throw index_out_of_bounds("Invalid row number referenced.");
    }
#endif

    return _elems[i];
}

template<class T>
inline  const T* matrix<T>::operator[](const int i) const
{
    // Checks wheter index is in bounds
#ifdef CHECKBOUNDS
    if (i < 0 || i >= _nrow)
    {
        throw index_out_of_bounds("Invalid row number referenced.");
    }
#endif

    return _elems[i];
}

/* Information about the matrix */
template<class T>
inline int matrix<T>::nrows(void) const
{
    return _nrow;
}

template<class T>
inline int matrix<T>::ncols(void) const
{
    return _ncol;
}

/* An override to define matrix out to stream */
template <class T>
std::ostream & operator<<(std::ostream &stream, const matrix<T> &mat)
{  
    stream << '{';

    // outputting matrix to stram
    for (int row = 0; row < mat.nrows(); row++)
    {
        if (row==0) {stream << "{";}
        else {stream << " {";}


        for (int col = 0; col < mat.ncols(); col++)
        {
            stream << std::setprecision(OUTPRECISION) << mat[row][col];

            if (col != (mat.ncols()-1)) {stream << " ,";}
        }
        if (row != (mat.nrows()-1)) {stream << "},\n";}
        else {stream << "}}\n";}
    }
    return stream;
}

// Typedefs to make the code simpler:
typedef matrix<char>                    MatChar;
typedef matrix<unsigned char>           MatUchar;
typedef matrix<int>                     MatInt;
typedef matrix<unsigned int>            MatUInt;
typedef matrix<long int>                MatLInt;
typedef matrix<long long int>           MatLLInt;
typedef matrix<unsigned long long int>  MatULLInt;
typedef matrix<double>                  MatDouble;
typedef matrix<long double>             MatLDouble;
typedef matrix<std::complex<double>>    MatCompex;


#endif // MATRIX