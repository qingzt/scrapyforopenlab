#include<iostream>
#include"arrayList.h"
using namespace std;
int main()
{
    arrayList<int> a(10);
    a.push_back(5);
    a.push_back(6);
    cout<<a;
    return 0;
}