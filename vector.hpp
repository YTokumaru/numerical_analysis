#ifndef VECTOR
#define VECTOR

#include "numerical_analysis.hpp"

template<class T>
class vector
{
private:
    int nrow;
    T *elems;
public:
    /* Creating vector */
    vector();                                           // Default constructor
    explicit vector(int n);                             // Construct vector with size n
    vector(int n, const T &a);                          // Initialize the vector to a constant 'a'
    vector(int n, const T *a);                          // Initialize the vector to a C-style array
    vector(const vector &othervector);                  // Copy constructor
    vector & operator=(const vector &othervector);      // Assignment operator

    /* Adressing elements */
    inline T & operator[](const int i);                 // Return element number i
    inline const T & operator[](const int i) const;         // const version. Called when vector is declared const

    /* Information about the vector */
    typedef T value_type;                               // Make T available
    inline int size(void) const;                        // The size of vector
    int find(const T &a) const;                       // Find the first occurence of 'a' in the vector and return its index

    /* Manipulating the vector */
    void resize(int newn);                              // resize to size n
    void assign(int newn, const T &a);                  // resize and assign constant 'a'

    ~vector();                                          // Destructor
};


/* Adressing elements */
template <class T>
inline T & vector<T>::operator[](const int i)
{
#ifdef CHECKBOUNDS
    if (i < 0 || i >= nrow)
    {
        throw("Index out of bounds!");
    }
#endif // CHECKBOUNDS
    return elems[i];
}

template <class T>
inline const T & vector<T>::operator[](const int i) const
{
#ifdef CHECKBOUNDS
    if (i < 0 || i >= nrow)
    {
        throw("Index out of bounds!");
    }
#endif // CHECKBOUNDS
    return elems[i];
}


/* Information about the vector */
template <class T>
inline int vector<T>::size(void) const
{
    return nrow;
}


// Typedefs to make the code simpler:
typedef vector<char>                    VecChar;
typedef vector<unsigned char>           VecUchar;
typedef vector<int>                     VecInt;
typedef vector<unsigned int>            VecUInt;
typedef vector<long int>                VecLInt;
typedef vector<long long int>           VecLLInt;
typedef vector<unsigned long long int>  VecULLInt;
typedef vector<double>                  VecDouble;
typedef vector<long double>             VecLDouble;
typedef vector<std::complex<double>>    VecCompex;

#endif // VECTOR