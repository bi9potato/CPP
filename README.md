# C++
YZU C++

1.课题内容：
（1）开发课题：学生成绩管理系统
（2）需求：
学生信息管理系统，是针对学校人事处的大量业务处理工作而开发的管理软件，是典型的管理信息系统。 
 它是一个教育单位不可缺少的部分，它的内容对于学校管理者来说是至关重要的，能有效的帮助学校和老师掌握学生的情况。在传统模式下利用人工进行学生信息管理，存在着较多的缺点，如：效率底，保密性差，时间一长将产生大量的文件和数据，更不便于查找，更新，维护等。诸如这些情况，令学校管理者对学生的信息管理带来了很大困难，严重影响了教育工作者的工作效率。随着科学技术的不断提高，使用日趋成熟的计算机技术来代替传统的人工模式，来实现学生信息的现代化管理，其强大的功能已为人们深刻认识，它已进入人类社会的各个领域并发挥着越来越重要的作用。作为计算机应用的一部分，使用计算机对学生信息进行管理，具有着手工管理所无法比拟的优点。例如：检索迅速、查找方便、易修改、可靠性高、存储量大、数据处理快捷、保密性好、寿命长、成本低等。这些优点能够极大地提高学生信息管理的效率，也是学校实现科学化、正规化管理的重要条件。因此，开发这样一套管理软件成为很有必要的事情。
（3）具体功能：
1.从磁盘读取数据
2.显示所有学生成绩信息
3.添加成绩信息
4.查询成绩信息
5.删除成绩信息
6.单科成绩分析
7.修改信息
8.将数据保存至磁盘
9.清空所有成绩信息

2.系统详细设计：
系统的总体设计思想：首先设计一个学生类，然后设计一个学生管理类，作为学生类的友元类，这样便可以调用所有学生类的函数。
学生类中包含一些学生用到的基础函数，如查看单科成绩，查看个人信息等；学生管理类可以调用学生类的基础函数，以此完成查询，排序，单科分析等功能，此外还有添加，删除，保存至磁盘，从磁盘读取，清空数据等功能

（1）系统整体流程：


（2）类的设计：
学生类：
class student {
    friend class studentMessage;				//友元类，学生管理
private:
    string sno;							//学号
    string name;							//姓名
    double score[4];						//score[0-3]记录python、c++、fortran和总分
    student * next;							//链表指针，指向下一个学生类
public:
    student();								//构造函数
	student(string sn, string n, double sco[4]);	//重载构造函数
    string getName()	{return name;}		//返回姓名
    string getSno()		{return sno;}			//返回学号
    double getPython()	{return score[0];}		//返回score[0] Python成绩
double getCpp()		{return score[1];}	//返回score[1]C++成绩
    double getFortran()	{return score[2];}		//返回score[3] FORTRAN成绩
    double gettotal()	{return score[3];}		//返回总分
    student* getNext()	{return next;}			//返回下一个学生类的地址	

    static void analyse(int ,student * );			//分析成绩
    void display();							//打印成绩
    void swap();							//交换对象和对象->next的信息,用于排序
};
学生管理类：
class studentMessage{
private:
    student * first;								//头指针
    student * last;								//尾指针
public:
    studentMessage();							//构造函数
    student* getFirst(){return first;}				//获取头指针
    student* getLast(){return last;}				//获取尾指针
    int getNum(){return num;}					//获取表中人数
    void add();                            	//添加
    void search();                             //查找
    void del();                            	//删除
    void showOne();                      		//分析
    void showAll();                        	//输出所有同学所有成绩
    void sort();                           		//排序
	void read();								//从磁盘读取
	void write();								//保存至磁盘
    void clear();                        	 	//清空并释放空间

};
（3）函数具体功能：
学生类函数：
student::student()									//构造
构造函数：每当创建一个新学生 student a时，从键盘输入学生借基础信息与成绩

student::student(string sn,string n,double sco[4])	//构造重载
重载构造函数：由于构造函数设定只能从键盘输入学生信息，局限性较大，故用此函数用于从磁盘读取学生信息，修改学生信息等。

void student::analyse(int a,student * first)
分析函数：统计单科优（90~100），良（70~89），中（60~69），不及格（0~59）的人数，并打印学生人数和单科均分。

void student::display()
输出函数：用于输出某一学生所有成绩

void student::swap()			//用于排序
交换函数：在学生管理类，交换函数中使用，交换两邻接学生类中数据。

学生管理类函数：
studentMessage::studentMessage()
构造函数：初始化头指针和尾指针为空

void studentMessage::add()
添加函数：向学生类链表中插入新的学生记录

void studentMessage::search()
查询函数：查询学生记录

void studentMessage::del()
删除函数：删除学生记录并释放被删除学生类的空间

void studentMessage::showOne()
分析单科函数：调用学生类中void student::analyse(int a,student * first)函数，此函数从键盘输入需要分析的科目代号

void studentMessage::showAll()
总输出函数：调用学生类中void student::display()函数，输出所有学生记录

void studentMessage::sort()
排序函数：调用学生类中void student::swap()函数，实现单科或总分从高到低排序

void studentMessage::update()
更新函数：更新学生记录，若学号相同禁止更新。

void studentMessage::read()
读取函数：从磁盘文件读取学生记录

void studentMessage::write()
保存函数：将学生类链表写入磁盘文件

void studentMessage::clear()
清空函数：清空所有学生类链表记录并释放空间

3.系统实现：
进入界面：选择是否从磁盘文件读取数据，这里选择的是Y（大小写皆可）

菜单界面：

选项1.显示所有学生成绩：

选项2.添加信息（无重复学号）：

选项3.查询：

选项4.删除：

选项5.成绩排序

选项6.成绩分析：

选项7.修改信息（无重复学号）：

选项8.保存

选项9.清空


选项0.退出



4.课程设计小结：
此次课程设计加深了我对友元类的理解，熟悉了友元类的使用，友元类是非常方便的，可以直接访问另一个类中的私有成员和受保护成员，提高效率，方便编程。但从网上查阅的信息来看，友元类破坏了类的封装性，提供了安全漏洞。由于我现阶段只在扫盲，对于友元类的缺点理解不够深刻，希望日后能加深友元类缺点的理解。
其次，此次课设代码设计有很多冗余，由于一开始参考了一些csdn的文章，我将学生类的构造函数定义为直接从键盘键入数据，导致后面的从磁盘读取，修改等功能无法实现，只能先删除，再重新输入正确的数据，局限性非常大，于是我增加了一个重载构造函数，解决了磁盘读取，数据修改等功能缺失。

