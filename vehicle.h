#pragma once
#ifndef _VEHICLE_H
#define _VEHICLE_H

#include<iostream>
#include"time.h"
#include<string>

using namespace std;

//vehicle�ı�����ͼ�бߵ���Ϣ�����бȽϵ�ʱ��Ƚ�consume��money
class vehicle :public time { //train��time�̳� 
private:
	//�������Ƿ���train��fly����ʽ��ʵ���һ�£�����������һ��ͳһ����ʽ�����ļ��У��˱�������ʽҲֻ����
	//train��fly���֣���������Ҳ��Ϊ�˱��ڽ����ڽӾ���ͳһ����
	string type;
	string name;
	time time1;
	time consume;
	time time2;
	int money;
public:
	vehicle();//Ĭ�Ϲ���	
	vehicle(string x1, string x2, time t3, time t4, time t5, int x6);//�ڹ����ʱ��Ҫע�⵽ʱ���ȡ����Ҫ�ȹ���3��time��
	void set(string, string, time, time, time, int);
};


#endif

