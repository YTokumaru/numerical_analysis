#include "vector.hpp"

/* Creating vector */
template <class T>
vector<T>::vector(): nrow(0), elems(nullptr) {}

template <class T>
vector<T>::vector(int n): nrow(n), elems(n>0? new T[n]: nullptr) {}

template <class T>
vector<T>::vector(int n, const T &a): nrow(n), elems(n>0? new T[n]: nullptr)
{
    for (int i = 0; i < nrow; i++)
    {
        elems[i] = a;
    }
}

template <class T>
vector<T>::vector(int n, const T *a): nrow(n), elems(n>0? new T[n]: nullptr)
{
    for (int i = 0; i < nrow; i++)
    {
        elems[i] = *a++;
    }
}

template <class T>
vector<T>::vector(const vector<T> &othervector): nrow(othervector.nrow), elems(nrow>0? new T[nrow]: nullptr)
{
    for (int i = 0; i < nrow; i++)
    {
        elems[i] = othervector[i];
    }
}

template <class T>
vector<T> & vector<T>::operator=(const vector<T> &othervector)
{
    if (this != &othervector)
    {
        if (nrow != othervector.nrow)
        {
            if (nrow != othervector.nrow)
            {
                if(elems != nullptr) delete[] (elems);
                nrow = othervector.nrow;
                elems = nrow>0? new T[nrow] : nullptr;
            }
            for (int i = 0; i < nrow; i++)
            {
                elems[i] = othervector[i];
            }
        }
    }
    return *this;
}

/* Manipulating the vector */
template <class T>
void vector<T>::resize(int newn)
{
	if (newn != nrow) {
		if (elems != nullptr) delete[] (elems);
		nrow = newn;
		elems = nrow > 0 ? new T[nrow] : NULL;
	}
}

template <class T>
void vector<T>::assign(int newn, const T& a)
{
	if (newn != nrow) {
		if (elems != nullptr) delete[] (elems);
		nrow = newn;
		elems = nrow > 0 ? new T[nrow] : nullptr;
	}
	for (int i = 0; i < nrow; i++) elems[i] = a;
}

/* Information about the vector */
template <class T>
int vector<T>::find(const T &a) const
{
    /* Finds the first occurence of 'a' in the vector and return its index 
     * When no occurence is found, it will return -1*/
    for (int i = 0; i < nrow; i++)
    {
        if (elems[i] == a)
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
	if (elems != nullptr) delete[] (elems);
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