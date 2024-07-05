#pragma once
#ifndef _FLY_H
#define _FLY_H

#include<iostream>
#include"times.h"
#include<string>

using namespace std;

//fly的本质也是图中边的信息，其中比较的时候比较consume和money
class fly :public times { //train对time继承 
private:
	string type = "fly";
	string name;
	times time1;
	times consume;
	times time2;
	int money;
public:
	fly();//默认构造	
	fly(string x1, times t2, times t3, times t4, int x5);//在构造的时候要注意到时候读取数据要先构造3个time类
	void set(string, times, times, times, int);
};


#endif