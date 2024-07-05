#pragma once
#include "graph.h"
#include <iostream>
#include<string>
#include<fstream>

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
	string type;
	string identifier;
	int day1;
	int hour1;
	int minute1;
	int hour_past;
	int minute_past;
	int day2;
	int hour2;
	int minute2;
	int money;
	

	while (input >> nosense) { //读取（
		if (nosense == '(') {
			getline(input, city_name1, ',');//读取 Beijing               
			getline(input, city_name2, ')');//读取 Wuhan    
			int num1 = traffic_map[city_name1];
			int num2 = traffic_map[city_name2];


			edges[num1, num2];
		}
	}
}

//默认构造函数
graph::graph() {
	//无
}