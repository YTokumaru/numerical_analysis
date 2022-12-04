#include "matrix.hpp"

/* Initializing the matrix */
template <class T>
matrix<T>::matrix(): nrow(0), ncol(0), elems(nullptr) {}

template <class T>
matrix<T>::matrix(int n, int m): nrow(n), ncol(m), elems(n>0? new T*[n]: nullptr)
{
    int i, nelm = n*m;
    if (elems != nullptr) elems[0] = nelm>0? new T[nelm] : nullptr;
    for (i = 1; i < n; i++) elems[i] = elems[i-1] + m;
}

template <class T>
matrix<T>::matrix(int n, int m, const T &a): nrow(n), ncol(m), elems(n>0? new T*[n]: nullptr)
{
    int i, j, nelm = n*m;
    if (elems != nullptr) elems[0] = nelm>0? new T[nelm] : nullptr;
    for (i = 1; i < n; i++) elems[i] = elems[i-1] + m;

    for (i = 0; i < n; i++) for (j = 0; j < m; j++) elems[i][j] = a;
}

template <class T>
matrix<T>::matrix(int n, int m, const T *a): nrow(n), ncol(m), elems(n>0? new T*[n]: nullptr)
{
    int i, j, nelm = n*m;
    if (elems != nullptr) elems[0] = nelm>0? new T[nelm] : nullptr;
    for (i = 1; i < n; i++) elems[i] = elems[i-1] + m;

    // Make sure that the size of a is same or longer than the matrix
    for (int i = 0; i < n; i++) for (j = 0; j < m; j++) elems[i][j] = *a++;
}

template <class T>
matrix<T>::matrix(const matrix<T> &othermatrix): nrow(othermatrix.nrow), ncol(othermatrix.ncol), elems(nrow>0? new T*[nrow]: nullptr)
{
    int i, j, nelm = nrow*ncol;
    if (elems != nullptr) elems[0] = nelm>0? new T[nelm] : nullptr;
    for (i = 1; i < nrow; i++) elems[i] = elems[i-1] + ncol;

    for (i = 0; i < nrow; i++) for (j = 0; j < ncol; j++) elems[i][j] = othermatrix[i][j];
}

template <class T>
matrix<T> & matrix<T>::operator=(const matrix<T> &othermatrix)
{
    if (this != &othermatrix)
    {
        int i, j, nelm;
        if (nrow != othermatrix.nrow || ncol != othermatrix.ncol)
        {
            // If the size is not the same, free all data and reallocate them
            if(elems != nullptr)
            {
                delete[] (elems[0]);
                delete[] (elems);
            }
            nrow = othermatrix.nrow;
            ncol = othermatrix.ncol;
            elems = nrow>0? new T*[nrow]: nullptr;
            nelm = nrow*ncol;

            if (elems != nullptr) elems[0] = nelm>0? new T[nelm] : nullptr;
            for (i = 1; i < nrow; i++) elems[i] = elems[i-1] + ncol;
        }
        // copy the data
        for (i = 0; i < nrow; i++) for (j = 0; j < ncol; j++) elems[i][j] = othermatrix[i][j];
    }
    return *this;
}

/* Manipulating the matrix */
template <class T>
void matrix<T>::resize(int newn, int newm)
{
	int i,nel;
	if (newn != nrow || newm != ncol) {
		if (elems != nullptr) {
			delete[] elems[0];
			delete[] elems;
		}
		nrow = newn;
		ncol = newm;
		elems = nrow>0 ? new T*[nrow] : nullptr;
		nel = ncol*nrow;
		if (elems) elems[0] = nel>0 ? new T[nel] : nullptr;
		for (i=1; i< nrow; i++) elems[i] = elems[i-1] + ncol;
	}
}

template <class T>
void matrix<T>::assign(int newn, int newm, const T& a)
{
	int i,j,nel;
	if (newn != nrow || newm != ncol) {
		if (elems != nullptr) {
			delete[] elems[0];
			delete[] elems;
		}
		nrow = newn;
		ncol = newm;
		elems = nrow>0 ? new T*[nrow] : nullptr;
		nel = ncol*nrow;
		if (elems) elems[0] = nel>0 ? new T[nel] : nullptr;
		for (i=1; i< nrow; i++) elems[i] = elems[i-1] + ncol;
	}
	for (i=0; i< nrow; i++) for (j=0; j<ncol; j++) elems[i][j] = a;
}

/* Destructor */
template <class T>
matrix<T>::~matrix()
{
    if (elems != nullptr)
    {
        delete[] (elems[0]);
        delete[] (elems);
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