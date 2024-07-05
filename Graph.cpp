#pragma once
#include "graph.h"
#include <iostream>
#include<string>
#include<fstream>

using namespace std;

//���ι��캯��
//���������У���Ҫʹ��"city.txt"��""��ʼ��
graph::graph(const string& file_path1, const string& file_path2) { 
	mycity = city(file_path1);//������Ҫ��ֵ
	number = mycity.name.size();
	edges.resize(number, vector<vector<vehicle>>(number));//��ʱ��������ά���飬ǰ��ά�ĳ������ɳ�������ȷ��
	
	//������ÿһ�����ж�Ӧһ����ţ����ں��������ÿ������
	for (int i = 0; i < number; i++) {
		this->traffic_map[mycity.name[i]] = i;
	}

	//���潨��ͼ����Ҫ��ȡ��ͨ�����ļ�����Ҳ�Ǳ���������Ҫ�Ĵ��沿��
	ifstream input("vehicle.txt");
	char nosense;//���ڱ������õķ���
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
	

	while (input >> nosense) { //��ȡ��
		if (nosense == '(') {
			getline(input, city_name1, ',');//��ȡ Beijing               
			getline(input, city_name2, ')');//��ȡ Wuhan    
			int num1 = traffic_map[city_name1];
			int num2 = traffic_map[city_name2];


			edges[num1, num2];
		}
	}
}

//Ĭ�Ϲ��캯��
graph::graph() {
	//��
}