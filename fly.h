#pragma once
#ifndef _FLY_H
#define _FLY_H

#include<iostream>
#include"time.h"
#include<string>

using namespace std;

//fly�ı���Ҳ��ͼ�бߵ���Ϣ�����бȽϵ�ʱ��Ƚ�consume��money
class fly :public time { //train��time�̳� 
private:
	string type = "fly";
	string name;
	time time1;
	time consume;
	time time2;
	int money;
public:
	fly();//Ĭ�Ϲ���	
	fly(string x1, time t2, time t3, time t4, int x5);//�ڹ����ʱ��Ҫע�⵽ʱ���ȡ����Ҫ�ȹ���3��time��
	void set(string, time, time, time, int);
};


#endif