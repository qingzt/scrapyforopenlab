#include<iostream>
#include <vector>
using namespace std;

struct elem
{
    int row;
    int col;
    int value;
};



class sparseMatrix
{
    private:
        int rows;
        int cols;
        vector<elem> terms;//非0元素在terms数组中
    public:
        sparseMatrix()//默认的构造函数
        {
            rows=0;
            cols=0;
        }
        sparseMatrix(int rows,int cols):rows(rows),cols(cols){}//构造函数
        void set(int row, int col);//重置矩阵
        void output();//输出
        int add();//加法
        void push(elem temp){terms.push_back(temp);}//将temp加入到矩阵中
        int getrows(){return rows;}//返回当前矩阵的行数
        int getcols(){return cols;}//返回当前矩阵的列数
        vector<elem> getterms(){return terms;}//返回储存非0元素的数组
        elem gettheterm(int q){return terms[q];}//返回第q个非0元素
        void reserve();//矩阵转置
        int multiply();//矩阵乘法
        int multplus();//修改版矩阵乘法
};

void sparseMatrix::set(int row, int col)
{
    rows = row;//设置行数
    cols = col;//设置列数
    terms.clear();//清空元素
    int in;//输入
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cin>>in;
            if(in!=0)//输入元素不为0
            {
                elem temp;//储存当前元素信息
                temp.row=i+1;
                temp.col=j+1;
                temp.value=in;
                terms.push_back(temp);//将当前元素加入矩阵
            }
        }
    }
}


void sparseMatrix::output()
{
    cout<<rows<<" "<<cols<<endl;
    int p=0;//确定当前应该输出的非0元素的序号
    if(terms.size()==0)//若为全0矩阵，直接全部输出0
    {
        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < cols; j++)
            {
                cout<<0<<" ";
            }
            cout<<endl;
        }
    }
    else
    {
        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < cols; j++)
            {
                if(p<terms.size()&&terms[p].row==i+1&&terms[p].col==j+1)//当前行或者列在数组中存有元素
                {
                    cout<<terms[p].value<<" ";//输出
                    p++;//数组移至下一个
                }
                else
                {
                    cout<<0<<" ";//否则输出0
                }
            }
            cout<<endl;
        }
    }
}

int sparseMatrix::add()//矩阵加法
{
    int newrows,newcols,t;
    cin>>newrows>>newcols;//输入新矩阵的行和列
    sparseMatrix Q(newrows,newcols);
    cin>>t;//t个非0元素
    for(int i=0;i<t;i++)
    {
        elem temp;
        cin>>temp.row>>temp.col>>temp.value;
        Q.push(temp);//将当前元素加入新矩阵
    }//输入另一个矩阵
    if(newrows!=rows||newcols!=cols)//矩阵不相容
    {
        this->terms=Q.getterms();
        this->cols=Q.getcols();
        this->rows=Q.getrows();
        return -1;//Q赋给当前矩阵，输出-1
    }
    else//矩阵相容
    {
        sparseMatrix R(rows, cols);//创建结果矩阵，行和列和当前矩阵相同
        int p = 0, q = 0;//用于遍历当前矩阵P和新的矩阵Q
        int psize = terms.size(), qsize = Q.getterms().size();//确定P和Q的大小
        while (p < psize && q < qsize)//遍历完P或者是Q
        {
            int pindex = (terms[p].row - 1) * cols + terms[p].col;
            int qindex = (Q.gettheterm(q).row - 1) * Q.getcols() + Q.gettheterm(q).col;//映射到一维
            if (pindex == qindex)//P的当前元素和Q的当前元素相同
            {
                elem temp;
                temp.row = terms[p].row;
                temp.col = terms[p].col;
                temp.value = terms[p].value + Q.gettheterm(q).value;//储存和的信息
                if (temp.value != 0)//和不为0时加入R
                    R.push(temp);
                p++;//P移至下一个
                q++;//Q移至下一个
            }
            else if (pindex < qindex)//P的位置靠前
            {
                R.push(terms[p]);//将P加入R
                p++;//P移至下一个
            }
            else if (qindex < pindex)//Q的位置靠前
            {
                R.push(Q.gettheterm(q));//将Q加入R
                q++;//Q移至下一个
            }
        }
        while (q < qsize)//将Q剩余的加入
        {
            R.push(Q.gettheterm(q));
            q++;
        }
        while (p < psize)//将P剩余的加入
        {
            R.push(terms[p]);
            p++;
        }
        terms = R.getterms();//R的非0元素赋给Q
        return 0;
    }
}

void sparseMatrix::reserve()
{
    sparseMatrix R(cols,rows);//创建转置后的矩阵
    int size=terms.size();
    int co = cols;
    int *colsize=new int[co+1];//每一列的元素个数
    int *rownext=new int[co + 1];//第i列的元素应在的位置
    for (int i = 0; i < cols; i++)
    {
        colsize[i] = 0;
        rownext[i] = 0;
    }//初始化
    for(int i=0;i<size;i++)
    {
        colsize[terms[i].col]++;//确定每一列的元素个数
    }
    for(int i=2;i<=cols;i++)
    {
        rownext[i]=rownext[i-1]+colsize[i-1];//求出当前元素应在转置后矩阵中的位置
    }
    elem *temp=new elem[size];
    for(int i=0;i<size;i++)
    {
        temp[rownext[terms[i].col]]=terms[i];
        rownext[terms[i].col]++;
    }//将当前元素放在转置后的位置上
    for(int i=0;i<size;i++)
    {
        int tempa=temp[i].col;
        temp[i].col=temp[i].row;
        temp[i].row=tempa;
        R.push(temp[i]);
    }//交换每一个元素的行和列
    this->rows=R.getrows();
    this->cols=R.getcols();
    this->terms=R.getterms();
    delete []colsize;
    delete []rownext;
    delete []temp;
}

int sparseMatrix::multiply()
{
    int newrows,newcols,t;
    cin>>newrows>>newcols;
    sparseMatrix Q(newrows,newcols);
    cin>>t;
    for(int i=0;i<t;i++)
    {
        elem temp;
        cin>>temp.row>>temp.col>>temp.value;
        Q.push(temp);
    }//输入另一个矩阵
    if(cols!=newrows)//矩阵不相容
    {
        this->terms=Q.getterms();
        this->cols=Q.getcols();
        this->rows=Q.getrows();
        return -1;
    }
    else if(terms.size()!=0)//矩阵相容，并且当前矩阵非全0
    {
        sparseMatrix R(rows,newcols);
        Q.reserve();//Q矩阵转置，由行主映射转为列主映射
        int psize = terms.size();//确定P的大小
        int qsize = Q.getterms().size();//确定Q的大小
        int pc=0;//用于记录p中非0元素在每次循环中的位置
        for(int p=1;p<=rows;p++)
        {
            int p1=0;//P中非0元素从第一个开始
            int qc=0;//用于记录q中非0元素在每次循环中的位置
            for(int q=1;q<=newcols;q++)//新矩阵的第q列
            {
                p1=pc;//P中非0元素回到开始位置
                int q1=qc;//Q中非0元素回到开始位置
                int result=0;//计算第p行第q列的元素的值
                for(int i=1;i<=cols; i++)//循环求乘积和
                {
                    int p1row=0, p1col=0, q1row=0, q1col=0;
                    if (p1 != psize)//保证不越界
                    {
                        p1row = terms[p1].row;
                        p1col = terms[p1].col;//P中当前元素的行列信息
                    }
                    if (q1 != qsize)//保证不越界
                    {
                        q1row = Q.gettheterm(q1).row;
                        q1col = Q.gettheterm(q1).col;//Q中当前元素的行列信息
                    }
                    if(p1row==p&&p1col==i&&q1row==q&&q1col==i)//行列都符合
                    {
                        result=result+terms[p1].value*Q.gettheterm(q1).value;//相乘加上
                        p1++;//P移向下一个元素
                        q1++;//Q移向下一个元素
                    }
                    else if(p1row==p&&p1col==i&&(q1row!=q||q1col!=i))//只有P符合
                    {
                        p1++;//结果为0，不用加，P移向下一个元素
                    }
                    else if((p1row!=p||p1col!=i)&&q1row==q&&q1col==i)//只有Q符合
                    {
                        q1++;//结果为0，不用加，Q移向下一个元素
                    }
                }
                qc=q1;//将Q的开始位置设置为当前位置
                if(result!=0)
                {
                    elem temp;
                    temp.row=p;
                    temp.col=q;
                    temp.value=result;
                    if(temp.value!=0)//结果非0
                        R.push(temp);//加入结果矩阵
                }
            }
            pc=p1;//P的开始位置设置为当前位置
        }
        rows=R.getrows();
        cols=R.getcols();
        terms=R.getterms();//结果矩阵赋给当前矩阵
        return 0;
    }
}

int sparseMatrix::multplus()
{
    int newrows,newcols,t;
    cin>>newrows>>newcols;
    sparseMatrix Q(newrows,newcols);
    cin>>t;
    for(int i=0;i<t;i++)
    {
        elem temp;
        cin>>temp.row>>temp.col>>temp.value;
        Q.push(temp);
    }//输入另一个矩阵
    if(cols!=newrows)//矩阵不相容
    {
        this->terms=Q.getterms();
        this->cols=Q.getcols();
        this->rows=Q.getrows();
        return -1;
    }
    else if(terms.size()!=0&&Q.getterms().size()!=0)//矩阵相容，并且当前矩阵非全0
    {
        sparseMatrix R(rows,newcols);
        vector<elem> RE;
        int psize=terms.size(),qsize=Q.getterms().size();
        for(int i=0;i<psize;i++)
        {
            for(int j=0;j<qsize;j++)
            {
                elem pelem=terms[i];
                elem qelem=Q.gettheterm(j);
                if(pelem.col==qelem.row)
                {
                    int in=0;
                    for(int r=0;r<RE.size();r++)
                    {
                        if(RE[r].row==pelem.row&&RE[r].col==qelem.col)
                        {
                            RE[r].value=pelem.value*qelem.value+RE[r].value;
                            in=1;
                            break;
                        }
                    }
                    if(in==0)
                    {
                        elem temp;
                        temp.row=terms[i].row;
                        temp.col=Q.gettheterm(j).col;
                        temp.value=terms[i].value*Q.gettheterm(j).value;
                        RE.push_back(temp);
                    }
                }
            }
        }
        cols=newcols;
        terms=RE;
    }
}


int main()
{
    int n;
    cin>>n;
    sparseMatrix a;
    for(int i=0;i<n;i++)
    {
        int op;
        cin>>op;
        if(op==1)
        {
            int rows,cols;
            cin>>rows>>cols;
            a.set(rows,cols);
        }
        else if(op==2)
        {
            int result=a.multiply();
            if(result==-1)
            {
                cout<<result<<endl;
            }
        }
        else if(op==3)
        {
            int result=a.add();
            if(result==-1)
            {
                cout<<result<<endl;
            }
        }
        else if(op==4)
        {
            a.output();
        }
        else if(op==5)
        {
            a.reserve();
        }
    }
    return 0;
}