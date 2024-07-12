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

//�ڽӾ����룺����ÿ���㷴ӳ���Ǳߵ�Ȩֵ����ÿ�������(1,2)�����1�Ͷ�Ӧ���ǳ������֣����������
//�����е�ֵ��ʵ���Ǳߵ�Ȩֵ����ͨ��ʽ�������������м���ڶ����ͨ��ʽ��һ�����ֵ�ͻ��Ӧ�����ͨ��ʽ��
//�ʾ����е�ÿ���㶼��һ��vector����vectoe��ÿ��Ԫ�ؾ���һ���ࣨtrain����fly��

struct PathStep {
	int prev;
	vehicle veh; // �洢�����Ľ�ͨ������Ϣ

	PathStep(int p = -1, vehicle v = vehicle()) : prev(p), veh(v) {}
};

struct PathStep3 {
	int prev; // �������е�����
	int next; // Ŀ�ĵس��е�����
	vehicle veh; // �洢�����Ľ�ͨ������Ϣ

	PathStep3(int p = -1, int n = -1, vehicle v = vehicle()) : prev(p), next(n), veh(v) {}
};

class graph { //Ҫ���õ����е���Ϣ�����Զ�Ҫ�̳�
public:
	unordered_map<string, int> traffic_map;//������źͳ��������γ�ӳ��
	city mycity;//���������϶����Ǽ̳У��˴�����Ĭ�Ϲ��캯��
	int number;//��������
	vector<vector<vector<vehicle>>> edges;

	graph(const string& file_path1, const string& file_path2);
	graph();//Ĭ�Ϲ���
	double time_transfer(int hour, int minute);//ʱ��ת������������


	//��ʾ���ʱ������
	//���ɻ�����
	vehicle getmin(vector<vehicle>& ve, times current_time, string type, string last_vehicle_name);
	void Time_Dijkstra(int start, int n, times current_time, string type);
	//�ɻ�����
	vehicle getmin2(vector<vehicle>& ve, times current_time, string last_vehicle_type, string last_vehicle_nam);
	void Time_Dijkstra2(int v, int n, times current_time);
	//ֱ��
	void DFS(int v, int end, const string& type, const string& vehicleName, vector<PathStep3>& path,
		times& current_time, vector<PathStep3>& bestPath, times& bestTime);
	void findBestPath(int start, int end, const times& preset_time, const string& type);



	//��ʾ���ٷ��õ����
	//���ɻ����ߣ���һ����֮�����ʡǮ���ڶ����Ƿ�Χ�ڵ���ʡǮ��
	vehicle getminmoney(vector<vehicle>& ve, times current_time, string type, string last_vehicle_name);
	void Money_Dijkstra(int v, int n, times current_time, string type);
	//������ʱ��
	vehicle getminmoney_limit(vector<vehicle>& ve, times current_time, string type, string last_vehicle_name, int extra_hour);
	void Money_Dijkstra_limit(int v, int n, times current_time, string type, int extra_hour);
	//�ɻ����ߣ���һ����֮�����ʡǮ���ڶ����Ƿ�Χ�ڵ���ʡǮ��
	vehicle getminmoney2(vector<vehicle>& ve, times current_time, string last_vehicle_type, string last_vehicle_name);
	void Money_Dijkstra2(int v, int n, times current_time);
	//������ʱ��
	vehicle getminmoney2_limit(vector<vehicle>& ve, times current_time, string last_vehicle_type, string last_vehicle_name, int extra_hour);
	void Money_Dijkstra2_limit(int v, int n, times current_time, int extra_time);
	//ֱ���һ����֮�����ʡǮ���ڶ����Ƿ�Χ�ڵ���ʡǮ��
	void DFS2(int v, int end, const string& type, const string& vehicleName, vector<PathStep3>& path,
		times& current_time, vector<PathStep3>& bestPath, times& bestTime, double& cheapestCost);
	void findBestPath2(int start, int end, const times& preset_time, const string& type);
	//������ʱ��
	void DFS2_limit(int v, int end, const string& type, const string& vehicleName, vector<PathStep3>& path,
		times& current_time, vector<PathStep3>& bestPath, times& bestTime, double& cheapestCost, int extra_time);
	void findBestPath2_limit(int start, int end, const times& preset_time, const string& type, int extra_hour);


	//������ʾ����
	//���ɻ�����
	void display(vector<times>& dist, vector<PathStep>& path, vector<bool>& S, int v, int n, string type);
	//�ɻ�����
	void display2(vector<times>& dist, vector<PathStep>& path, vector<bool>& S, int v, int n);
	//�������ù���
	void optimal();//�õ����ŷ���
	void optimal2();


	//���Թ���
	void show();
	void tiaoshi();
	bool timecheck(times time1, times time2, int wait_hours);
};


#endif