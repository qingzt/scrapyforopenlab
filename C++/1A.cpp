#include<iostream>
#include<math.h>
using namespace std;
int valuea[2000000];//全局变量，用于存放每个子集的价值
int p=0;//全局变量的下标
void getsubset(int a[],int yesno[],int current,int lenth)
{
    if(current==lenth)//递归出口
    {
        int n=0;
        int value=0;//初始化当前子集价值
        for(int i=0;i<lenth;i++)
        {
            if(yesno[i]==1)
            {
                n++;
            }
        }//此循环确定当前子集有多少元素
        int newa[n];//根据元素个数新建数组便于计算价值
        n=0;
        for(int i=0;i<lenth;i++)
        {
            if(yesno[i]==1)
            {
                newa[n]=a[i];//将选出的元素放入新的数组
                n++;
            }
        }
        for(int i=0;i<n;i++)
        {
            value=newa[i]*(i+1)+value;//计算价值
        }
        valuea[p]=value;//总价值放入数组
        p++;//下标加一
    }
    else
    {
        yesno[current]=1;//对于每个元素有两种选择，放入子集或者不放入
        getsubset(a,yesno,current+1,lenth);//current+1同理
        yesno[current]=0;
        getsubset(a,yesno,current+1,lenth);
    }
}


int main()
{
    int n;
    cin>>n;
    int a[n];
    int yesno[n];//用于标记全集中每个元素是否放入子集
    int result=0;
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
    }
    getsubset(a,yesno,0,n);
    for(int i=0;i<pow(2,n);i++)
    {
        result=result^valuea[i];//异或和计算
    }
    
    cout<<result;
    return 0;
}