#include<iostream>
#include"lowerTriangularMatrix.h"
#include"higherTriangularMatrix.h"
#include"matrix.h"


using namespace std;
template<class T>
matrix<T> multiply(const higherTriangularMatrix<T> a,const lowerTriangularMatrix<T> b,int n)
{
    matrix<T> c(n,n);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            int sum=0;
            for(int k=1;k<=n;k++)
            {
                T a1=a.get(i,k);
                T b1=b.get(k,j);
                sum=sum+a1*b1;
            }
            c.element[(i - 1) * n + j - 1]=sum;
        }

    }
    return c;

}

int main()
{
    higherTriangularMatrix<int> a(3);
    lowerTriangularMatrix<int> b(3);
    a.set(1,1,1);
    a.set(1,2,2);
    a.set(1,3,3);
    a.set(2,2,4);
    a.set(2,3,5);
    a.set(3,3,6);
    b.set(1,1,1);
    b.set(2,1,2);
    b.set(2,2,3);
    b.set(3,1,4);
    b.set(3,2,5);
    b.set(3,3,6);
    cout<<multiply(a,b,3);
    return 0;
}