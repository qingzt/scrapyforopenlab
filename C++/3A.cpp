#include<iostream>
#include<istream>
#include<string>
using namespace std;

st



struct student
{
    string name;
    string tele;
    int clas;
    int dorm;
};

void changelong(student *S,int oldl,int newl)
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
        student *S;
        int lenl;
        int size=0;
    public:
        arrayList()
        {
            S = new student[10];
            lenl = 10;
        }

        void insert(string nam,string tel,int cla,int dor)
        {
            size++;
            if(size>lenl)
            {
                changelong(S,lenl,2*lenl);
                lenl=2*lenl;
            }
            S[size-1].name=nam;
            S[size-1].tele=tel;
            S[size-1].clas=cla;
            S[size-1].dorm=dor;
        }

        void erase(string nam)
        {
            for(int i=0;i<size;i++)
            {
                if(S[i].name==nam)
                {
                    size--;
                    for(int p=i;i<size;p++)
                    {
                        S[p]=S[p+1];
                    }
                    break;
                }
            }
        }

        void edit(string nam,int t)
        {
            for(int i=0;i<size;i++)
            {
                if(S[i].name==nam)
                {
                    if(t==1)
                    {
                        string Tel;
                        cin >> Tel;
                        S[i].tele=Tel;
                    }
                    if(t==2)
                    {
                        int Clas;
                        cin >> Clas;
                        S[i].clas=Clas;
                    }
                    if(t==3)
                    {
                        int Dorm;
                        cin >> Dorm;
                        S[i].dorm=Dorm;
                    }
                    break;
                }
            }
        }

        void search(string nam)
        {
            int yes=0;
            for(int i=0;i<size;i++)
            {
                if(S[i].name==nam)
                {
                    yes=1;
                    break;
                }
            }
            cout<<yes<<endl;
        }

        void sum()
        {
            int result=0;
            for(int i=0;i<size;i++)
            {
                result=result^(S[i].dorm);
            }
        }
        
        void input()
        {
            int o;
            cin>>o;
            if(o==0)
            {
                string nam;
                string tel;
                int cla;
                int dor;
                cin >> nam;
                cin >> tel;
                cin>>cla;
                cin>>dor;
                cin.clear();
                insert(nam,tel,cla,dor);
            }
            if(o==1)
            {
                string nam;
                cin>>nam;
                erase(nam);
            }
            if(o==2)
            {
                string name;
                int n;
                cin >> name;
                cin >> n;
                edit(name,n);
            }
            if(o==3)
            {
                string name;
                search(name);
            }
            if(o==4)
            {
                sum();
            }
        }

        void output()
        {
            for(int i=0; i<size; i++)
            {
                cout<<S[i].name<<" "<<S[i].tele<<" "<<S[i].clas<<" "<<S[i].dorm<<endl;
            }
        }

};


int main()
{
    arrayList a;
    int n;
    cin >>n;
    for(int i=0; i<n; i++)
    {
        a.input();
    }
    return 0;
}