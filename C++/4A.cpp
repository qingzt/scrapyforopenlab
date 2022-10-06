#include<iostream>
using namespace std;

struct chainNode
{
    int element;
    chainNode *next;

    chainNode(){}
    chainNode(const int& element)
    {
        this->element = element;
    }
    chainNode(const int& element, chainNode* next)
    {
        this->element = element;
        this->next = next;
    }
};

class miterator
{  
    protected:
        chainNode *node;
    public:
        miterator(chainNode *thenode=NULL)
        {
            node=thenode;
        }
        int& operator*() const
        {
            return node->element;
        }
        int* operator->() const
        {
            return &node->element;
        }
        miterator& operator++()
        {
            node=node->next;
            return *this;
        }
        miterator operator++(int)
        {
            miterator temp=*this;
            node=node->next;
            return temp;
        }
        bool operator!=(const miterator right) const
        {
            return node!=right.node;
        }
        bool operator==(const miterator right) const
        {   
            return node== right.node;
        }
};

class chain
{
    private:
        chainNode *head;
        int ListSize;
    public:
        chain()
        {
            head = NULL;
            ListSize =0;
        }
        chain(int element)
        {
            head=new chainNode(element,NULL);
            ListSize =1;
        }
        int size() const
        {
            return ListSize;
        }
        void insert(int index,int element)
        {
            if (index == 0)
                head = new chainNode(element, head);
            else
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
        int erase(int theelement)
        {
            if(head->element==theelement)
            {
                chainNode *dele=head;
                head=dele->next;
                delete dele;
            }
            else
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
            return -1;
            }
        }
        void reseve()
        {
            chainNode *bef=NULL,*ptr=head,*aft=ptr->next;
            for (int i = 0;i<ListSize-1; i++)
            {
                ptr->next=bef;
                bef=ptr;
                ptr=aft;
                aft=ptr->next;
            }
            ptr->next=bef;
            bef=ptr;
            ptr=aft;
            head=bef;
        }
        int research(int theelement)
        {
            chainNode *currnode=head;
            for(int i=0;i<ListSize;i++)
            {
                if(currnode->element==theelement)
                {
                    return i;
                }
                currnode=currnode->next;
            }
            return -1;
        }
        chainNode* first()
        {
            return head;
        }
        int yihuo()
        {
            int result=0;
            miterator it(head);
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
    cin>>q;
    int out[q];
    int p=0;
    int start;
    cin>>start;
    chain a(start);
    for(int i=0;i<n-1;i++)
    {
        int temp;
        cin>>temp;
        a.insert(i+1,temp);
    }
    for(int i=0;i<q;i++)
    {
        int op;
        cin>>op;
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
    }
    return 0;
}