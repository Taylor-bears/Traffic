#pragma once
#ifndef _VEHICLE_H
#define _VEHICLE_H

#include<iostream>
#include"time.h"
#include<string>

using namespace std;

//vehicle的本质是图中边的信息，其中比较的时候比较consume和money
class vehicle :public time { //train对time继承 
private:
	//这里我们发现train和fly的形式其实差不多一致，所以我们用一个统一的形式，在文件中，此变量的形式也只会有
	//train和fly两种，这样处理也是为了便于建立邻接矩阵（统一化）
	string type;
	string name;
	time time1;
	time consume;
	time time2;
	int money;
public:
	vehicle();//默认构造	
	vehicle(string x1, string x2, time t3, time t4, time t5, int x6);//在构造的时候要注意到时候读取数据要先构造3个time类
	void set(string, string, time, time, time, int);
};


#endif

