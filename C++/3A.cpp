#include<iostream>
#include<istream>
#include<string>
using namespace std;

struct instruct//用来存放指令
{
    int no=-1;//指令的编号
    int type=-1;//修改指令的操作对象
    string name="";//初始化
    string tele="";
    int clas=-1;
    int dorm=-1;
};

struct student
{
    string name="";//初始化
    string tele="";
    int clas=-1;
    int dorm=-1;
};

void changelong(student *&S,int oldl,int newl)//改变线性表长度
{
    student* temp= new student[newl];
    for(int i=0;i<oldl;i++)
    {
        temp[i]=S[i];
    }
    delete [] S;
    S = temp;
}


class arrayList
{   
    private:
        student *S;//数据成员
        int lenl;//线性表长度
        int size=0;//学生个数
        instruct *ins;//存放指令的数组
    public:
        arrayList(int n)
        {
            S = new student[n];
            lenl = n;
        }//给定大小的构造函数
        arrayList()
        {
            S = new student[10];
            lenl = 10;
        }//默认的构造函数
        
        void insert(string nam,string tel,int cla,int dor)
        {
            size++;//大小加一
            if(size>lenl)
            {
                changelong(S,lenl,2*lenl);
                lenl=2*lenl;
            }//长度不够变为2倍
            S[size-1].name=nam;
            S[size-1].tele=tel;
            S[size-1].clas=cla;
            S[size-1].dorm=dor;//添加新值
        }

        void erase(string nam)
        {
            for(int i=0;i<size;i++)
            {
                if(S[i].name==nam)//找到名字相同
                {
                    size--;//大小减一
                    for(int j=i;j<size;j++)
                    {
                        S[j].name=S[j+1].name;
                        S[j].clas=S[j+1].clas;
                        S[j].dorm=S[j+1].dorm;
                        S[j].tele=S[j+1].tele;
                    }//后面的向前移动
                    S[size].name="";
                    S[size].clas=-1;
                    S[size].dorm=-1;
                    S[size].tele="";//最后一个初始化
                    break;
                }
            }
        }

        void edit(string nam,int t,instruct ins)
        {
            for(int i=0;i<size;i++)
            {
                if(S[i].name==nam)
                {
                    if(t==1)//指令判断
                    {
                        S[i].tele=ins.tele;
                    }
                    if(t==2)
                    {
                        S[i].clas=ins.clas;
                    }
                    if(t==3)
                    {
                        S[i].dorm=ins.dorm;
                    }
                    break;
                }
            }
        }

        void search(string nam)
        {
            int yes=0;
            for(int i=0;i<size;i++)//搜索
            {
                if(S[i].name==nam)
                {
                    yes=1;
                    break;
                }
            }
            cout<<yes<<endl;
        }

        void sum(instruct ins)
        {
            int result=0;//异或和值初始化
            for(int i=0;i<size;i++)
            {
                if(S[i].clas==ins.clas)//判断班级相同
                {
                    result=result^(S[i].dorm);
                }
            }
            cout<<result<<endl;
        }
        
        void act(int n)//指令接受完毕开始执行
        {
            for(int i=0;i<n;i++)
            {
                if(ins[i].no==0)
                {
                    insert(ins[i].name,ins[i].tele,ins[i].clas,ins[i].dorm);
                }
                if(ins[i].no==1)
                {
                    erase(ins[i].name);
                }
                if(ins[i].no==2)
                {
                    edit(ins[i].name,ins[i].type,ins[i]);
                }
                if(ins[i].no==3)
                {
                    search(ins[i].name);
                }
                if(ins[i].no==4)
                {
                    sum(ins[i]);
                }
            }           
        }

        void input(int n)//接收指令
        {
            ins=new instruct[n];//创建数量的指令结构体
            for(int i=0;i<n;i++)
            {
                cin>>ins[i].no;//根据不同指令选择不同的存放方式
                if(ins[i].no==0)
                {
                    cin>>ins[i].name;
                    cin>>ins[i].tele;
                    cin>>ins[i].clas;
                    cin>>ins[i].dorm;
                }
                if(ins[i].no==1)
                {
                    cin>>ins[i].name;
                }
                if(ins[i].no==2)
                {
                    cin>>ins[i].name;
                    cin>>ins[i].type;
                    if(ins[i].type==1)
                    {
                        cin>>ins[i].tele;
                    }
                    if(ins[i].type==2)
                    {
                        cin>>ins[i].clas;
                    }
                    if(ins[i].type==3)
                    {
                        cin>>ins[i].dorm;
                    }
                }
                if(ins[i].no==3)
                {
                    cin>>ins[i].name;
                }
                if(ins[i].no==4)
                {
                    cin>>ins[i].clas;
                }
            }
        }

        void output()//测试使用
        {
            for(int i=0; i<size; i++)
            {
                cout<<S[i].name<<" "<<S[i].tele<<" "<<S[i].clas<<" "<<S[i].dorm<<endl;
            }
        }

};


int main()
{
    int n;
    cin >>n;
    arrayList a;
    a.input(n);
    a.act(n);
    return 0;
}