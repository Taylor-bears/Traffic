#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
using namespace std;

void readtext1()     //���ļ�����,��ȡ���о���
{
	ifstream ifs;   //����������
	ifs.open("���о���.txt", ios::in);//���ļ�
	string buf;
	while (getline(ifs, buf))         //����ѭ����getline��ȡ�ļ�
	{
		cout << buf << endl;
	}

	ifs.close();        //�ر��ļ�
}

void readtext2()     //���ļ���������ȡ��ͨ��Ϣ
{
	ifstream ifs;    //����������
	ifs.open("vehicle.txt", ios::in);//���ļ�
	string buf;
	while (getline(ifs, buf))        //����ѭ����getline��ȡ�ļ�
	{
		cout << buf << endl;
	}
	ifs.close();
}

void writetext1()    //д�ļ�������д����о����ļ���д������λ���������ݵ���һ�С�
{
	ofstream ofs;
	ofs.open("���о���.txt", ios::app);
	cout << "�����벹����Ϣ�� " << endl;
	string s;
	getline(cin, s);
	ofs << s << endl;
	ofs.close();
}

void writetext2()   //д�ļ�������д�뽻ͨ��Ϣ�ļ���д������λ�������������ݵ���һ�С�
{
	ofstream ofs;
	ofs.open("vehicle.txt", ios::app);
	cout << "�����벹����Ϣ�� " << endl;
	string s;
	getline(cin, s);
	ofs << s << endl;
	ofs.close();

}

void deletetext1()//ɾ�����о����ļ��е�ָ������
{
	string target;
	cout << "��������Ҫɾ�������ݣ� " << endl;
	getline(cin, target);

	ifstream infile("���о���.txt");
	ostringstream tempStream;
	tempStream << infile.rdbuf();
	string fileContents = tempStream.str();
	infile.close();

	size_t pos;
	while ((pos = fileContents.find(target)) != string::npos) 
	{
		fileContents.erase(pos, target.length());
	}
	ofstream outfile("���о���.txt");
	outfile << fileContents;
	outfile.close();

	cout << "ָ��������ɾ����" << endl;


}

void deletetext2()
{
	string target;
	cout << "��������Ҫɾ�������ݣ� " << endl;
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

	cout << "ָ��������ɾ����" << endl;


}

void showmenu()//�˵�����
{
	cout << "************��ӭʹ�ý�ͨ��ѯϵͳ���ļ�����ϵͳ************" << endl;
	cout << "*******************1.��ʾ��ͬ���о���*********************" << endl;//��Ӧreadtext1����
	cout << "******************2.��ʾ�г���������Ϣ********************" << endl;//��Ӧreadtext2����
	cout << "*****************3.������³��о�����Ϣ*******************" << endl;//��Ӧwritetext1����
	cout << "****************4.��������г���������Ϣ******************" << endl;//��Ӧwritetext2����
	cout << "**************5.ɾ�����о����ļ���ָ������****************" << endl;//��Ӧdeletetext1����
	cout << "************6.ɾ���г�������Ϣ�ļ���ָ������**************" << endl;//��Ӧdeletetext2����
	cout << "**********************7.�˳�ϵͳ**************************" << endl;//�˳�ϵͳ
	cout << "**********************************************************" << endl;
}

void exitsystem() //�˳��˵�����
{
	cout << "��ӭ�´�ʹ�ã�" << endl;
	system("pause");
	exit(0);
}

int main()
{    
	int choice = 0;
	while (true)
	{
		showmenu();
		cout << "����������ѡ�� " << endl;
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