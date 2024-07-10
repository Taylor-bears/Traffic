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
	void Time_Dijkstra(int start, int n, times current_time, string type);//�ڶ���time��ָ��ʱ��
	vehicle getmin(vector<vehicle>& ve, times current_time, string last_vehicle_type,string last_vehicle_name);//�ڶ���time��ָ��ʱ��
	void display(vector<times>& dist, vector<PathStep>& path, vector<bool>& S, int v, int n, string type);//��ʾĳ�㵽ĳ������·��
	void optimal();//�õ����ŷ���
};


#endif