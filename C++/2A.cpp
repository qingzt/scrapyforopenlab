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
        void rank();
        void select();
        void bubble();
        void insert();
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
        void rank();
        void select();
        void bubble();
        void insert();
        void input();
        void output();
};


void sort<int>::input()
{
    cin>>n;
    a=new int[n];
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

void sort<int>::rank()
{
    int r[n];
    for(int i=0;i<n;i++)
    {
        r[i]=0;
    }
    for(int i=1;i<n;i++)
    {
        for(int p=0;p<i;p++)
        {
            if(a[p]<=a[i])
                r[i]++;
            else
                r[p]++;
        }
    }
    int s[n];
    for(int i=0;i<n;i++)
    {
        s[r[i]]=a[i];
    }
    for(int i=0;i<n;i++)
    {
        a[i]=s[i];
    }
}

void sort<int>::select()
{
    bool sorted=false;
    for(int i=n;!sorted&&(i>1);i--)
    {
        int mindex=0;
        sorted=true;
        for(int p=0;p<i;p++)
        {
            if(a[mindex]<a[p])
            {
                mindex=p;
            }
            else
                sorted=false;
        }
        int temp=a[i-1];
        a[i-1]=a[mindex];
        a[mindex]=temp;
    }
}

void sort<int>::bubble()
{
    bool sorted=false;
    for(int i=n;i>1&&(!sorted);i--)
    {
        sorted=true;
        for(int p=0;p<i-1;p++)
        {
            if(a[p]>a[p+1])
            {
                int temp=a[p];
                a[p]=a[p+1];
                a[p+1]=temp;
                sorted=false;
            }
        }
    }
}

void sort<int>::insert()
{
    for(int i=1;i<n;i++)
    {
        for(int p=0;p<i;p++)
        {
            if(a[i]<a[p])
            {
                int temp=a[i];
                for(int q=i-1;q>=p;q--)
                {
                    a[q+1]=a[q];
                }
                a[p]=temp;
            }
        }
    }
}



int main()
{
    sort<int> a;
    a.input();
    a.select();
    a.output();
    return 0;
}