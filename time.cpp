#pragma once
#include "time.h"
#include <iostream>
#include<fstream>
#include<string>

time::time() {	
	day = 0;
	hour = 0;
	minute = 0;
}

time::time(int x2, int x3, int x4) {
	day = x2;
	hour = x3;
	minute = x4;
}

void time::set(int x2, int x3, int x4) {
	day = x2;
	hour = x3;
	minute = x4;
}

//���ܻ�Ҫ���time��Ӽ����㷨