#pragma once
#ifndef _TIME_H
#define _TIME_H

class time {
private:	
	int day;
	int hour;
	int minute;
public:
	time();//Ĭ�Ϲ���	
	time(int,int,int);
	void set(int, int, int);
};

#endif
