#include<iostream>
#include"arrayList.h"
using namespace std;
int main()
{
    arrayList<int> a(10);
    a.push_back(5);
    a.push_back(6);
    a.pop_back();
    cout<<a<<endl;
    cout<<a.capacity()<<endl;
    a.reserve(9);
    cout<<a.capacity()<<endl;
    a.reserve(11);
    cout<<a.capacity()<<endl;
    a.clear();
    cout<<a<<endl;
    return 0;
}