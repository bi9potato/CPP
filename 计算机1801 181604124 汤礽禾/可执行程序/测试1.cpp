#include<iostream>
#include <stdlib.h>
#include <windows.h>
#include<fstream>
#include<string>
#include<iomanip>
using namespace std;

int num;                                   //总学生人数

class student {
    friend class studentMessage;
private:
    string sno;
    string name;
    double score[4];								//score[0-3]记录python、c++、fortran和总分
    student * next;
public:
    student();
	student(string sn, string n, double sco[4]);
    string getName()	{return name;}
    string getSno()		{return sno;}
    double getPython()	{return score[0];}
    double getCpp()		{return score[1];}
    double getFortran()	{return score[2];}
    double gettotal()	{return score[3];}
    student* getNext()	{return next;}

    static void analyse(int ,student * );			//分析成绩
    void display();									//打印成绩
    void swap();									//交换对象和对象->next的信息,用于排序
};

student::student()									//构造
{
    cout<<"请输入学生学号 : ";cin>>sno;
    cout<<"请输入学生姓名 : ";cin>>name;
    cout<<"请输入学生的python、c++、fortran成绩 : "<<endl;
    int a,b,c;
    cin>>a;
    while(a<0||a>100)
    {
        cout<<"PYTHON成绩输入有误，请重新输入: "<<endl;
        cin>>a;
    }
    cin>>b;
    while(b<0||b>100)
    {
        cout<<"C++输入成绩输入有误，请重新输入: "<<endl;
        cin>>b;
    }
    cin>>c;
    while(c<0||c>100)
    {
        cout<<"FORTRAN成绩输入有误，请重新输入: "<<endl;
        cin>>c;
    }
    score[0]=a;
    score[1]=b;
    score[2]=c;
    score[3]=a+b+c;
    next=NULL;
}

student::student(string sn,string n,double sco[4])	//构造重载
{													//这个函数本没必要，因为一开始没考虑保存功能，上头那个构造函数只能从键盘输入，
													//故不能从文件写入，也不能修改，故此重载构造函数诞生了
	sno = sn;
	name = n;
	for(int i = 0; i <= 3; i++)
	{
		score[i] = sco[i];
	}
	next=NULL;
}
	

void student::analyse(int a,student * first)	
{
	int x;
	if(a==1) x = 0;
	else if(a ==2) x = 1;
	else x = 2;
    int you=0,liang=0,zhong=0,bujige=0;
    student * t=first;
    double average=0;	//平均分
    while(t)
    {
        int b = int(t->score[x]/10);
        switch(b)
        {
        case 10:
        case 9:you++;	break;
        case 8:
        case 7:liang++;	break;
        case 6:zhong++;	break;
        default:bujige++;
        }
        average+=t->score[x];
        t=t->next;
    }
    average=average/num;
    cout<<" 考生总人数 : "<<num<<"     平均分 : "<<average<<endl;
    cout<<"\n 优     良      中     不及格  "<<endl;
    cout<<" "<<you<<" \t"<<liang<<" \t"<<zhong<<"\t"<<bujige<<endl;
}

void student::display()
{
    cout<<" "<<setw(3)<<sno<<"     "<<setw(3)<<name<<"      ";
    for (int i=0;i<=3;i++)
    {
        cout<<setw(3)<<score[i]<<"       ";
    }
    cout<<endl;
}

void student::swap()			//用于排序
{
    int j;
    string na,id;
    double sco[4];
    na=name;name=next->name;next->name=na;
    id=sno;sno=next->sno;next->sno=id;
    for(j=0;j<=3;j++)
    {
        sco[j]=score[j];
        score[j]=next->score[j];
        next->score[j]=sco[j];
    }
}

class studentMessage{
private:
    student * first;
    student * last;
public:
    studentMessage();
    student* getFirst(){return first;}
    student* getLast(){return last;}
    int getNum(){return num;}
    void add();                             //添加
    void search();                          //查找
    void del();                             //删除
	void update();
    void showOne();                         //分析
    void showAll();                         //输出所有同学所有成绩
    void sort();                            //排序
	void read();							//读
	void write();							//写
    void clear();                           //清空并退出

};

studentMessage::studentMessage()
{
    first=NULL;			//头结点
    last=NULL;			//尾结点
    num=0;
}

void studentMessage::add()
{
    student * t =new student;
    student *p = first;
    while(p)
	{
        if(p->sno==t->sno)
        {
            cout<<"\n学号输入错误或该学生成绩已经存在！"<<endl;
			Sleep(2000);
			system("cls");
            return;
        }
        p=p->next;
    }
    num++;
    if(first==NULL)
    {
        first=last=t;

    }
    else
    {
        last->next=t;
        last=last->next;
    }
	cout<<"添加成功!";
	system("pause");system("cls");
}

void studentMessage::search()
{
    string a;
    cout<<"\n请输入要查找的学生的学号:";cin>>a;
    student *t = first;
    while(t)
	{
        if(t->sno==a)
            break;
        t=t->next;
    }
    if(!t)
    {
        cout<<"\n未找到要查找学生！"<<endl;
		system("pause");system("cls");
        return;
    }
    cout<<"\n查找成功！"<<endl;
    cout << " 学号    姓名     PYTHON     C++     FORTRAN   总分" << endl;
    t->display();
	system("pause");system("cls");
}

void studentMessage::del()
{
    string a;
    cout<<"\n请输入要删除的学生的学号: ";cin>>a;
    student *t = first;
    student *p=NULL;
    while(t){
        if(t->sno==a)break;
        p=t;
        t=t->next;
    }
    if(!t)
    {
        cout<<"\n未找到要删除学生！"<<endl;
		system("pause");system("cls");
        return;
    }
    if(!p)
    {
        first=first->next;
        cout<<"\n成功删除学生"<<a<<endl;
        delete t;
    }
    else
    {
        p->next=t->next;
        cout<<"成功删除学生"<<a<<endl;
        delete t;
    }

    num--;
	system("pause");system("cls");
}

void studentMessage::showOne()
{
    int a;
    while(1)
    {
        cout<<"\n想要分析哪一门成绩？请输入学科序号(1:PYTHON 2:C++ 3:FORTRAN):  ";cin>>a;
        if(a!=1 && a!=2 && a!=3)
            cout<<"\n输入序号或名称有误，请重新输入！"<<endl;
        else break;
    }
    cout<<"\n\t成绩分析如下: \n"<<endl;
    student::analyse(a,first);
	system("pause");system("cls");
}

void studentMessage::showAll()
{
	if(!first) 
	{
		cout<<"当前系统内无学生记录"<<endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "-----------------------成绩列表------------------------"<< endl;
    cout << " 学号    姓名     PYTHON     C++     FORTRAN     总分" << endl;
    student *t = first;
    while(t){
        t->display();
        t=t->next;
    }
	system("pause");
	system("cls");
}

void studentMessage::sort()
{
    int a,n=0;                  //n--排名
    cout<<"请输入相应序号(1.python 2.c++ 3.fortran 4.总成绩)排序: ";
    while(1)
    {
        cin>>a;
        if (a!=1&&a!=2&&a!=3&&a!=4)
            cout<<"\n输入序号有误，请重新输入 : ";
        else break;
    }
    student *t=first;
    student *p=t;
	/*student *tail=last;
	for(;t->next!=NULL;t=t->next)
		for(student * q=t->next;q!=NULL;q=q->next)
			if(t->next->score[a-1]>=t->score[a-1])
            {
                t->swap();
            }*/
	while(p->next)
    {
        t=first;
        while(t->next)
        {
            if(t->next->score[a-1]>=t->score[a-1])
            {
                t->swap();
            }
            t=t->next;
        }
        p=p->next;
    }
    t = first;
    cout<<"\n\t 成绩表如下: "<<endl;
    cout<<"学号    姓名    成绩    排名"<<endl;
    while(t)
	{
        n++;
        cout<<" "<<t->getSno()<<"  \t"<<t->getName()<<"  \t";
        switch(a)
        {
            case 1 :cout<<t->getPython()<<"  \t"<<n<<endl;break;
            case 2 :cout<<t->getCpp()<<"  \t"<<n<<endl;break;
            case 3 :cout<<t->getFortran()<<"  \t"<<n<<endl;break;
            case 4 :cout<<t->gettotal()<<"  \t"<<n<<endl;break;
        }
        t=t->next;
    }
	system("pause");system("cls");
}
//
void studentMessage::update()
{
	string a;
    cout<<"\n请输入要修改的学生的学号或姓名:";cin>>a;
    student *t = first;
    while(t)
	{
        if(t->sno==a || t->getName()==a) break;
        t=t->next;
    }
    if(!t)
    {
        cout<<"\n未找到要修改学生！"<<endl;
        return;
    }
    cout<<"\n要修改的学生记录如下："<<endl;
    cout << " 学号    姓名     PYTHON     C++     FORTRAN     总分" << endl;
    t->display();

	int x=0,flag=0;
	string na;
	student *m;
	while(x!=6)
	{
		
		cout<<"\n1.修改学号 2.修改姓名 3.修改PYTHON分数 4.修改C++分数 5.修改FORTRAN分数 6.退出修改:"; cin>>x;
		switch(x)
		{
		case 1:
			{
			cout<<"请输入学号:";			
			cin>>na;
			m=first;
			while(m)
			{
				if(m->sno==na)
				{
					cout<<"\n学号输入错误或该学生成绩已经存在!"<<endl;flag=1;
					break;
				}
				m=m->next;
			}
			if(!flag) t->sno=na;
			break;
			}
		case 2:cout<<"请输入姓名:";			cin>>t->name;break;
		case 3:cout<<"请输入PYTHON分数:";	cin>>t->score[0];t->score[3]=t->score[1]+t->score[0]+t->score[2];break;
		case 4:cout<<"请输入C++分数:";		cin>>t->score[1];t->score[3]=t->score[1]+t->score[0]+t->score[2];break;
		case 5:cout<<"请输入FORTRAN分数:";	cin>>t->score[2];t->score[3]=t->score[1]+t->score[0]+t->score[2];break;
		case 6:break;
		default:cout<<"输入错误，请重新选择修改项"<<endl;
		}
		cout<<"\n\t   修改后学生记录为：\n";
		cout << " 学号    姓名     PYTHON     C++     FORTRAN   总分" << endl;
		t->display();
	}
	system("pause");
	system("cls");
}
void studentMessage::read()
{
	ifstream fs; 
	student *s=first; 
	string sno,name;
	double score[4];
	fs.open("Student.dat",ios::in|ios::binary );  
	fs>>sno>>name>>score[0]>>score[1]>>score[2]>>score[3];
	
	while(fs.good()) 
	{
		s= new student(sno,name,score);
		student *s2 = first;
		if(first) //若已经存在结点 
		{ 
			student *s2 = first; 
			while(s2->next) //查找尾结点 
			{ 
				s2=s2->next; 
			} 
			s2->next=s; //连接 
		} 
		else //若不存在结点(表空) 
		{ 
			first=s; //连接 
		} 
		fs>>sno>>name>>score[0]>>score[1]>>score[2]>>score[3];
		num++;
		last=s;
	}
	fs.close(); 
	cout<<"\n读取成功!\n";
}

void studentMessage::write()
{ 
	ofstream fs("Student.dat",ios::out|ios::binary ); 
	char c; 
	cout<<"\n保存数据,是否继续?(输入Y/N):";
	cin>>c; 
	if(toupper(c)!='Y')
		return; 
	student *s=first; 
	while(s) 
	{ 
		fs<<s->sno<<" "<<s->name<<" "<<s->score[0]<<" "<<s->score[1]<<" "<<s->score[2]<<" "<<s->score[3]<<endl;
		s=s->next; 
	} 
	fs.close(); 
	cout<<"\n保存成功!\n"; 
	system("pause");
	system("cls");
} 

void studentMessage::clear()
{
    char x;
    cout<<"确认要清空所有信息？(输入Y/N) : ";cin>>x;
    if (toupper(x)!='Y')
    {
        cout<<"\n取消清空\n"<<endl;
        return;
    }
    student *t = first;
    student *p;
    while(t){
        p=t;
        t=t->next;
        delete p;
    }
	last=first=NULL;
    cout<<"\n清空完成!\n";
	system("pause");system("cls");
}

void showMenu()
{
    cout << "                               \n";
    cout << "===============================\n";
    cout << "      学生成绩管理系统\n\n";
    cout << "      1.显示所有学生成绩\n";
    cout << "      2.添加信息\n";
    cout << "      3.查询信息\n";
    cout << "      4.删除信息\n";
    cout << "      5.成绩排序\n";
    cout << "      6.单科成绩分析\n";
	cout << "      7.修改信息\n";
	cout << "      8.保存\n";
    cout << "      9.清空成绩信息\n";
    cout << "      0.退出系统\n";
    cout << "===============================\n";
    cout << "                               \n";
}

int main()
{
	char x;
    int h;
	studentMessage stuM=studentMessage();
    cout<<"\n\n\t\t------欢迎进入学生成绩管理系统!-------"<<endl;
	cout<<"\t\t\t需要读取数据吗？(输入Y/N) : ";cin>>x;
	if (toupper(x)=='Y')
	{
		stuM.read();
	}
	system("pause");
	system("cls");

	
    while(1)
    {
        showMenu();
        cout << "请输入操作对应的序号 : ";
        cin >>h;
        cout<<endl;
        switch(h)
        {
            case 1: stuM.showAll();	break;
            case 2: stuM.add();	break;
            case 3: stuM.search();	break;
            case 4: stuM.del();	break;
            case 5: stuM.sort();break;
            case 6: stuM.showOne();	break;
			case 7: stuM.update();break;
			case 8: stuM.write();break;
            case 9: stuM.clear();break;
            case 0: cout<<"\n退出成功！";return 0;
            default:cout<<"\n输入序号有误！请输入正确的序号。"<<endl;
        }
    }
}