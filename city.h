#pragma once
#ifndef _CITY_H
#define _CITY_H

#include<iostream>
#include<string>
#include<vector>

using namespace std;

class city {
private:
	vector<string> name; //һά�����洢���е�����
	vector<int> distance;
	vector<vector<int>> edges; //��ά�����洢���м�ľ���
public:
	city(const string& file_path) {} //���ļ���Ϊ�������������Ҫ�õ�city.txt��
	~city();//����
};



#endif