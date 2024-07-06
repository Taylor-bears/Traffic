#pragma once
#ifndef _TIME_H
#define _TIME_H

//注意时间这个类，不可以用time，需要用times，因为C++标准库中有time，会使得后面用这个类型出错
class times {
public:
	int day;
	int hour;
	int minute;

public:
	times();//默认构造	
	times(int, int, int);
	void set(int, int, int);
};

#endif
