#include<iostream>
using namespace std;

struct chainNode//节点类，为链表中的节点
{
    int element;
    chainNode *next;

    chainNode(){}
    chainNode(const int& element)//复制构造函数
    {
        this->element = element;
    }
    chainNode(const int& element, chainNode* next)
    {
        this->element = element;
        this->next = next;
    }
};

class miterator//迭代器
{  
    protected:
        chainNode *node;//迭代器的元素
    public:
        miterator(chainNode *thenode=NULL)//复制构造函数
        {
            node=thenode;
        }
        int& operator*() const//重载*
        {
            return node->element;
        }
        int* operator->() const//重载->
        {
            return &node->element;
        }
        miterator& operator++()//前++重载
        {
            node=node->next;
            return *this;
        }
        miterator operator++(int)//后++重载
        {
            miterator temp=*this;
            node=node->next;
            return temp;
        }
        bool operator!=(const miterator right) const//重载！=
        {
            return node!=right.node;
        }
        bool operator==(const miterator right) const//重载=
        {   
            return node== right.node;
        }
};

class chain//链表类
{
    private:
        chainNode *head;//头节点
        int ListSize;//链表长度
    public:
        chain()//默认的构造函数
        {
            head = NULL;
            ListSize =0;
        }
        chain(int element)//给定头节点的构造函数
        {
            head=new chainNode(element,NULL);
            ListSize =1;
        }
        ~chain()
        {
            while (head != NULL)
            {
                chainNode* nextNode = head->next;
                delete head;
                head = nextNode;
            }
        }
        int size() const//返回链表长度
        {
            return ListSize;
        }
        void insert(int index,int element)//再第index个元素之后插入
        {
            if (index == 0)//在头节点插入
                head = new chainNode(element, head);
            else//其他
            {
                chainNode *currnode=head;
                for(int i=0;i<index-1;i++)
                {
                    currnode=currnode->next;
                }
                currnode->next=new chainNode(element,currnode->next);
            }
            ListSize++;
        }
        int erase(int theelement)//删除
        {
            if(head->element==theelement)//要删除的元素为头节点
            {
                chainNode *dele=head;
                head=dele->next;
                delete dele;
            }
            else//要删除的元素为一般节点
            {
                chainNode *currnode=head;
                for(int i=0;i<ListSize-1;i++)
                {
                    if(currnode->next->element==theelement)
                    {
                        chainNode *dele=currnode->next;
                        currnode->next=dele->next;
                        delete dele;
                        ListSize--;
                        return 0;
                    }
                    currnode=currnode->next;
                }
            return -1;//未找到要删除的元素
            }
        }
        void reseve()//转置
        {
            chainNode *bef=NULL,*ptr=head,*aft=ptr->next;
            for (int i = 0;i<ListSize-1; i++)//遍历直至倒数第二个
            {
                ptr->next=bef;
                bef=ptr;
                ptr=aft;
                aft=ptr->next;
            }
            ptr->next=bef;//对最后一个进行操作
            head=ptr;
        }
        int research(int theelement)//查找
        {
            chainNode *currnode=head;
            for(int i=0;i<ListSize;i++)
            {
                if(currnode->element==theelement)
                {
                    return i;//找到返回索引
                }
                currnode=currnode->next;
            }
            return -1;
        }
        chainNode* first()
        {
            return head;//返回头节点，用于初始化迭代器
        }
        int yihuo()//求异或和
        {
            int result=0;
            miterator it(head);//定义迭代器
            for(int i=0;i<ListSize;i++)
            {
                int temp=*it;
                it++;
                result=result+(temp^i);
            }
            return result;
        }

};



int main()
{
    int n,m;
    cin>>n>>m;
    int a[n],b[m];//暂时存入输入的数字
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
    }
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
    }//将数字排序
    chain a1(a[0]);
    for(int i=0;i<n-1;i++)
    {
        a1.insert(i+1,a[i+1]);
    }//形成链表
    for(int i=0;i<m;i++)
    {
        cin>>b[i];
    }
    for(int i=1;i<m;i++)
    {
        for(int p=0;p<i;p++)
        {
            if(b[i]<b[p])
            {
                int temp=b[i];
                for(int q=i-1;q>=p;q--)
                {
                    b[q+1]=b[q];
                }
                b[p]=temp;
            }
        }
    }
    chain b1(b[0]);
    for(int i=0;i<m-1;i++)
    {
        b1.insert(i+1,b[i+1]);
    }//形成链表
    miterator at(a1.first());
    miterator bt(b1.first());//定义迭代器
    chain c;//链表c用于存储合并后的链表
    if(n==0&&m!=0)//当a的长度为0时
    {
        for(int i=0;i<m;i++)
        {
            c.insert(i,*bt);
            bt++;
        }//c即为b
    }
    if(m==0&&n!=0)//当b的长度为0时
    {
        for(int i=0;i<n;i++)
        {
            c.insert(i,*at);
            at++;
        }//c即为a
    }
    if(n!=0&&m!=0)//均不为0时
    {
        int ac=0,bc=0,sym=0,j=0;//ac表示已经并入c的a的个数，bc表示已经并入c的b的个数，sym表示a或b已经全部添加，j表示c中已并入的个数
        int sum=a1.size()+b1.size();//sum为c的长度
        while(j<sum)
        {
            int aa=*at,bb=*bt;//aa表示a当前的元素，bb表示b当前的元素
            if(aa<bb)
            {
                c.insert(j,*at);
                ac++;
                at++;
            }//将a的元素并入c
            if(bb<=aa)
            {
                c.insert(j,*bt);
                bc++;
                bt++;
            }//将b的元素并入c
            j++;//c中元素个数+1
            if(ac==a1.size())//检测a是否已经全部并入
            {
                sym=1;
                break;
            }
            if(bc==b1.size())//检测b是否已经全部并入
            {
                sym=2;
                break;
            }
        }
        if(sym==1)//a已经全部并入
        {
            while(j<sum)//将b剩余的插入
            {
                c.insert(j,*bt);
                bt++;
                j++;
            }
        }
        if(sym==2)//b已经全部并入
        {
            while(j<sum)//将a剩余的插入
            {
                c.insert(j,*at);
                at++;
                j++;
            }
        }
    }
    if(n!=0)
    {
        cout<<a1.yihuo()<<endl;
    }
    else
    {
        cout<<0<<endl;
    }
    if(m!=0)
    {
        cout<<b1.yihuo()<<endl;
    }
    else
    {
        cout<<0<<endl;
    }
    cout<<c.yihuo();//输出异或和
    return 0;
}