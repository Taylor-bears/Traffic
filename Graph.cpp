#pragma once
#include "graph.h"
#include <iostream>
#include<string>

using namespace std;

graph::graph(const string& file_path) {
	city mycity("city.txt");
	number = mycity.name.size();
	edges.resize(number, vector<vector<vehicle>>(number));//��ʱ��������ά���飬ǰ��ά�ĳ������ɳ�������ȷ��


}