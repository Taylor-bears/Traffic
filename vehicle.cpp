#pragma once
#include "vehicle.h"
#include"time.h"
#include <iostream>
#include<string>

using namespace std;

vehicle::vehicle() {
	type = "";
	name = "";
	time1; //Ĭ�Ϲ���
	consume=0.0;
	time2;
	money = 0.0;
}

vehicle::vehicle(string x1, string x2, times t3, double t4, times t5, double x6) {
	type = x1;
	name = x2;
	time1 = t3;
	consume = t4;
	time2 = t5;
	money = x6;
}

void vehicle::set(string x1, string x2, times t3, double t4, times t5, double x6) {
	type = x1;
	name = x2;
	time1 = t3;
	consume = t4;
	time2 = t5;
	money = x6;
}

vehicle& vehicle::operator =(const vehicle& v) {
	type = v.type;
	name = v.name;
	time1 = v.time1;
	consume = v.consume;
	time2 = v.time2;
	money = v.money;
}