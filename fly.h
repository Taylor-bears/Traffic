#pragma once
#ifndef _FLY_H
#define _FLY_H

#include<iostream>
#include"times.h"
#include<string>

using namespace std;

//fly�ı���Ҳ��ͼ�бߵ���Ϣ�����бȽϵ�ʱ��Ƚ�consume��money
class fly :public times { //train��time�̳� 
private:
	string type = "fly";
	string name;
	times time1;
	times consume;
	times time2;
	int money;
public:
	fly();//Ĭ�Ϲ���	
	fly(string x1, times t2, times t3, times t4, int x5);//�ڹ����ʱ��Ҫע�⵽ʱ���ȡ����Ҫ�ȹ���3��time��
	void set(string, times, times, times, int);
};


#endif