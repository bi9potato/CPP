#include<iostream>
#include <stdlib.h>
#include <windows.h>
#include<fstream>
#include<string>
#include<iomanip>
using namespace std;

int num;                                   //��ѧ������

class student {
    friend class studentMessage;
private:
    string sno;
    string name;
    double score[4];								//score[0-3]��¼python��c++��fortran���ܷ�
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

    static void analyse(int ,student * );			//�����ɼ�
    void display();									//��ӡ�ɼ�
    void swap();									//��������Ͷ���->next����Ϣ,��������
};

student::student()									//����
{
    cout<<"������ѧ��ѧ�� : ";cin>>sno;
    cout<<"������ѧ������ : ";cin>>name;
    cout<<"������ѧ����python��c++��fortran�ɼ� : "<<endl;
    int a,b,c;
    cin>>a;
    while(a<0||a>100)
    {
        cout<<"PYTHON�ɼ�������������������: "<<endl;
        cin>>a;
    }
    cin>>b;
    while(b<0||b>100)
    {
        cout<<"C++����ɼ�������������������: "<<endl;
        cin>>b;
    }
    cin>>c;
    while(c<0||c>100)
    {
        cout<<"FORTRAN�ɼ�������������������: "<<endl;
        cin>>c;
    }
    score[0]=a;
    score[1]=b;
    score[2]=c;
    score[3]=a+b+c;
    next=NULL;
}

student::student(string sn,string n,double sco[4])	//��������
{													//���������û��Ҫ����Ϊһ��ʼû���Ǳ��湦�ܣ���ͷ�Ǹ����캯��ֻ�ܴӼ������룬
													//�ʲ��ܴ��ļ�д�룬Ҳ�����޸ģ��ʴ����ع��캯��������
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
    double average=0;	//ƽ����
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
    cout<<" ���������� : "<<num<<"     ƽ���� : "<<average<<endl;
    cout<<"\n ��     ��      ��     ������  "<<endl;
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

void student::swap()			//��������
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
    void add();                             //���
    void search();                          //����
    void del();                             //ɾ��
	void update();
    void showOne();                         //����
    void showAll();                         //�������ͬѧ���гɼ�
    void sort();                            //����
	void read();							//��
	void write();							//д
    void clear();                           //��ղ��˳�

};

studentMessage::studentMessage()
{
    first=NULL;			//ͷ���
    last=NULL;			//β���
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
            cout<<"\nѧ�����������ѧ���ɼ��Ѿ����ڣ�"<<endl;
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
	cout<<"��ӳɹ�!";
	system("pause");system("cls");
}

void studentMessage::search()
{
    string a;
    cout<<"\n������Ҫ���ҵ�ѧ����ѧ��:";cin>>a;
    student *t = first;
    while(t)
	{
        if(t->sno==a)
            break;
        t=t->next;
    }
    if(!t)
    {
        cout<<"\nδ�ҵ�Ҫ����ѧ����"<<endl;
		system("pause");system("cls");
        return;
    }
    cout<<"\n���ҳɹ���"<<endl;
    cout << " ѧ��    ����     PYTHON     C++     FORTRAN   �ܷ�" << endl;
    t->display();
	system("pause");system("cls");
}

void studentMessage::del()
{
    string a;
    cout<<"\n������Ҫɾ����ѧ����ѧ��: ";cin>>a;
    student *t = first;
    student *p=NULL;
    while(t){
        if(t->sno==a)break;
        p=t;
        t=t->next;
    }
    if(!t)
    {
        cout<<"\nδ�ҵ�Ҫɾ��ѧ����"<<endl;
		system("pause");system("cls");
        return;
    }
    if(!p)
    {
        first=first->next;
        cout<<"\n�ɹ�ɾ��ѧ��"<<a<<endl;
        delete t;
    }
    else
    {
        p->next=t->next;
        cout<<"�ɹ�ɾ��ѧ��"<<a<<endl;
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
        cout<<"\n��Ҫ������һ�ųɼ���������ѧ�����(1:PYTHON 2:C++ 3:FORTRAN):  ";cin>>a;
        if(a!=1 && a!=2 && a!=3)
            cout<<"\n������Ż������������������룡"<<endl;
        else break;
    }
    cout<<"\n\t�ɼ���������: \n"<<endl;
    student::analyse(a,first);
	system("pause");system("cls");
}

void studentMessage::showAll()
{
	if(!first) 
	{
		cout<<"��ǰϵͳ����ѧ����¼"<<endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "-----------------------�ɼ��б�------------------------"<< endl;
    cout << " ѧ��    ����     PYTHON     C++     FORTRAN     �ܷ�" << endl;
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
    int a,n=0;                  //n--����
    cout<<"��������Ӧ���(1.python 2.c++ 3.fortran 4.�ܳɼ�)����: ";
    while(1)
    {
        cin>>a;
        if (a!=1&&a!=2&&a!=3&&a!=4)
            cout<<"\n��������������������� : ";
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
    cout<<"\n\t �ɼ�������: "<<endl;
    cout<<"ѧ��    ����    �ɼ�    ����"<<endl;
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
    cout<<"\n������Ҫ�޸ĵ�ѧ����ѧ�Ż�����:";cin>>a;
    student *t = first;
    while(t)
	{
        if(t->sno==a || t->getName()==a) break;
        t=t->next;
    }
    if(!t)
    {
        cout<<"\nδ�ҵ�Ҫ�޸�ѧ����"<<endl;
        return;
    }
    cout<<"\nҪ�޸ĵ�ѧ����¼���£�"<<endl;
    cout << " ѧ��    ����     PYTHON     C++     FORTRAN     �ܷ�" << endl;
    t->display();

	int x=0,flag=0;
	string na;
	student *m;
	while(x!=6)
	{
		
		cout<<"\n1.�޸�ѧ�� 2.�޸����� 3.�޸�PYTHON���� 4.�޸�C++���� 5.�޸�FORTRAN���� 6.�˳��޸�:"; cin>>x;
		switch(x)
		{
		case 1:
			{
			cout<<"������ѧ��:";			
			cin>>na;
			m=first;
			while(m)
			{
				if(m->sno==na)
				{
					cout<<"\nѧ�����������ѧ���ɼ��Ѿ�����!"<<endl;flag=1;
					break;
				}
				m=m->next;
			}
			if(!flag) t->sno=na;
			break;
			}
		case 2:cout<<"����������:";			cin>>t->name;break;
		case 3:cout<<"������PYTHON����:";	cin>>t->score[0];t->score[3]=t->score[1]+t->score[0]+t->score[2];break;
		case 4:cout<<"������C++����:";		cin>>t->score[1];t->score[3]=t->score[1]+t->score[0]+t->score[2];break;
		case 5:cout<<"������FORTRAN����:";	cin>>t->score[2];t->score[3]=t->score[1]+t->score[0]+t->score[2];break;
		case 6:break;
		default:cout<<"�������������ѡ���޸���"<<endl;
		}
		cout<<"\n\t   �޸ĺ�ѧ����¼Ϊ��\n";
		cout << " ѧ��    ����     PYTHON     C++     FORTRAN   �ܷ�" << endl;
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
		if(first) //���Ѿ����ڽ�� 
		{ 
			student *s2 = first; 
			while(s2->next) //����β��� 
			{ 
				s2=s2->next; 
			} 
			s2->next=s; //���� 
		} 
		else //�������ڽ��(���) 
		{ 
			first=s; //���� 
		} 
		fs>>sno>>name>>score[0]>>score[1]>>score[2]>>score[3];
		num++;
		last=s;
	}
	fs.close(); 
	cout<<"\n��ȡ�ɹ�!\n";
}

void studentMessage::write()
{ 
	ofstream fs("Student.dat",ios::out|ios::binary ); 
	char c; 
	cout<<"\n��������,�Ƿ����?(����Y/N):";
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
	cout<<"\n����ɹ�!\n"; 
	system("pause");
	system("cls");
} 

void studentMessage::clear()
{
    char x;
    cout<<"ȷ��Ҫ���������Ϣ��(����Y/N) : ";cin>>x;
    if (toupper(x)!='Y')
    {
        cout<<"\nȡ�����\n"<<endl;
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
    cout<<"\n������!\n";
	system("pause");system("cls");
}

void showMenu()
{
    cout << "                               \n";
    cout << "===============================\n";
    cout << "      ѧ���ɼ�����ϵͳ\n\n";
    cout << "      1.��ʾ����ѧ���ɼ�\n";
    cout << "      2.�����Ϣ\n";
    cout << "      3.��ѯ��Ϣ\n";
    cout << "      4.ɾ����Ϣ\n";
    cout << "      5.�ɼ�����\n";
    cout << "      6.���Ƴɼ�����\n";
	cout << "      7.�޸���Ϣ\n";
	cout << "      8.����\n";
    cout << "      9.��ճɼ���Ϣ\n";
    cout << "      0.�˳�ϵͳ\n";
    cout << "===============================\n";
    cout << "                               \n";
}

int main()
{
	char x;
    int h;
	studentMessage stuM=studentMessage();
    cout<<"\n\n\t\t------��ӭ����ѧ���ɼ�����ϵͳ!-------"<<endl;
	cout<<"\t\t\t��Ҫ��ȡ������(����Y/N) : ";cin>>x;
	if (toupper(x)=='Y')
	{
		stuM.read();
	}
	system("pause");
	system("cls");

	
    while(1)
    {
        showMenu();
        cout << "�����������Ӧ����� : ";
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
            case 0: cout<<"\n�˳��ɹ���";return 0;
            default:cout<<"\n�������������������ȷ����š�"<<endl;
        }
    }
}