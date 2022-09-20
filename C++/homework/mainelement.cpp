#include<iostream>
using namespace std;
int main()
{
    int n;
    cin>>n;
    int A[n];
    int b[n];//下标表示每一个元素的值，b[n]表示当前值出现的次数
    int flag=1;
    for(int i=0;i<n;i++)
    {
        cin>>A[i];
        b[i]=0;
    }//输入和初始化
    for(int i=0;i<n;i++)
    {
        b[A[i]]++;//当前元素值对应的出现次数增加
        if(b[A[i]]>n/2)//超过一半直接结束循环
        {
            cout<<A[i];//输出当前元素
            flag=0;//表示已经找到
            break;
        }
    }
    if(flag)
    {
        cout<<-1;//未找到输出-1
    }
    return 0;
}