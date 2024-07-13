#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
using namespace std;

void readtext1()     //读文件函数,读取城市距离
{
	ifstream ifs;   //创建流对象
	ifs.open("城市距离.txt", ios::in);//打开文件
	string buf;
	while (getline(ifs, buf))         //利用循环和getline读取文件
	{
		cout << buf << endl;
	}

	ifs.close();        //关闭文件
}

void readtext2()     //读文件函数，读取交通信息
{
	ifstream ifs;    //创建流对象
	ifs.open("vehicle.txt", ios::in);//打开文件
	string buf;
	while (getline(ifs, buf))        //利用循环和getline读取文件
	{
		cout << buf << endl;
	}
	ifs.close();
}

void writetext1()    //写文件函数，写入城市距离文件，写入内容位于已有内容的下一行。
{
	ofstream ofs;
	ofs.open("城市距离.txt", ios::app);
	cout << "请输入补充信息： " << endl;
	string s;
	getline(cin, s);
	ofs << s << endl;
	ofs.close();
}

void writetext2()   //写文件函数，写入交通信息文件，写入内容位于所有已有内容的下一行。
{
	ofstream ofs;
	ofs.open("vehicle.txt", ios::app);
	cout << "请输入补充信息： " << endl;
	string s;
	getline(cin, s);
	ofs << s << endl;
	ofs.close();

}

void deletetext1()//删除城市距离文件中的指定内容
{
	string target;
	cout << "请输入需要删除的内容： " << endl;
	getline(cin, target);

	ifstream infile("城市距离.txt");
	ostringstream tempStream;
	tempStream << infile.rdbuf();
	string fileContents = tempStream.str();
	infile.close();

	size_t pos;
	while ((pos = fileContents.find(target)) != string::npos) 
	{
		fileContents.erase(pos, target.length());
	}
	ofstream outfile("城市距离.txt");
	outfile << fileContents;
	outfile.close();

	cout << "指定内容已删除。" << endl;


}

void deletetext2()
{
	string target;
	cout << "请输入需要删除的内容： " << endl;
	getline(cin, target);

	ifstream infile("vehicle.txt");
	ostringstream tempStream;
	tempStream << infile.rdbuf();
	string fileContents = tempStream.str();
	infile.close();

	size_t pos;
	while ((pos = fileContents.find(target)) != string::npos)
	{
		fileContents.erase(pos, target.length());
	}
	ofstream outfile("vehicle.txt");
	outfile << fileContents;
	outfile.close();

	cout << "指定内容已删除。" << endl;


}

void showmenu()//菜单函数
{
	cout << "************欢迎使用交通查询系统的文件管理系统************" << endl;
	cout << "*******************1.显示不同城市距离*********************" << endl;//对应readtext1函数
	cout << "******************2.显示列车及航班信息********************" << endl;//对应readtext2函数
	cout << "*****************3.补充更新城市距离信息*******************" << endl;//对应writetext1函数
	cout << "****************4.补充更新列车及航班信息******************" << endl;//对应writetext2函数
	cout << "**************5.删除城市距离文件的指定内容****************" << endl;//对应deletetext1函数
	cout << "************6.删除列车航班信息文件的指定内容**************" << endl;//对应deletetext2函数
	cout << "**********************7.退出系统**************************" << endl;//退出系统
	cout << "**********************************************************" << endl;
}

void exitsystem() //退出菜单函数
{
	cout << "欢迎下次使用！" << endl;
	system("pause");
	exit(0);
}

int main()
{    
	int choice = 0;
	while (true)
	{
		showmenu();
		cout << "请输入您的选择： " << endl;
		cin >> choice;

		switch (choice)
		{
		case 1:
			readtext1(); break;
		case 2:
			readtext2(); break;
		case 3:
			writetext1(); break;
		case 4:
			writetext2(); break;
		case 5:
			deletetext1(); break;
		case 6:
			deletetext2(); break;
		case 7:
			exitsystem(); break;




		default:
			system("cls");
			break;
		}



	}
	system("pause");
	return 0;
}