#pragma once
#ifndef _TRAIN_H
#define _TRAIN_H

#include<iostream>
#include"times.h"
#include<string>

using namespace std;

//train�ı�����ͼ�бߵ���Ϣ�����бȽϵ�ʱ��Ƚ�consume��money
class train :public times{ //train��time�̳� 
private: 
	string type = "train";
	string name;
	times time1;
	times consume;
	times time2;
	int money;
public:
	train();//Ĭ�Ϲ���	
	train(string x1,times t2,times t3,times t4,int x5);//�ڹ����ʱ��Ҫע�⵽ʱ���ȡ����Ҫ�ȹ���3��time��
	void set(string, times, times, times, int);
};


#endif
