#include<iostream>
#include<string>
#include<sstream>
#include"city.h"
#include"vehicle.h"
#include"time.h"
#include"graph.h"

using namespace std;


//路径查询函数接入
void graph_find() {
	graph mygraph("city.txt", "vehicle.txt");
	cout << "已更新city.txt与vehicle.txt文件，正在更新交通图……" << endl;
	int flag;

	string transport_type;
	cout << "欢迎使用路径查询系统" << endl;
	do {
		cout << "输入1查询最快的路径，输入2查询费用最少的路径，输入3退出" << endl;
		cin >> flag;
		string city1, city2;
		int day, hour, minute;
		if (flag == 1 || flag == 2) {
			cout << "请输入你的出发地与目的地" << endl;
			
			cout << "请输入出发地：" << endl;
			cin >> city1;
			cout << "请输入目的地：" << endl;
			cin >> city2;
			
			cout << "请输入开始时间（日 时 分，例如 6 15 30表示本月的6号15点30分）： ";
			cin >> day >> hour >> minute;
			cout << "请输入数字选择查询类型" << endl;
		}
		switch (flag) {
		case 1:
			int flag_1;
			do {
				cout << "请输入数字设置路径" << endl;
				cout << "输入1：过程中不会更换交通工具类型" << endl <<
					"输入2：过程中可以更换交通工具类型" << endl <<
					"输入3：过程中将保持一种交通工具（直达）" << endl <<
					"输入4：退出最快路径查询" << endl;
				cin >> flag_1;
				switch (flag_1) {
				case 1:
					cout << "请选择交通工具类型（train/fly）：" << endl;
					cin >> transport_type;
					while (transport_type != "train" && transport_type != "fly") {
						cout << "输入的交通工具类型不正确，请重新输入。" << endl;
						cin >> transport_type;
					}
					mygraph.optimal(city1, city2, transport_type, day, hour, minute);
					break;
				case 2:
					mygraph.optimal_notype(city1, city2, day, hour, minute);
					break;
				case 3:
					cout << "请选择交通工具类型（train/fly）：" << endl;
					cin >> transport_type;
					while (transport_type != "train" && transport_type != "fly") {
						cout << "输入的交通工具类型不正确，请重新输入。" << endl;
						cin >> transport_type;
					}
					mygraph.optimal_DFS(city1, city2, transport_type, day, hour, minute);
					break;
				case 4:
					cout << "正在退出最快路径查询系统" << endl;
					break;
				default:
					cout << "无效选择，请重新输入" << endl;
				}
			} while (flag_1 != 4);
			break;
		case 2:
			int flag_2;
			do {
				cout << "请输入数字设置路径" << endl;
				cout << "输入1：过程中不会更换交通工具类型" << endl <<
					"输入2：过程中可以更换交通工具类型" << endl <<
					"输入3：过程中将保持一种交通工具（直达）" << endl <<
					"输入4：退出费用最少路径查询" << endl;
				cin >> flag_2;
				switch (flag_2) {
				case 1:
					int flag_2_1;
					cout << "是否需要设置出发时间上限，是请输入1，否请输入2" << endl;
					cin >> flag_2_1;
					while (flag_2_1 != 2 && flag_2_1 != 1) {
						cout << "输入的数字无效，请重新输入" << endl;
						cin >> flag_2_1;
					}
					if (flag_2_1 == 2) {
						cout << "请选择交通工具类型（train/fly）：" << endl;
						cin >> transport_type;
						while (transport_type != "train" && transport_type != "fly") {
							cout << "输入的交通工具类型不正确，请重新输入。" << endl;
							cin >> transport_type;
						}
						mygraph.optimal_money(city1, city2, transport_type, day, hour, minute);
					}
					if (flag_2_1 == 1) {
						cout << "请输入出发时间上限，输入1，则出发时间将会在预设时间的1天内筛选" << endl;
						int extra_day;
						cin >> extra_day;
						cout << "请选择交通工具类型（train/fly）：" << endl;
						cin >> transport_type;
						while (transport_type != "train" && transport_type != "fly") {
							cout << "输入的交通工具类型不正确，请重新输入。" << endl;
							cin >> transport_type;
						}
						mygraph.optimal_money_limit(city1, city2, day, hour, minute, transport_type, extra_day);
					}
					break;
				case 2:
					int flag_2_2;
					cout << "是否需要设置出发时间上限，是请输入1，否请输入2" << endl;
					cin >> flag_2_2;
					while (flag_2_2 != 2 && flag_2_2 != 1) {
						cout << "输入的数字无效，请重新输入" << endl;
						cin >> flag_2_2;
					}
					if (flag_2_2 == 2) {
						mygraph.optimal_money_notype(city1, city2, day, hour, minute);
					}
					if (flag_2_2 == 1) {
						cout << "请输入出发时间上限，输入1，则出发时间将会在预设时间的1天内筛选" << endl;
						int extra_day;
						cin >> extra_day;
						mygraph.optimal_money_notype_limit(city1, city2, day, hour, minute, extra_day);
					}
					break;
				case 3:
					int flag_2_3;
					cout << "是否需要设置出发时间上限，是请输入1，否请输入2" << endl;
					cin >> flag_2_3;
					while (flag_2_3 != 2 && flag_2_3 != 1) {
						cout << "输入的数字无效，请重新输入" << endl;
						cin >> flag_2_3;
					}
					if (flag_2_3 == 2) {
						cout << "请选择交通工具类型（train/fly）：" << endl;
						cin >> transport_type;
						while (transport_type != "train" && transport_type != "fly") {
							cout << "输入的交通工具类型不正确，请重新输入。" << endl;
							cin >> transport_type;
						}
						mygraph.optimal_DFS_money(city1, city2, transport_type, day, hour, minute);
					}
					if (flag_2_3 == 1) {
						cout << "请输入出发时间上限，输入1，则出发时间将会在预设时间的1天内筛选" << endl;
						int extra_day;
						cin >> extra_day;
						cout << "请选择交通工具类型（train/fly）：" << endl;
						cin >> transport_type;
						while (transport_type != "train" && transport_type != "fly") {
							cout << "输入的交通工具类型不正确，请重新输入。" << endl;
							cin >> transport_type;
						}
						mygraph.optimal_DFS_money_limit(city1, city2, day, hour, minute, transport_type, extra_day);
					}
					break;
				case 4:
					cout << "正在退出费用最少路径查询系统" << endl;
					break;
				default:
					cout << "无效选择，请重新输入" << endl;
				}
			} while (flag_2 != 4);
			break;
		case 3:
			cout << "正在退出路径查询系统" << endl;
			break;
		default:
			cout << "输入无效。请重新输入" << endl;
		}
	} while (flag != 3);
	return;
}




//信息查询函数接入
void txt_find(){
	graph mygraph("city.txt", "vehicle.txt");
	cout << "已更新city.txt与vehicle.txt文件，正在更新交通图……" << endl;
	int flag;

	cout << "欢迎使用信息查询系统" << endl;
	do {
		cout << "请输入数字查询相应的文件" << endl;
		cout << "输入1：查询城市信息" << endl <<
			"输入2：查询交通信息" << endl <<
			"输入3：退出信息查询系统" << endl;
		cin >> flag;
		switch(flag){
		case 1:
			mygraph.find_city();
			break;
		case 2:
			cout << "是否需要时间范围限制，是输入1，否输入2" << endl;
			int flag_1;
			cin >> flag_1;
			while (flag_1 != 2 && flag_1 != 1) {
				cout << "输入的数字无效，请重新输入" << endl;
				cin >> flag_1;
			}
			if(flag_1==2)
				mygraph.find_vehicle();
			else if(flag_1 == 1)
				mygraph.find_vehicle_limit();
			break;
		case 3:
			cout << "正在退出信息查询系统" << endl;
			break;
		default:
			cout << "输入的数字无效，请重新输入" << endl;
		}
	} while (flag!=2);
	return;
}