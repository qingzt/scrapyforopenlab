#include<iostream>
using namespace std;

template<class T>
bool judge(T a[],int n,T number)
{
    if(n>=0)
    {
        if(a[n]==number)
            return true;
        else
            return judge(a,n-1,number);
    }
    return false;
}


int main()
{
    int a[5]={1,2,3,4,5};
    cout<<judge(a,5,6);
    return 0;
}