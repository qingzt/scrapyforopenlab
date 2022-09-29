#include<iostream>
#include<string>
using namespace std;
struct student{
	string xm;//姓名 
	string dh;//电话 
	int bj;//班级 
	int ss;//宿舍 
};
class linearlist{
	public:
		linearlist(int n){stu= new student[n];zs=n;length=0;};
		void insert(string xm1,string dh1,int bj1,int ss1);
		void del(string xm1);//删除 
		void change(string xm1, int a,int b);
		int search(string xm1);
		int yihuo(int bj1);
	private:
		student *stu;
		int zs;//学生总数 
		int length=0;//数组元素个数，即插入时用到的序号 
};

void linearlist::insert(string xm1,string dh1,int bj1,int ss1){
	stu[length].xm=xm1; stu[length].dh=dh1; stu[length].bj=bj1; stu[length].ss=ss1; length++;}

void linearlist::del(string xm1){
	for (int i = 0; i < zs; i++) {
		if (stu[i].xm==xm1) {
			copy(stu+i+1,stu+zs,stu+i);
			length--;}//表示现在长度已经-1，插入时尾序号-1 
	}
}

void linearlist::change(string xm1, int a,int b) {
	for (int i = 0; i < length; i++) {
		if (stu[i].xm==xm1) {
			switch(a){
				case 1:stu[i].dh=b;break;
				case 2:stu[i].bj=b;break;
				case 3:stu[i].ss=b;break;
			}
		}
	}
}

int linearlist::search(string xm1){
	for (int i = 0; i < length; i++) {
		if(stu[i].xm==xm1) return 1;}
	return 0;
}

int linearlist::yihuo(int bj1){
	int sum=0;
	for (int i = 0; i < length; i++){
		if(stu[i].bj==bj1) sum=sum^stu[i].ss;
	}
	return sum;
}

int main()
{
int n,m,bj1,ss1;//指令数，每次输入的数字，待输入的班级和宿舍 
string xm1,dh1;
int bb;//用于change函数的第三个参数 
int aa;//用于change函数的第二个参数 
cin>>n; 
linearlist list(n);
/*cin>>xm1>>dh1>>bj1>>ss1;
list.insert(xm1,dh1,bj1,ss1);*/
for(int k=0;k<n;k++)
{
	cin>>m;
	switch(m){
		case 0:{
			cin>> xm1 >> dh1 >> bj1 >> ss1;
			cout<<"case1"<<endl;
			list.insert(xm1,dh1,bj1,ss1);
			break;
		}
		case 1:{
			cin>>xm1;
			list.del(xm1);
			break;
		}
		case 2:{
			cin>>xm1>>aa>>bb;
			list.change(xm1,aa,bb);
			break;
		}
		case 3:{
			cin>>xm1;
			cout<<list.search(xm1)<<endl;
			break;
		}
		case 4:{
			cin>>bj1;
			cout<<list.yihuo(bj1)<<endl;
			break;
		}
	}
}


return 0;
}