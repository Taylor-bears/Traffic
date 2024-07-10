#pragma once
#ifndef _GRAPH_H
#define _GRAPH_H

#include<iostream>
#include<unordered_map>
#include<fstream>
#include<string>
#include"city.h"
#include"vehicle.h"
#include"times.h"

using namespace std;

//邻接矩阵构想：他的每个点反映的是边的权值，而每个点比如(1,2)这里的1就对应的是城市名字，而这个点在
//矩阵中的值其实就是边的权值（交通方式），由于两城市间存在多个交通方式，一个点的值就会对应多个交通方式，
//故矩阵中的每个点都是一个vector，而vectoe中每个元素就是一个类（train或者fly）

struct PathStep {
	int prev;
	vehicle veh; // 存储完整的交通工具信息

	PathStep(int p = -1, vehicle v = vehicle()) : prev(p), veh(v) {}
};

class graph { //要利用到所有的信息，所以都要继承
public:
	unordered_map<string, int> traffic_map;//矩阵序号和城市名称形成映射
	city mycity;//这是类的组合而不是继承，此处调用默认构造函数
	int number;//城市数量
	vector<vector<vector<vehicle>>> edges;

	graph(const string& file_path1, const string& file_path2);
	graph();//默认构造
	double time_transfer(int hour, int minute);//时间转换函数的申明
	//显示最快时间的情况
	void Time_Dijkstra(int start, int n, times current_time, string type);//第二个time是指定时间
	vehicle getmin(vector<vehicle>& ve, times current_time, string last_vehicle_type,string last_vehicle_name);//第二个time是指定时间
	void display(vector<times>& dist, vector<PathStep>& path, vector<bool>& S, int v, int n, string type);//显示某点到某点的最短路径
	void optimal();//得到最优方案
};


#endif