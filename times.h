#pragma once
#ifndef _TIME_H
#define _TIME_H

//ע��ʱ������࣬��������time����Ҫ��times����ΪC++��׼������time����ʹ�ú�����������ͳ���
class times {
public:
	int day;
	int hour;
	int minute;

public:
	times();//Ĭ�Ϲ���	
	times(int, int, int);
	void set(int, int, int);
};

#endif
