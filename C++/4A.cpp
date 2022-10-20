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
    int n,q;
    cin>>n;
    cin>>q;//输入操作数
    int out[q];//存储输出
    int p=0;
    int start;
    cin>>start;//使用第一个元素初始化链表
    chain a(start);
    for(int i=0;i<n-1;i++)
    {
        int temp;
        cin>>temp;
        a.insert(i+1,temp);
    }//形成链表
    for(int i=0;i<q;i++)
    {
        int op;
        cin>>op;//输入操作数
        if(op==1)
        {
            int index,theelement;
            cin>>index>>theelement;
            a.insert(index,theelement);
        } 
        if(op==2)
        {
            int theelement;
            cin>>theelement;
            int res;
            res=a.erase(theelement);
            if(res==-1)
            {
                out[p]=res;
                p++;
            }
        }
        if(op==3)
        {
            a.reseve();
        }
        if(op==4)
        {
            int theelement;
            cin>>theelement;
            out[p]=a.research(theelement);
            p++;
        }
        if(op==5)
        {
            out[p]=a.yihuo();
            p++;
        }
/*        miterator t(a.first());
        for(int k=0;k<a.size();k++) 
        {
           cout<<*t<<" ";
           t++;
        }
        cout<<endl;*/
        
    }
    for(int i=0;i<p;i++)
    {
        cout<<out[i]<<endl;
    }//输出结果
    return 0;
}