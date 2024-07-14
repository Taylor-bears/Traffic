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

struct PathStep3 {
	int prev; // 出发城市的索引
	int next; // 目的地城市的索引
	vehicle veh; // 存储完整的交通工具信息

	PathStep3(int p = -1, int n = -1, vehicle v = vehicle()) : prev(p), next(n), veh(v) {}
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
	//不可换工具
	vehicle getmin(vector<vehicle>& ve, times current_time, string type, string last_vehicle_name);
	void Time_Dijkstra(int start, int n, times current_time, string type);
	//可换工具
	vehicle getmin2(vector<vehicle>& ve, times current_time, string last_vehicle_type, string last_vehicle_nam);
	void Time_Dijkstra2(int v, int n, times current_time);
	//直达
	void DFS(int v, int end, const string& type, const string& vehicleName, vector<PathStep3>& path,
		times& current_time, vector<PathStep3>& bestPath, times& bestTime);
	void findBestPath(int start, int end, const times& preset_time, const string& type);



	//显示最少费用的情况
	//不可换工具（第一种是之后的最省钱，第二种是范围内的最省钱）
	vehicle getminmoney(vector<vehicle>& ve, times current_time, string type, string last_vehicle_name);
	void Money_Dijkstra(int v, int n, times current_time, string type);
	//可限制时间
	vehicle getminmoney_limit(vector<vehicle>& ve, times current_time, string type, string last_vehicle_name, int extra_day);
	void Money_Dijkstra_limit(int v, int n, times current_time, string type, int extra_day);
	//可换工具（第一种是之后的最省钱，第二种是范围内的最省钱）
	vehicle getminmoney2(vector<vehicle>& ve, times current_time, string last_vehicle_type, string last_vehicle_name);
	void Money_Dijkstra2(int v, int n, times current_time);
	//可限制时间
	vehicle getminmoney2_limit(vector<vehicle>& ve, times current_time, string last_vehicle_type, string last_vehicle_name, int extra_day);
	void Money_Dijkstra2_limit(int v, int n, times current_time, int extra_day);
	//直达（第一种是之后的最省钱，第二种是范围内的最省钱）
	void DFS2(int v, int end, const string& type, const string& vehicleName, vector<PathStep3>& path,
		times& current_time, vector<PathStep3>& bestPath, times& bestTime, double& cheapestCost);
	void findBestPath2(int start, int end, const times& preset_time, const string& type);
	//可限制时间
	void DFS2_limit(int v, int end, const string& type, const string& vehicleName, vector<PathStep3>& path,
		times& current_time, vector<PathStep3>& bestPath, times& bestTime, double& cheapestCost, int extra_day);
	void findBestPath2_limit(int start, int end, const times& preset_time, const string& type, int extra_day);



	//公共显示功能
	//不可换工具
	void display(vector<times>& dist, vector<PathStep>& path, vector<bool>& S, int v, int n, string type);
	


	//说明：直达的情况，有没有type限制是没有意义的，因为前后都是固定一种类型
	//公共调用功能
	void optimal();//找最快路径（有type限制）
	void optimal( string city1, string city2, string transport_type, int day, int hour, int minute);
	void optimal_money();//找最省钱路径（有type限制）
	void optimal_money( string city1, string city2, string transport_type, int day, int hour, int minute);
	void optimal_notype();//找最快路径（无type限制）
	void optimal_notype( string city1, string city2, int day, int hour, int minute);
	void optimal_money_notype();//找最省钱路径（无type限制）
	void optimal_money_notype( string city1, string city2, int day, int hour, int minute);
	void optimal_money_limit();//找最省钱路径（有type、time限制）
	void optimal_money_limit(string city1, string city2, int day, int hour, int minute, string transport_type, int extra_day);
	void optimal_money_notype_limit();//找最省钱路径（无type限制、有time限制）
	void optimal_money_notype_limit(string city1, string city2, int day, int hour, int minute, int extra_day);
	void optimal_DFS();//找直通最快路径
	void optimal_DFS( string city1, string city2, string transport_type, int day, int hour, int minute);
	void optimal_DFS_money();//找直通最省钱路径
	void optimal_DFS_money( string city1, string city2, string transport_type, int day, int hour, int minute);
	void optimal_DFS_money_limit();//找直通最省钱路径（有time限制）
	void optimal_DFS_money_limit( string city1, string city2, int day, int hour, int minute, string transport_type, int extra_day);



	//调试功能
	void show();
	void tiaoshi();
	bool timecheck(times time1, times time2, int wait_hours);



	//查询功能
	void find_city();
	void find_vehicle();
	void find_vehicle_limit();
};


#endif