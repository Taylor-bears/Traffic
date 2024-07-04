#pragma once
#ifndef _CITY_H
#define _CITY_H

#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<utility>

using namespace std;

//�Զ����ϣ������Ϊ pair<string, string> �����ṩһ���Զ���Ĺ�ϣ�����������ϣ����������һ���ṹ�����
// һ������������������ pair<string, string> ���͵ļ��Ĺ�ϣֵ
struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1, T2>& pair) const {
        auto hash1 = std::hash<T1>{}(pair.first);
        auto hash2 = std::hash<T2>{}(pair.second);
        return hash1 ^ hash2;
    }
};

//�Զ�����ȱȽϺ�����Ϊ pair<string, string> �����ṩһ���Զ������ȱȽϺ�����������������Ƚ����� 
// pair<string, string> ���͵ļ��Ƿ����
struct pair_equal {
    template <class T1, class T2>
    bool operator () (const std::pair<T1, T2>& lhs, const std::pair<T1, T2>& rhs) const {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    }
};

class city {
public:
	vector<string> name; //һά�����洢���е�����
    //��Ϊ������еĲ��ֶ�������û��pair���ͣ�����Ҫ���¶����ϣ��������ȱȽϺ���
    unordered_map<pair<string, string>, int, pair_hash, pair_equal> distance_map;//��ͬ����֮�����Ĺ�ϣ����
	
public:
	city(const string& file_path); //���ļ���Ϊ�������������Ҫ�õ�city.txt��
};



#endif