#include<iostream>
#include<string>
#include <iomanip>
using namespace std;


template<class T>
class Stack
{
    private:
        T terms[2000];//数组实现栈
        int lenth;//栈的长度
        int top;//栈顶位置
    public:
        Stack()//默认的构造函数
        {
            lenth=0;
            top=-1;
        }
        void push(T x)//将x压入栈
        {
            terms[top+1]=x;
            top++;
            lenth++;
        }
        T pop()//弹出栈顶元素
        {
            T temp=terms[top];
            terms[top]=0;
            top--;
            lenth--;
            return temp;
        }
        T peek()//查看栈顶元素
        {
            return terms[top];
        }
        int size()//返回栈的大小
        {
            return lenth;
        }
        bool isEmpty()//判断栈是否为空
        {
            return lenth==0;
        }
};

void calculate(int n)//计算n个
{
    Stack<double> num;//用于存放数字
    Stack<char> op;//用于存放操作
    char input;//当前应该存入栈的元素
    for(int i=0;i<n;i++)
    {
        string a;
        cin>>a;//输入表达式
        for(int i=0;i<a.size();i++)//对表达式每一位进行判断
        {
            input=a[i];//当前元素
            if(input=='+'||input=='-'||input=='*'||input=='/'||input=='('||input==')')//当前元素为操作
            {
                char oppeek=op.peek();//查看栈顶操作元素
                if((oppeek=='*'||oppeek=='/')&&input!='(')//当前元素不为'('，则之前的乘和除操作可以进行
                {
                    double a2=num.pop();
                    double a1=num.pop();
                    char ope=op.pop();
                    double result;
                    if(ope=='+')
                    {
                        result=a2+a1;
                    }
                    else if(ope=='-')
                    {
                        result=a1-a2;
                    }
                    else if(ope=='*')
                    {
                        result=a1*a2;
                    }
                    else if(ope=='/')
                    {
                        result=a1/a2;
                    }
                    num.push(result);//将结果压入数据栈
                    if((op.peek()=='+'||op.peek()=='-')&&input!='*'&&input!='/')//如果当前不是乘和除，则之前的加减操作也可以进行
                    {
                        double a2=num.pop();
                        double a1=num.pop();
                        char ope=op.pop();
                        double result;
                        if(ope=='+')
                        {
                            result=a2+a1;
                        }
                        else if(ope=='-')
                        {
                            result=a1-a2;
                        }
                        else if(ope=='*')
                        {
                            result=a1*a2;
                        }
                        else if(ope=='/')
                        {
                            result=a1/a2;
                        }
                        num.push(result);
                    }
                    op.push(input);
                }
                else if((oppeek=='+'||oppeek=='-')&&input!='*'&&input!='/'&&input!='(')//如果当前不是乘除或者'('，则之前的加减可以进行
                {
                    double a2=num.pop();
                    double a1=num.pop();
                    char ope=op.pop();
                    double result;
                    if(ope=='+')
                    {
                        result=a2+a1;
                    }
                    else if(ope=='-')
                    {
                        result=a1-a2;
                    }
                    else if(ope=='*')
                    {
                        result=a1*a2;
                    }
                    else if(ope=='/')
                    {
                        result=a1/a2;
                    }
                    num.push(result);
                    op.push(input);
                }
                else //其他情况压入栈
                {
                    op.push(input);
                }
                if(input==')')//压入栈的元素是')'
                {
                    if(op.peek()==')')//之前的操作中，右括号可能会被压入，将其弹出
                    {
                        op.pop();
                    }
                    if(op.peek()!='(')//如果前一个操作不是'('，执行括号中的运算，是为了防止3+(5/6)这种不用加括号的情况
                    {
                        double a2=num.pop();
                        double a1=num.pop();
                        char ope=op.pop();
                        double result;
                        if(ope=='+')
                        {
                            result=a2+a1;
                        }
                        else if(ope=='-')
                        {
                            result=a1-a2;
                        }
                        else if(ope=='*')
                        {
                            result=a1*a2;
                        }
                        else if(ope=='/')
                        {
                            result=a1/a2;
                        }
                        num.push(result);
                        if(op.peek()=='(')//将左括号弹出
                            op.pop();
                    }
                    else//前一个操作是'('，将左括号弹出
                    {
                        op.pop();
                    }
                }
            }
            else//当前元素是数字，直接压入栈
            {
                int curr=input-'0';
                num.push(curr);
            }
        }
        int numsize=num.size();
        for(int i=0;i<numsize-1;i++)//剩余的操作执行完
        {
            double a2=num.pop();
            double a1=num.pop();
            char ope=op.pop();
            double result;
            if(ope=='+')
            {
                result=a2+a1;
            }
            else if(ope=='-')
            {
                result=a1-a2;
            }
            else if(ope=='*')
            {
                result=a1*a2;
            }
            else if(ope=='/')
            {
                result=a1/a2;
            }
            num.push(result);
        }
        cout<<fixed<<setprecision(2)<<num.pop()<<endl;//输出结果
    }
    return;
}




int main()
{
    int n;
    cin>>n;
    calculate(n);
    return 0;
}