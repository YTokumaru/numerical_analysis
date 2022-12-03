#include "matrix.hpp"

/* Initializing the matrix */
template <class T>
matrix<T>::matrix(): nn(0), mm(0), v(nullptr) {}

template <class T>
matrix<T>::matrix(int n, int m): nn(n), mm(m), v(n>0? new T*[n]: nullptr)
{
    int i, nelm = n*m;
    if (v) v[0] = nelm>0? new T[nelm] : nullptr;
    for (i = 1; i < n; i++) v[i] = v[i-1] + m;
}

template <class T>
matrix<T>::matrix(int n, int m, const T &a): nn(n), mm(m), v(n>0? new T*[n]: nullptr)
{
    int i, j, nelm = n*m;
    if (v) v[0] = nelm>0? new T[nelm] : nullptr;
    for (i = 1; i < n; i++) v[i] = v[i-1] + m;

    for (i = 0; i < n; i++) for (j = 0; j < m; j++) v[i][j] = a;
}

template <class T>
matrix<T>::matrix(int n, int m, const T *a): nn(n), mm(m), v(n>0? new T*[n]: nullptr)
{
    int i, j, nelm = n*m;
    if (v) v[0] = nelm>0? new T[nelm] : nullptr;
    for (i = 1; i < n; i++) v[i] = v[i-1] + m;

    // Make sure that the size of a is same or longer than the matrix
    for (int i = 0; i < n; i++) for (j = 0; j < m; j++) v[i][j] = *a++;
}

template <class T>
matrix<T>::matrix(const matrix &othermatrix): nn(othermatrix.nn), mm(othermatrix.mm), v(nn>0? new T*[nn]: nullptr)
{
    int i, j, nelm = nn*mm;
    if (v) v[0] = nelm>0? new T[nelm] : nullptr;
    for (i = 1; i < nn; i++) v[i] = v[i-1] + mm;

    for (i = 0; i < nn; i++) for (j = 0; j < mm; j++) v[i][j] = othermatrix[i][j];
}

template <class T>
matrix<T> & matrix<T>::operator=(const matrix<T> &othermatrix)
{
    if (this != &othermatrix)
    {
        int i, j, nelm;
        if (nn != othermatrix.nn || mm != othermatrix.mm)
        {
            // If the size is not the same, free all data and reallocate them
            if(v)
            {
                delete[] (v[0]);
                delete[] (v);
            }
            nn = othermatrix.nn;
            mm = othermatrix.mm;
            v = nn>0? new T*[nn]: nullptr;
            nelm = nn*mm;

            if (v) v[0] = nelm>0? new T[nelm] : nullptr;
            for (i = 1; i < nn; i++) v[i] = v[i-1] + mm;
        }
        // copy the data
        for (i = 0; i < nn; i++) for (j = 0; j < mm; j++) v[i][j] = othermatrix[i][j];
    }
    return *this;
}

/* Destructor */
template <class T>
matrix<T>::~matrix()
{
    if (v)
    {
        delete[] (v[0]);
        delete[] (v);
    }
}

// Explicit template instantiation; add as needed
template class matrix<char>;
template class matrix<unsigned char>;
template class matrix<int>;
template class matrix<unsigned int>;
template class matrix<long int>;
template class matrix<long long int>;
template class matrix<unsigned long long int>;
template class matrix<double>;
template class matrix<long double>;
template class matrix<std::complex<double>>;