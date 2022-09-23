#include<iostream>
#include"chain.h"
using namespace std;
int main()
{
    chain<int> a(10);
    a.insert(0,1);
    a.insert(0,2);
    a.insert(1,3);
    a.set(1,5);
    a.reverse();
    cout<<a;
    return 0;
}