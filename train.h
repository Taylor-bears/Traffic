#pragma once
#ifndef _TRAIN_H
#define _TRAIN_H

#include<iostream>
#include"time.h"
#include<string>

using namespace std;

//train的本质是图中边的信息，其中比较的时候比较consume和money
class train :public time{ //train对time继承 
private: 
	string type = "train";
	string name;
	time time1;
	time consume;
	time time2;
	int money;
public:
	train();//默认构造	
	train(string x1,time t2,time t3,time t4,int x5);//在构造的时候要注意到时候读取数据要先构造3个time类
	void set(string, time, time, time, int);
};


#endif
