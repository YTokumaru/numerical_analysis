#include "vector.hpp"

/* Creating vector */
template <class T>
vector<T>::vector(): _nrow(0), _elems(nullptr) {}

template <class T>
vector<T>::vector(int n): _nrow(n), _elems(n>0? new T[n]: nullptr) {}

template <class T>
vector<T>::vector(int n, const T &a): _nrow(n), _elems(n>0? new T[n]: nullptr)
{
    for (int i = 0; i < _nrow; i++)
    {
        _elems[i] = a;
    }
}

template <class T>
vector<T>::vector(int n, const T *a): _nrow(n), _elems(n>0? new T[n]: nullptr)
{
    for (int i = 0; i < _nrow; i++)
    {
        _elems[i] = *a++;
    }
}

template <class T>
vector<T>::vector(const vector<T> &othervector): _nrow(othervector._nrow), _elems(_nrow>0? new T[_nrow]: nullptr)
{
    for (int i = 0; i < _nrow; i++)
    {
        _elems[i] = othervector[i];
    }
}

template <class T>
vector<T> & vector<T>::operator=(const vector<T> &othervector)
{
    if (this != &othervector)
    {
        if (_nrow != othervector._nrow)
        {
            if (_nrow != othervector._nrow)
            {
                if(_elems != nullptr) delete[] (_elems);
                _nrow = othervector._nrow;
                _elems = _nrow>0? new T[_nrow] : nullptr;
            }
            for (int i = 0; i < _nrow; i++)
            {
                _elems[i] = othervector[i];
            }
        }
    }
    return *this;
}

/* Manipulating the vector */
template <class T>
void vector<T>::resize(int newn)
{
	if (newn != _nrow) {
		if (_elems != nullptr) delete[] (_elems);
		_nrow = newn;
		_elems = _nrow > 0 ? new T[_nrow] : NULL;
	}
}

template <class T>
void vector<T>::assign(int newn, const T& a)
{
	if (newn != _nrow) {
		if (_elems != nullptr) delete[] (_elems);
		_nrow = newn;
		_elems = _nrow > 0 ? new T[_nrow] : nullptr;
	}
	for (int i = 0; i < _nrow; i++) _elems[i] = a;
}

/* Information about the vector */
template <class T>
int vector<T>::find(const T &a) const
{
    /* Finds the first occurence of 'a' in the vector and return its index 
     * When no occurence is found, it will return -1*/
    for (int i = 0; i < _nrow; i++)
    {
        if (_elems[i] == a)
        {
            return i;
        }
    }
    return -1;
}

/* Destructor */
template <class T>
vector<T>::~vector()
{
	if (_elems != nullptr) delete[] (_elems);
}


// Explicit template instantiation; add as needed
template class vector<char>;
template class vector<unsigned char>;
template class vector<int>;
template class vector<unsigned int>;
template class vector<long int>;
template class vector<long long int>;
template class vector<unsigned long long int>;
template class vector<double>;
template class vector<long double>;
template class vector<std::complex<double>>;