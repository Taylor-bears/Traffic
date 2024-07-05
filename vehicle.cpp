#pragma once
#include "vehicle.h"
#include"time.h"
#include <iostream>
#include<string>

using namespace std;

vehicle::vehicle() {
	type = "";
	name = "";
	time1; //Ä¬ÈÏ¹¹Ôì
	consume;
	time2;
	money = 0;
}

vehicle::vehicle(string x1, string x2, times t3, double t4, times t5, int x6) {
	type = x1;
	name = x2;
	time1 = t3;
	consume = t4;
	time2 = t5;
	money = x6;
}

void vehicle::set(string x1, string x2, times t3, double t4, times t5, int x6) {
	type = x1;
	name = x2;
	time1 = t3;
	consume = t4;
	time2 = t5;
	money = x6;
}