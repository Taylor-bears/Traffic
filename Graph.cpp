#pragma once
#include "graph.h"
#include <iostream>
#include<string>

using namespace std;

graph::graph(const string& file_path) {
	city mycity("city.txt");
	number = mycity.name.size();
	edges.resize(number, vector<vector<vehicle>>(number));//此时建立的三维数组，前两维的长度已由城市数量确定


}