#include<iostream>
using namespace std;

int valuea[5000000];//全局变量用于存放价值
int p=0;//全局变量的下标

void fullarrange(int a[],int current,int lenth)
{
    if(current==lenth)//递归出口
    {
        int value=0;
        for(int i=0;i<lenth;i++)
        {
            int v=a[i]^(i+1);
            value=value+v;
        }//计算价值
        valuea[p]=value;//价值存入
        p++;
    }
    else//通过两个元素不断改变位置实现全排列
    {
        for(int i=current;i<lenth;i++)//current用来标记经过交换的元素，从左向右交换依次进行
        {
            int temp=a[i];
            a[i]=a[current];
            a[current]=temp;//进行交换
            fullarrange(a,current+1,lenth);//进入递归
            //temp=a[i];
            //a[i]=a[current];
            //a[current]=temp;//交换回来
        }
    }
}


int main()
{
    int n;
    int sum=1;
    int result=0;
    cin>>n;
    int a[n];
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
        sum=sum*(i+1);//计算价值的个数
    }
    fullarrange(a,0,n);
    for(int i=0;i<sum;i++)
    {
        result=result|valuea[i];//按位与
    }
    cout<<result;
    return 0;
}