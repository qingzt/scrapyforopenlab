#include<iostream>
using namespace std;
int GCD(int x,int y)
{
    if(y==0)
        return x;
    else
        return(GCD(y,x%y));
}
int main()
{
    cout<<GCD(20,30)<<endl;
    return 0;
}