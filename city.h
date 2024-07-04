#pragma once
#ifndef _CITY_H
#define _CITY_H

#include<iostream>
#include<string>
#include<vector>

using namespace std;

class city {
private:
	vector<string> name; //一维向量存储城市的名称
	vector<int> distance;
	vector<vector<int>> edges; //二维向量存储城市间的距离
public:
	city(const string& file_path) {} //以文件作为输入参数（即需要用到city.txt）
	~city();//析构
};



#endif