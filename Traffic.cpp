#include<iostream>
#include<string>
#include<sstream>
#include"city.h"
#include"vehicle.h"
#include"time.h"
#include"graph.h"

using namespace std;

int main() {
	graph mygraph("city.txt","vehicle.txt");
	mygraph.optimal();
	return 0;
}

