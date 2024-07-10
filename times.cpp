#pragma once
#include "times.h"
#include <iostream>
#include<fstream>
#include<string>

times::times() {	
	day = 0;
	hour = 0;
	minute = 0;
}

times::times(int x2, int x3, int x4) {
	day = x2;
	hour = x3;
	minute = x4;
}

void times::set(int x2, int x3, int x4) {
	day = x2;
	hour = x3;
	minute = x4;
}

times& times::operator =(const times& t) {
	this->day = t.day;
	this->hour = t.hour;
	this->minute = t.minute;
	return *this;
}

bool times::operator<(const times& t) const {
	if (day < t.day) return true;
	if (day > t.day) return false;
	if (hour < t.hour) return true;
	if (hour > t.hour) return false;
	return minute < t.minute;
}

void times::addMinutes(int minutes) {
	this->minute += minutes;
	this->hour += this->minute / 60;
	this->minute %= 60;
	this->day += this->hour / 24;
	this->hour %= 24;
}

times times::operator+(const times& t) const {
	int totalMinutes = minute + t.minute;
	int totalHours = hour + t.hour + totalMinutes / 60; // ���ϴӷ��ӽ�λ��Сʱ��
	totalMinutes %= 60; // ����ʣ��ķ�����
	int totalDays = day + t.day + totalHours / 24; // ���ϴ�Сʱ��λ������
	totalHours %= 24; // ����ʣ���Сʱ��

	return times(totalDays, totalHours, totalMinutes);
}

bool times::operator>(const times& t) const {
	if (day > t.day) return true;
	if (day < t.day) return false;
	if (hour > t.hour) return true;
	if (hour < t.hour) return false;
	return minute > t.minute;
}

bool times::operator==(const times& other) const {
	return (day == other.day && hour == other.hour && minute == other.minute);
}