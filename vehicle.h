#pragma once
#ifndef _VEHICLE_H
#define _VEHICLE_H

#include<iostream>
#include"times.h"
#include<string>

using namespace std;

//vehicle的本质是图中边的信息，其中比较的时候比较consume和money
class vehicle :public times { //train对time继承 
public:
	//这里我们发现train和fly的形式其实差不多一致，所以我们用一个统一的形式，在文件中，此变量的形式也只会有
	//train和fly两种，这样处理也是为了便于建立邻接矩阵（统一化）
	string type;
	string name;
	times time1;
	double consume;//到时候需要调用时间转换函数，耗时大致形式是1.35这样
	times time2;
	double money;

public:
	//若调用默认构造函数，此时建立的工具类当于邻接矩阵中的0，即自身与自身没有距离
	vehicle();//默认构造	
	vehicle(string x1, string x2, times t3, double t4, times t5, double x6);//在构造的时候要注意到时候读取数据要先构造3个time类
	//注意，若调用默认形参的构造方式，但有默认构造时，调用默认形参会有问题，直接输入
	// "MAX","MAX",times timetmp1,INF,times timetmp2,INF，识别第一个type即可知道是否是无限大值
	// 此时建立的工具类相当于邻接矩阵中的无限大这一概念，即不连接
	void set(string, string, times, double, times, double);

	vehicle& operator =(const vehicle& v);//由于后面要用到相等操作，所以这里重载
	
};


#endif

