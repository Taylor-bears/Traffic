#pragma once
#include "time.h"
#include <iostream>
#include<fstream>
#include<string>

time::time() {
	month = 0;
	day = 0;
	hour = 0;
	minute = 0;
}

time::time(int x1, int x2, int x3, int x4) {
	month = x1;
	day = x2;
	hour = x3;
	minute = x4;
}

void time::set(int x1, int x2, int x3, int x4) {
	month = x1;
	day = x2;
	hour = x3;
	minute = x4;
}

//可能还要设计time相加计算算法