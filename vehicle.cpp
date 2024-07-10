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
	this->type = v.type;
	this->name = v.name;
	this->time1 = v.time1;
	this->consume = v.consume;
	this->time2 = v.time2;
	this->money = v.money;
	return *this;
}

bool vehicle::operator==(const vehicle& other) const {
	return (type == other.type && name == other.name && time1 == other.time1 &&
		consume == other.consume && time2 == other.time2 && money == other.money);
}