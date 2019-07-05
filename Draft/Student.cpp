#include "conio.h"
#include <fstream>
#include <iostream>
#include <stdio.h>

using namespace std;

class student //定义学生类
{
      public:	  //定义学生类的私有成员
	char name[20]; //名字
	char sex[5];   //性别
	int number;    //学号
	int score[3];  //分数
	int total;     //总分
	int average;   //平均分

	student();      //学生构造函数，用于学生数据的初始化及保存学生数据
	void add();     //添加学生信息函数
	void output();  //输出学生信息函数
	void find();    //查找学生数据函数
	void modify();  //修改学生信息函数
	void deleted(); //删除学生信息函数
	void sort();    //排序函数
	void save();    //保存学生信息并写入文件函数
	void load();    //打开写有学生信息的文件的函数
};

student stu[100];
int n = 0;
void student::add() //添加函数
{
	char flag = 'Y';
	while (toupper(flag) == 'Y') {
		cin >> stu[n];
		n++;
		cout << " 要继续添加吗(y/n)";
		cin >> flag;
		if (toupper(flag) != 'Y') {
			if (toupper(flag) == 'N') {
				break;
			} else {
				cout << "错误，请重输：";
				cin >> flag;
			}
		}
	}
}
void student::output() //输出函数
{
	if (n != 0) {
		cout << " ---------------------------------------------------------------------------\n";
		cout << " number     name      sex    math    C++     English    total    average\n";
		cout << " --------------------------------------------------------------------------- \n";
		for (int t = 0; t < n; t++) {
			cout << stu[t];
		}
	}
	while (cin.get() != '\n')
		continue;
	;
}
void student::find() //查找函数
{
	int f3 = 0;
	char n1[20];
	student temp;
	cout << " 输入你要查找的人的姓名: ";
	cin >> n1;
	for (int j = 0; j < n; j++) {
		if (strcmp(stu[j].name, n1) == 0) {
			temp = stu[j];
			f3 = 1;
		}
	}
	if (f3 == 0)
		cout << "对不起，没有你要查找的学生成绩" << endl;

	else {
		cout << " ---------------------------------------------------------------------------\n";
		cout << " number name sex math C++ English total average\n";
		cout << " --------------------------------------------------------------------------- \n";
		cout << " " << temp.number << " " << temp.name << " " << temp.sex << " " << temp.score[0]
		     << " " << temp.score[1] << " " << temp.score[2] << " " << temp.total << " " << temp.average << endl;
	}
	while (cin.get() != '\n')
		continue;
	;
}
void student::modify() //修改函数
{
	int f4 = 0;
	int t;
	char n2[50];
	cout << " 输入你要修改的人的姓名:";
	cin >> n2;
	for (int j = 0; j < n; j++) {
		if (strcmp(stu[j].name, n2) == 0) {
			t = j;
			f4 = 1;
		}
	}
	if (f4 == 0)
		cout << "对不起，没有你要修改的学生成绩" << endl;
	else {
		cout << "请输入学号: ";
		cin >> stu[t].number;
		cout << " 姓名: ";
		cin >> stu[t].name;
		cout << " 性别 : ";
		cin >> stu[t].sex;
		cout << " 数学成绩: ";
		cin >> stu[t].score[0];
		cout << " C++成绩: ";
		cin >> stu[t].score[1];
		cout << " 英语成绩: ";
		cin >> stu[t].score[2];
		stu[t].total = stu[t].score[0] + stu[t].score[1] + stu[t].score[2];
		stu[t].average = stu[t].total / 3;
		cout << " 修改成功 !" << endl;
	}
	while (cin.get() != '\n')
		continue;
	;
}
void student::deleted() //删除函数
{
	char n3[20];
	bool f5 = 0;
	char c;
	do {
		cout << "请输入您要删除的学生姓名：";
		cin >> n3;
		for (int i = 0; i < n; i++) {
			if (strcmp(n3, stu[i].name) == 0) {
				f5 = 1;
				n--;
				do {
					stu[i] = stu[i + 1];
					i++;
				} while (i <= n);
			}
		}
		if (f5 == 0)
			cout << "您要求删除的对象本来就不存在！";
		cout << "要继续删除吗？(y/n)" << endl;
		cin >> c;
		if (toupper(c) != 'Y' && toupper(c) != 'N') {
			cout << "输入指令错误！请重新输入Y或N！" << endl;
			cin >> c;
		}
	} while (toupper(c) == 'Y');
	while (cin.get() != '\n')
		continue;
	;
}
void student::sort() //排序函数
{
	int i, j, k;
	student s3;
	for (i = 0; i < (n - 1); i++) {
		k = i;
		for (j = i + 1; j < n; j++)
			if (stu[j].average > stu[i].average)
				k = j;
		if (k != i) {
			s3 = stu[i];
			stu[i] = stu[k];
			stu[k] = s3;
		}
	}
	cout << "\n\n排序成功!\n\n";
}

void student::save() //保存函数
{
	char filename1[20];
	cout << "请输入文件名: ";
	cin >> filename1;
	ofstream fout(filename1, ios::app);
	if (!fout)
		cout << "文件不能打开!" << endl;
	else {
		for (int i = 0; i < n; i++)
			fout << ' ' << stu[i].name << ' ' << stu[i].sex << ' ' << stu[i].number << ' '
			     << stu[i].score[0] << ' ' << stu[i].score[1] << ' ' << stu[i].score[2] << ' ' << stu[i].total << ' ' << stu[i].average << ' ';
		cout << "保存成功!" << endl;
	}
	fout.close();
	while (cin.get() != '\n')
		continue;
	;
}
void student::load() //读取函数
{
	char filename2[20];
	cout << "请输入你要读取的文件名: ";
	cin >> filename2;
	ifstream fin(filename2, ios::in);
	if (!fin)
		cout << "文件打不开 !" << endl;
	else {
		for (int i = 0;; i++, n = i - 1) {
			if (fin.eof())
				break;
			fin >> stu[i].name >> stu[i].sex >> stu[i].number >> stu[i].score[0] >> stu[i].score[1] >> stu[i].score[2] >> stu[i].total >> stu[i].average;
		}
		cout << "文件已读取成功!" << endl;
	}
	fin.close();
	while (cin.get() != '\n')
		continue;
	;
}
student &student::operator=(student T) //重载=
{
	strcpy(name, T.name);
	strcpy(sex, T.sex);
	number = T.number;
	for (int i = 0; i < 3; i++)
		score[i] = T.score[i];
	total = T.total;
	average = T.average;
	return (*this);
}
ostream &student::operator<<(ostream &scout, student &s2) //重载<<
{
	cout << setw(6) << s2.number << setw(10) << s2.name << setw(8) << s2.sex << setw(8) << s2.score[0]
	     << setw(8) << s2.score[1] << setw(10) << s2.score[2] << setw(10) << s2.total << setw(8) << s2.average << endl;
	return scout;
}
istream &student::operator>>(istream &scin, student &s1) //重载>>
{
	cout << " \t学号:";
	scin >> s1.number;
	cout << " \t姓名:";
	scin >> s1.name;
	cout << " \t性别 :";
	scin >> s1.sex;
	cout << " \t数学成绩:";
	scin >> s1.score[0];
	cout << " \tC++成绩:";
	scin >> s1.score[1];
	cout << " \t英语成绩:";
	scin >> s1.score[2];
	s1.total = s1.score[0] + s1.score[1] + s1.score[2];
	s1.average = s1.total / 3;
	return scin;
}
student::student() //构造函数
{
	strcpy(name, " ");
	strcpy(sex, " ");
	number = 0;
	for (int i = 0; i < 3; i++)
		score[i] = 0;
	total = 0;
	average = 0;
}
void menu() //菜单函数
{
	cout << "\n\n\n学生成绩管理系统主菜单 " << endl;
	cout << "\n\n\n1.添加学生信息 " << endl;
	cout << "2.输出学生信息 " << endl;
	cout << "3.查找学生信息 " << endl;
	cout << "4.修改学生信息 " << endl;
	cout << "5.删除学生信息 " << endl;
	cout << "6.学生信息排序 " << endl;
	cout << "7.保存数据 " << endl;
	cout << "8.读出数据 " << endl;
	cout << "9.退出系统 " << endl;
	cout << "\n\n请选择(1~9)并按回车键确认:";
}

int main() //主函数
{
	int choose;
	student s;
	do {
		menu();
		cin >> choose;
		switch (choose) {
		case 1:
			s.add();
			break;
		case 2:
			s.output();
			break;
		case 3:
			s.find();
			break;
		case 4:
			s.modify();
			break;
		case 5:
			s.deleted();
			break;
		case 6:
			s.sort();
			break;
		case 7:
			s.save();
			break;
		case 8:
			s.load();
			break;
		default:
			break;
		}
	} while (choose != 0);
}
