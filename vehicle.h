#pragma once
#ifndef _VEHICLE_H
#define _VEHICLE_H

#include<iostream>
#include"times.h"
#include<string>

using namespace std;

//vehicle�ı�����ͼ�бߵ���Ϣ�����бȽϵ�ʱ��Ƚ�consume��money
class vehicle :public times { //train��time�̳� 
public:
	//�������Ƿ���train��fly����ʽ��ʵ���һ�£�����������һ��ͳһ����ʽ�����ļ��У��˱�������ʽҲֻ����
	//train��fly���֣���������Ҳ��Ϊ�˱��ڽ����ڽӾ���ͳһ����
	string type;
	string name;
	times time1;
	double consume;//��ʱ����Ҫ����ʱ��ת����������ʱ������ʽ��1.35����
	times time2;
	double money;

public:
	//������Ĭ�Ϲ��캯������ʱ�����Ĺ����൱���ڽӾ����е�0��������������û�о���
	vehicle();//Ĭ�Ϲ���	
	vehicle(string x1, string x2, times t3, double t4, times t5, double x6);//�ڹ����ʱ��Ҫע�⵽ʱ���ȡ����Ҫ�ȹ���3��time��
	//ע�⣬������Ĭ���βεĹ��췽ʽ������Ĭ�Ϲ���ʱ������Ĭ���βλ������⣬ֱ������
	// "MAX","MAX",times timetmp1,INF,times timetmp2,INF��ʶ���һ��type����֪���Ƿ������޴�ֵ
	// ��ʱ�����Ĺ������൱���ڽӾ����е����޴���һ�����������
	void set(string, string, times, double, times, double);

	vehicle& operator =(const vehicle& v);//���ں���Ҫ�õ���Ȳ�����������������
	
};


#endif

