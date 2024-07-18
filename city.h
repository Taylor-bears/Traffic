#pragma once
#ifndef _CITY_H
#define _CITY_H

#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<utility>
#include<algorithm>
#include<cmath>
#include <map>
#include<fstream>
#include<sstream>

#define M_PI 3.14159265358979323846

using namespace std;

//自定义哈希函数：为 pair<string, string> 类型提供一个自定义的哈希函数。这个哈希函数可以是一个结构体或者
// 一个函数对象，用来计算 pair<string, string> 类型的键的哈希值
struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1, T2>& pair) const {
        auto hash1 = std::hash<T1>{}(pair.first);
        auto hash2 = std::hash<T2>{}(pair.second);
        return hash1 ^ hash2;
    }
};

//自定义相等比较函数：为 pair<string, string> 类型提供一个自定义的相等比较函数。这个函数用来比较两个 
// pair<string, string> 类型的键是否相等
struct pair_equal {
    template <class T1, class T2>
    bool operator () (const std::pair<T1, T2>& lhs, const std::pair<T1, T2>& rhs) const {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    }
};

class city {
public://测试用public
	vector<string> name; //一维向量存储城市的名称
    //因为无序表中的部分对象类型没有pair类型，所以要重新定义哈希函数和相等比较函数
    unordered_map<pair<string, string>, int, pair_hash, pair_equal> distance_map;//不同城市之间直线距离的哈希函数
    //连通距离
    unordered_map<pair<string, string>, int, pair_hash, pair_equal> link_map;//不同城市之间连通距离的哈希函数
    vector<vector<int>> dist;

	city(const string& file_path, const string& file_path2); //以文件作为输入参数（即需要用到city.txt）
    city();
    //还需要添加、修改、删除函数
};





#endif