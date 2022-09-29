#include<iostream>
using namespace std;

template<class T>
class sort//模板类
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
class sort<int>//特化
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


void sort<int>::input()//输入
{
    cin>>n;
    a=new int[n];
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
    }
}

void sort<int>::output()//输出
{
    for(int i=0;i<n;i++)
    {
        cout<<a[i]<<" ";
    }
}

void sort<int>::rank()//名次排序
{
    int r[n];
    for(int i=0;i<n;i++)
    {
        r[i]=0;
    }//初始化
    for(int i=1;i<n;i++)
    {
        for(int p=0;p<i;p++)
        {
            if(a[p]<=a[i])
                r[i]++;
            else
                r[p]++;
        }
    }//取得名次
    int s[n];
    for(int i=0;i<n;i++)
    {
        s[r[i]]=a[i];
    }//附加数组排序
    for(int i=0;i<n;i++)
    {
        a[i]=s[i];
    }//回到原数组
}

void sort<int>::select()//选择排序
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
        }//找到最大的索引
        int temp=a[i-1];
        a[i-1]=a[mindex];
        a[mindex]=temp;//与当前交换
    }
}

void sort<int>::bubble()//冒泡排序
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

void sort<int>::insert()//插入排序
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
            }//选择位置插入
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