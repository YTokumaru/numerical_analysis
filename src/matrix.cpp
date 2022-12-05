#include "matrix.hpp"

/* Initializing the matrix */
template <class T>
matrix<T>::matrix(): _nrow(0), _ncol(0), _elems(nullptr) {}

template <class T>
matrix<T>::matrix(int n, int m): _nrow(n), _ncol(m), _elems(n>0? new T*[n]: nullptr)
{
    int i, nelm = n*m;
    if (_elems != nullptr) _elems[0] = nelm>0? new T[nelm] : nullptr;
    for (i = 1; i < n; i++) _elems[i] = _elems[i-1] + m;
}

template <class T>
matrix<T>::matrix(int n, int m, const T &a): _nrow(n), _ncol(m), _elems(n>0? new T*[n]: nullptr)
{
    int i, j, nelm = n*m;
    if (_elems != nullptr) _elems[0] = nelm>0? new T[nelm] : nullptr;
    for (i = 1; i < n; i++) _elems[i] = _elems[i-1] + m;

    for (i = 0; i < n; i++) for (j = 0; j < m; j++) _elems[i][j] = a;
}

template <class T>
matrix<T>::matrix(int n, int m, const T *a): _nrow(n), _ncol(m), _elems(n>0? new T*[n]: nullptr)
{
    int i, j, nelm = n*m;
    if (_elems != nullptr) _elems[0] = nelm>0? new T[nelm] : nullptr;
    for (i = 1; i < n; i++) _elems[i] = _elems[i-1] + m;

    // Make sure that the size of a is same or longer than the matrix
    for (int i = 0; i < n; i++) for (j = 0; j < m; j++) _elems[i][j] = *a++;
}

template <class T>
matrix<T>::matrix(const matrix<T> &othermatrix): _nrow(othermatrix._nrow), _ncol(othermatrix._ncol), _elems(_nrow>0? new T*[_nrow]: nullptr)
{
    int i, j, nelm = _nrow*_ncol;
    if (_elems != nullptr) _elems[0] = nelm>0? new T[nelm] : nullptr;
    for (i = 1; i < _nrow; i++) _elems[i] = _elems[i-1] + _ncol;

    for (i = 0; i < _nrow; i++) for (j = 0; j < _ncol; j++) _elems[i][j] = othermatrix[i][j];
}

template <class T>
matrix<T> & matrix<T>::operator=(const matrix<T> &othermatrix)
{
    if (this != &othermatrix)
    {
        int i, j, nelm;
        if (_nrow != othermatrix._nrow || _ncol != othermatrix._ncol)
        {
            // If the size is not the same, free all data and reallocate them
            if(_elems != nullptr)
            {
                delete[] (_elems[0]);
                delete[] (_elems);
            }
            _nrow = othermatrix._nrow;
            _ncol = othermatrix._ncol;
            _elems = _nrow>0? new T*[_nrow]: nullptr;
            nelm = _nrow*_ncol;

            if (_elems != nullptr) _elems[0] = nelm>0? new T[nelm] : nullptr;
            for (i = 1; i < _nrow; i++) _elems[i] = _elems[i-1] + _ncol;
        }
        // copy the data
        for (i = 0; i < _nrow; i++) for (j = 0; j < _ncol; j++) _elems[i][j] = othermatrix[i][j];
    }
    return *this;
}

/* Manipulating the matrix */
template <class T>
void matrix<T>::resize(int newn, int newm)
{
	int i,nel;
	if (newn != _nrow || newm != _ncol) {
		if (_elems != nullptr) {
			delete[] _elems[0];
			delete[] _elems;
		}
		_nrow = newn;
		_ncol = newm;
		_elems = _nrow>0 ? new T*[_nrow] : nullptr;
		nel = _ncol*_nrow;
		if (_elems) _elems[0] = nel>0 ? new T[nel] : nullptr;
		for (i=1; i< _nrow; i++) _elems[i] = _elems[i-1] + _ncol;
	}
}

template <class T>
void matrix<T>::assign(int newn, int newm, const T& a)
{
	int i,j,nel;
	if (newn != _nrow || newm != _ncol) {
		if (_elems != nullptr) {
			delete[] _elems[0];
			delete[] _elems;
		}
		_nrow = newn;
		_ncol = newm;
		_elems = _nrow>0 ? new T*[_nrow] : nullptr;
		nel = _ncol*_nrow;
		if (_elems) _elems[0] = nel>0 ? new T[nel] : nullptr;
		for (i=1; i< _nrow; i++) _elems[i] = _elems[i-1] + _ncol;
	}
	for (i=0; i< _nrow; i++) for (j=0; j<_ncol; j++) _elems[i][j] = a;
}

/* Destructor */
template <class T>
matrix<T>::~matrix()
{
    if (_elems != nullptr)
    {
        delete[] (_elems[0]);
        delete[] (_elems);
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