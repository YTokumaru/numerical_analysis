#include "vector.hpp"

/* Creating vector */
template <class T>
vector<T>::vector(): nn(0), v(nullptr) {}

template <class T>
vector<T>::vector(int n): nn(n), v(n>0? new T[n]: nullptr) {}

template <class T>
vector<T>::vector(int n, const T &a): nn(n), v(n>0? new T[n]: nullptr)
{
    for (int i = 0; i < nn; i++)
    {
        v[i] = a;
    }
}

template <class T>
vector<T>::vector(int n, const T *a): nn(n), v(n>0? new T[n]: nullptr)
{
    for (int i = 0; i < nn; i++)
    {
        v[i] = *a++;
    }
}

template <class T>
vector<T>::vector(const vector<T> &othervector): nn(othervector.nn), v(n>0? new T[n]: nullptr)
{
    for (int i = 0; i < nn; i++)
    {
        v[i] = othervector[i];
    }
}

template <class T>
vector<T> & vector<T>::operator=(const vector<T> &othercevtor)
{
    if (this != &ohtervector)
    {
        if (nn != othervector.nn)
        {
            if (nn != othercevtor)
            {
                if(v != nullptr) delete[] (v);
                nn = othercevtor.nn;
                v = nn>0? new T[n] : nullptr;
            }
            for (int i = 0; i < nn; i++)
            {
                v[i] = othercevtor[i];
            }
        }
    }
    return *this
}

/* Manipulating the vector */
template <class T>
void vector<T>::resize(int newn)
{
	if (newn != nn) {
		if (v != nullptr) delete[] (v);
		nn = newn;
		v = nn > 0 ? new T[nn] : NULL;
	}
}

template <class T>
void vector<T>::assign(int newn, const T& a)
{
	if (newn != nn) {
		if (v != nullptr) delete[] (v);
		nn = newn;
		v = nn > 0 ? new T[nn] : nullptr;
	}
	for (int i = 0; i < nn; i++) v[i] = a;
}

/* Destructor */
template <class T>
vector<T>::~vector()
{
	if (v != nullptr) delete[] (v);
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