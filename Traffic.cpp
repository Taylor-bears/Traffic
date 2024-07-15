#include<iostream>
#include<string>
#include<sstream>
#include"city.h"
#include"vehicle.h"
#include"time.h"
#include"graph.h"

using namespace std;


//·����ѯ��������
void graph_find() {
	graph mygraph("city.txt", "vehicle.txt");
	cout << "�Ѹ���city.txt��vehicle.txt�ļ������ڸ��½�ͨͼ����" << endl;
	int flag;

	string transport_type;
	cout << "��ӭʹ��·����ѯϵͳ" << endl;
	do {
		cout << "����1��ѯ����·��������2��ѯ�������ٵ�·��������3�˳�" << endl;
		cin >> flag;
		string city1, city2;
		int day, hour, minute;
		if (flag == 1 || flag == 2) {
			cout << "��������ĳ�������Ŀ�ĵ�" << endl;
			
			cout << "����������أ�" << endl;
			cin >> city1;
			cout << "������Ŀ�ĵأ�" << endl;
			cin >> city2;
			
			cout << "�����뿪ʼʱ�䣨�� ʱ �֣����� 6 15 30��ʾ���µ�6��15��30�֣��� ";
			cin >> day >> hour >> minute;
			cout << "����������ѡ���ѯ����" << endl;
		}
		switch (flag) {
		case 1:
			int flag_1;
			do {
				cout << "��������������·��" << endl;
				cout << "����1�������в��������ͨ��������" << endl <<
					"����2�������п��Ը�����ͨ��������" << endl <<
					"����3�������н�����һ�ֽ�ͨ���ߣ�ֱ�" << endl <<
					"����4���˳����·����ѯ" << endl;
				cin >> flag_1;
				switch (flag_1) {
				case 1:
					cout << "��ѡ��ͨ�������ͣ�train/fly����" << endl;
					cin >> transport_type;
					while (transport_type != "train" && transport_type != "fly") {
						cout << "����Ľ�ͨ�������Ͳ���ȷ�����������롣" << endl;
						cin >> transport_type;
					}
					mygraph.optimal(city1, city2, transport_type, day, hour, minute);
					break;
				case 2:
					mygraph.optimal_notype(city1, city2, day, hour, minute);
					break;
				case 3:
					cout << "��ѡ��ͨ�������ͣ�train/fly����" << endl;
					cin >> transport_type;
					while (transport_type != "train" && transport_type != "fly") {
						cout << "����Ľ�ͨ�������Ͳ���ȷ�����������롣" << endl;
						cin >> transport_type;
					}
					mygraph.optimal_DFS(city1, city2, transport_type, day, hour, minute);
					break;
				case 4:
					cout << "�����˳����·����ѯϵͳ" << endl;
					break;
				default:
					cout << "��Чѡ������������" << endl;
				}
			} while (flag_1 != 4);
			break;
		case 2:
			int flag_2;
			do {
				cout << "��������������·��" << endl;
				cout << "����1�������в��������ͨ��������" << endl <<
					"����2�������п��Ը�����ͨ��������" << endl <<
					"����3�������н�����һ�ֽ�ͨ���ߣ�ֱ�" << endl <<
					"����4���˳���������·����ѯ" << endl;
				cin >> flag_2;
				switch (flag_2) {
				case 1:
					int flag_2_1;
					cout << "�Ƿ���Ҫ���ó���ʱ�����ޣ���������1����������2" << endl;
					cin >> flag_2_1;
					while (flag_2_1 != 2 && flag_2_1 != 1) {
						cout << "�����������Ч������������" << endl;
						cin >> flag_2_1;
					}
					if (flag_2_1 == 2) {
						cout << "��ѡ��ͨ�������ͣ�train/fly����" << endl;
						cin >> transport_type;
						while (transport_type != "train" && transport_type != "fly") {
							cout << "����Ľ�ͨ�������Ͳ���ȷ�����������롣" << endl;
							cin >> transport_type;
						}
						mygraph.optimal_money(city1, city2, transport_type, day, hour, minute);
					}
					if (flag_2_1 == 1) {
						cout << "���������ʱ�����ޣ�����1�������ʱ�佫����Ԥ��ʱ���1����ɸѡ" << endl;
						int extra_day;
						cin >> extra_day;
						cout << "��ѡ��ͨ�������ͣ�train/fly����" << endl;
						cin >> transport_type;
						while (transport_type != "train" && transport_type != "fly") {
							cout << "����Ľ�ͨ�������Ͳ���ȷ�����������롣" << endl;
							cin >> transport_type;
						}
						mygraph.optimal_money_limit(city1, city2, day, hour, minute, transport_type, extra_day);
					}
					break;
				case 2:
					int flag_2_2;
					cout << "�Ƿ���Ҫ���ó���ʱ�����ޣ���������1����������2" << endl;
					cin >> flag_2_2;
					while (flag_2_2 != 2 && flag_2_2 != 1) {
						cout << "�����������Ч������������" << endl;
						cin >> flag_2_2;
					}
					if (flag_2_2 == 2) {
						mygraph.optimal_money_notype(city1, city2, day, hour, minute);
					}
					if (flag_2_2 == 1) {
						cout << "���������ʱ�����ޣ�����1�������ʱ�佫����Ԥ��ʱ���1����ɸѡ" << endl;
						int extra_day;
						cin >> extra_day;
						mygraph.optimal_money_notype_limit(city1, city2, day, hour, minute, extra_day);
					}
					break;
				case 3:
					int flag_2_3;
					cout << "�Ƿ���Ҫ���ó���ʱ�����ޣ���������1����������2" << endl;
					cin >> flag_2_3;
					while (flag_2_3 != 2 && flag_2_3 != 1) {
						cout << "�����������Ч������������" << endl;
						cin >> flag_2_3;
					}
					if (flag_2_3 == 2) {
						cout << "��ѡ��ͨ�������ͣ�train/fly����" << endl;
						cin >> transport_type;
						while (transport_type != "train" && transport_type != "fly") {
							cout << "����Ľ�ͨ�������Ͳ���ȷ�����������롣" << endl;
							cin >> transport_type;
						}
						mygraph.optimal_DFS_money(city1, city2, transport_type, day, hour, minute);
					}
					if (flag_2_3 == 1) {
						cout << "���������ʱ�����ޣ�����1�������ʱ�佫����Ԥ��ʱ���1����ɸѡ" << endl;
						int extra_day;
						cin >> extra_day;
						cout << "��ѡ��ͨ�������ͣ�train/fly����" << endl;
						cin >> transport_type;
						while (transport_type != "train" && transport_type != "fly") {
							cout << "����Ľ�ͨ�������Ͳ���ȷ�����������롣" << endl;
							cin >> transport_type;
						}
						mygraph.optimal_DFS_money_limit(city1, city2, day, hour, minute, transport_type, extra_day);
					}
					break;
				case 4:
					cout << "�����˳���������·����ѯϵͳ" << endl;
					break;
				default:
					cout << "��Чѡ������������" << endl;
				}
			} while (flag_2 != 4);
			break;
		case 3:
			cout << "�����˳�·����ѯϵͳ" << endl;
			break;
		default:
			cout << "������Ч������������" << endl;
		}
	} while (flag != 3);
	return;
}




//��Ϣ��ѯ��������
void txt_find(){
	graph mygraph("city.txt", "vehicle.txt");
	cout << "�Ѹ���city.txt��vehicle.txt�ļ������ڸ��½�ͨͼ����" << endl;
	int flag;

	cout << "��ӭʹ����Ϣ��ѯϵͳ" << endl;
	do {
		cout << "���������ֲ�ѯ��Ӧ���ļ�" << endl;
		cout << "����1����ѯ������Ϣ" << endl <<
			"����2����ѯ��ͨ��Ϣ" << endl <<
			"����3���˳���Ϣ��ѯϵͳ" << endl;
		cin >> flag;
		switch(flag){
		case 1:
			mygraph.find_city();
			break;
		case 2:
			cout << "�Ƿ���Ҫʱ�䷶Χ���ƣ�������1��������2" << endl;
			int flag_1;
			cin >> flag_1;
			while (flag_1 != 2 && flag_1 != 1) {
				cout << "�����������Ч������������" << endl;
				cin >> flag_1;
			}
			if(flag_1==2)
				mygraph.find_vehicle();
			else if(flag_1 == 1)
				mygraph.find_vehicle_limit();
			break;
		case 3:
			cout << "�����˳���Ϣ��ѯϵͳ" << endl;
			break;
		default:
			cout << "�����������Ч������������" << endl;
		}
	} while (flag!=2);
	return;
}