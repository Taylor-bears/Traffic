#pragma once
#include "train.h"
#include"time.h"
#include <iostream>
#include<string>

using namespace std;

train::train() {
	name="";
	time; //Ä¬ÈÏ¹¹Ôì
	consume;
	time2;
	money=0;
}

train::train(string x1, time t2, time t3, time t4, int x5) {
	name = x1;
	time1 = t2;
	consume = t3;
	time2 = t4;
	money = x5;
}

void train::set(string x1, time t2, time t3, time t4, int x5) {
	name = x1;
	time1 = t2;
	consume = t3;
	time2 = t4;
	money = x5;
}