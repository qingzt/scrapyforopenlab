#include<iostream>
using namespace std;

template<class T>
class sort
{
    private:
        T *a=NULL;
        int n=0;
    public:
        ~sort(){delete a;};
        void ranking();
//        void select();
//        void bubble();
//        void insert();
        void input();
        void output();
};

template<>
class sort<int>
{
    private:
        int *a=NULL;
        int n=0;
    public:
        ~sort(){delete a;}
        void ranking();
//        void select();
//        void bubble();
//        void insert();
        void input();
        void output();
};


void sort<int>::input()
{
    cin>>n;
    a=new int(n);
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
    }
}

void sort<int>::output()
{
    for(int i=0;i<n;i++)
    {
        cout<<a[i]<<" ";
    }
}





int main()
{
    sort<int> a;
    a.input();
    a.output();
    return 0;
}