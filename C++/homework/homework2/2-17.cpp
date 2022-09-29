#include<iostream>
#include "extendedChain.h"
using namespace std;

int main()
{
    extendedChain<int> a;
    extendedChain<int> b;
    a.push_back(1);
    a.push_back(2);
    b.push_back(5);
    b.push_back(6);
    b.push_back(7);
    b.push_back(8);
    cout<<a<<endl;
    cout<<b<<endl;
    cout<<meld(a,b);
    return 0;
}