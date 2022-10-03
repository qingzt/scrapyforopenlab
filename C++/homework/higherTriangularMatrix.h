// lower triangle matrix
#ifndef higherTriangularMatrix_
#define higherTriangularMatrix_


#include "myExceptions.h"

using namespace std;

template<class T>
class higherTriangularMatrix 
{
   public:
      higherTriangularMatrix(int theN = 10);
      ~higherTriangularMatrix() {delete [] element;}
      T get(int, int) const;
      void set(int, int, const T&);
   private:
      int n;       // matrix dimension
      T *element;  // 1D array for higher triangle
};


template<class T>
higherTriangularMatrix<T>::higherTriangularMatrix(int theN)
{// Constructor.
   // validate theN
   if (theN < 1)
       throw illegalParameterValue("Matrix size must be > 0");

   n = theN;
   element = new T [n * (n + 1) / 2];
}
   
template <class T>
T higherTriangularMatrix<T>::get(int i, int j) const
{// Return (i,j)th element of matrix.
   // validate i and j
   if ( i < 1 || j < 1 || i > n || j > n)
       throw matrixIndexOutOfBounds();

   // (i,j) in higher triangle iff i >= j
   if (i <= j)
      return element[n*(i-1)-(i-2)*(i-1)/2+j-i];
   else
      return 0;
}

template<class T>
void higherTriangularMatrix<T>::set(int i, int j, const T& newValue)
{// Store newValue as (i,j)th element.
   // validate i and j
   if ( i < 1 || j < 1 || i > n || j > n)
       throw matrixIndexOutOfBounds();


   // (i,j) in higher triangle iff i >= j
   if (i <= j)
      element[n*(i-1)-(i-2)*(i-1)/2+j-i] = newValue;
   else
      if (newValue != 0)
         throw illegalParameterValue
               ("elements not in higher triangle must be zero");
}

#endif