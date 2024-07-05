#pragma once
#include "graph.h"
#include <iostream>
#include<string>
#include<fstream>
#include<vector>

using namespace std;

//带参构造函数
//在主函数中，需要使用"city.txt"和""初始化
graph::graph(const string& file_path1, const string& file_path2) { 
	mycity = city(file_path1);//这里需要赋值
	number = mycity.name.size();
	edges.resize(number, vector<vector<vehicle>>(number));//此时建立的三维数组，前两维的长度已由城市数量确定
	
	//下面让每一个城市对应一个编号，便于后面矩阵中每个数字
	for (int i = 0; i < number; i++) {
		this->traffic_map[mycity.name[i]] = i;
	}

	//下面建立图（需要读取交通工具文件），也是本程序最重要的储存部分
	ifstream input("vehicle.txt");
	char nosense;//用于保存无用的符号
	string city_name1;
	string city_name2;
	//下面是vehicle的五个数据
	string type;
	string identifier;	
	times mytime1;
	double consume;
	times mytime2;
	int money;

	while (input >> nosense) { //读取（
		string day1;
		string hour1;
		string minute1;
		string hour_past;
		string minute_past;
		string day2;
		string hour2;
		string minute2;
		string cost;
		if (nosense == '(') {
			getline(input, city_name1, ',');//读取 Beijing               
			getline(input, city_name2, ')');//读取 Wuhan    
			int num1 = traffic_map[city_name1];
			int num2 = traffic_map[city_name2];
			input >> nosense;//读取","
			getline(input, type, ',');//1作为类型存储
			getline(input, identifier, ',');//2作为编号存储
			getline(input, day1, '.');
			getline(input, hour1, ':');
			getline(input, minute1, ',');
			mytime1 = times(stoi(day1), stoi(hour1), stoi(minute1));//3作为时间1存储
			getline(input, hour_past, ':');
			getline(input, minute_past, ',');
			consume = time_transfer(stoi(hour_past),stoi(minute_past));//4作为耗时需要保存
			getline(input, day2, '.');
			getline(input, hour2, ':');
			getline(input, minute2, ',');
			mytime2 = times(stoi(day2), stoi(hour2), stoi(minute2));//5作为时间1存储
			getline(input, cost);
			money = stoi(cost);//6作为费用存储
			vehicle myvehicle(type, identifier, mytime1, consume, mytime2, money);//已经读取好了一个工具类
			//将工具读入边的向量中，即邻接矩阵的点上
			edges[num1][num2].push_back(myvehicle);//num1和num2是两个城市的编号（注意这里是有向图，并不对称）
		}
	}
	//通过以上操作只是建立了有连通处两地的连接，
	//图中还要包含0和∞两种特殊情况
	for (int i = 0; i < number; i++) {
		for (int j = 0; j < number; j++) {
			if (edges[i][j].empty()) {//如果为空，则
				if (i == j)
					edges[i][j].push_back(vehicle());
				//此时调用默认构造函数，每个值都为0，通过识别""空串(type)即可知道
				else {
					times timetmp1;//调用默认构造，内部成员都为0
					times timetmp2;
					edges[i][j].push_back(vehicle("MAX", "MAX", timetmp1, 11.1111, timetmp2, -1));
					//此时建立的是无穷大边值，通过识别"MAX"(type)即可知道
				}					
			}
		}
	}
}

//默认构造函数
graph::graph() {
	//无
}

//时间转换函数的定义
double graph::time_transfer(int hour, int minute)
{
	double a;
	a = hour + minute / 60.0;
	a = static_cast<int>(a * 10 + 0.5);
	return a / 10.0;
}