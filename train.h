#pragma once
#ifndef _TRAIN_H
#define _TRAIN_H

#include<iostream>
#include"time.h"
#include<string>

using namespace std;

//train�ı�����ͼ�бߵ���Ϣ�����бȽϵ�ʱ��Ƚ�consume��money
class train :public time{ //train��time�̳� 
private: 
	string type = "train";
	string name;
	time time1;
	time consume;
	time time2;
	int money;
public:
	train();//Ĭ�Ϲ���	
	train(string x1,time t2,time t3,time t4,int x5);//�ڹ����ʱ��Ҫע�⵽ʱ���ȡ����Ҫ�ȹ���3��time��
	void set(string, time, time, time, int);
};


#endif
