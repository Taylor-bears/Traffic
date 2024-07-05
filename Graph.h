#pragma once
#ifndef _GRAPH_H
#define _GRAPH_H

#include<iostream>
#include<unordered_map>
#include<fstream>
#include<string>
#include"city.h"
#include"vehicle.h"
#include"time.h"

using namespace std;

//�ڽӾ����룺����ÿ���㷴ӳ���Ǳߵ�Ȩֵ����ÿ�������(1,2)�����1�Ͷ�Ӧ���ǳ������֣����������
//�����е�ֵ��ʵ���Ǳߵ�Ȩֵ����ͨ��ʽ�������������м���ڶ����ͨ��ʽ��һ�����ֵ�ͻ��Ӧ�����ͨ��ʽ��
//�ʾ����е�ÿ���㶼��һ��vector����vectoe��ÿ��Ԫ�ؾ���һ���ࣨtrain����fly��

class graph { //Ҫ���õ����е���Ϣ�����Զ�Ҫ�̳�
public:
	unordered_map<string, int> traffic_map;//������źͳ��������γ�ӳ��
	city mycity;//���������϶����Ǽ̳У��˴�����Ĭ�Ϲ��캯��
	int number;//��������
	vector<vector<vector<vehicle>>> edges;

	graph(const string& file_path1, const string& file_path2);
	graph();//Ĭ�Ϲ���
	
};


#endif