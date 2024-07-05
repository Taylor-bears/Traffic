#pragma once
#include "fly.h"
#include"time.h"
#include <iostream>
#include<string>

using namespace std;

fly::fly() {
	name = "";
	time; //Ä¬ÈÏ¹¹Ôì
	consume;
	time2;
	money = 0;
}

fly::fly(string x1, times t2, times t3, times t4, int x5) {
	name = x1;
	time1 = t2;
	consume = t3;
	time2 = t4;
	money = x5;
}

void fly::set(string x1, times t2, times t3, times t4, int x5) {
	name = x1;
	time1 = t2;
	consume = t3;
	time2 = t4;
	money = x5;
}