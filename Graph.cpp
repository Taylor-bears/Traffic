#pragma once
#include "graph.h"
#include <iostream>
#include<string>
#include<fstream>
#include<vector>
const int INF = 0x3f3f3f3f;

using namespace std;

//带参构造函数
//在主函数中，需要使用"city.txt"和""初始化
graph::graph(const string& file_path1, const string& file_path2) {
	mycity = city(file_path1);//这里需要赋值
	number = mycity.name.size();
	edges.resize(number, vector<vector<vehicle>>(number));//此时建立的三维数组，前两维的长度已由城市数量确定

	//下面让每一个城市对应一个编号，便于后面矩阵中每个数字
	for (int i = 0; i < number; i++) {
		this->traffic_map[mycity.name[i]] = i;
	}

	//下面建立图（需要读取交通工具文件），也是本程序最重要的储存部分
	ifstream input("vehicle.txt");
	char nosense;//用于保存无用的符号
	string city_name1;
	string city_name2;
	//下面是vehicle的五个数据
	string type;
	string identifier;
	times mytime1;
	double consume;
	times mytime2;
	double money;

	while (input >> nosense) { //读取（
		string day1;
		string hour1;
		string minute1;
		string hour_past;
		string minute_past;
		string day2;
		string hour2;
		string minute2;
		string cost;
		if (nosense == '(') {
			getline(input, city_name1, ',');//读取 Beijing               
			getline(input, city_name2, ')');//读取 Wuhan    
			int num1 = traffic_map[city_name1];
			int num2 = traffic_map[city_name2];
			input >> nosense;//读取","
			getline(input, type, ',');//1作为类型存储
			getline(input, identifier, ',');//2作为编号存储
			getline(input, day1, '.');
			getline(input, hour1, ':');
			getline(input, minute1, ',');
			mytime1 = times(stoi(day1), stoi(hour1), stoi(minute1));//3作为时间1存储
			getline(input, hour_past, ':');
			getline(input, minute_past, ',');
			consume = time_transfer(stoi(hour_past), stoi(minute_past));//4作为耗时需要保存
			getline(input, day2, '.');
			getline(input, hour2, ':');
			getline(input, minute2, ',');
			mytime2 = times(stoi(day2), stoi(hour2), stoi(minute2));//5作为时间1存储
			getline(input, cost);
			money = stod(cost);//6作为费用存储
			vehicle myvehicle(type, identifier, mytime1, consume, mytime2, money);//已经读取好了一个工具类
			//将工具读入边的向量中，即邻接矩阵的点上
			edges[num1][num2].push_back(myvehicle);//num1和num2是两个城市的编号（注意这里是有向图，并不对称）
		}
	}
	//通过以上操作只是建立了有连通处两地的连接，
	//图中还要包含0和∞两种特殊情况
	for (int i = 0; i < number; i++) {
		for (int j = 0; j < number; j++) {
			if (edges[i][j].empty()) {//如果为空，则
				if (i == j) {
					vehicle myvehicle;
					edges[i][j].push_back(myvehicle);
				}
				//此时调用默认构造函数，每个值都为0，通过识别""空串(type)即可知道
				else {
					times timetmp1;//调用默认构造，内部成员都为0
					times timetmp2;
					edges[i][j].push_back(vehicle("MAX", "MAX", timetmp1, INF, timetmp2, INF));
					//此时建立的是无穷大边值，通过识别"MAX"(type)即可知道
				}
			}
		}
	}
	/*测试用例：cout << number;
	测试用例：for (int i = 0; i < number; i++) {
		for (int j = 0; j < number; j++) {
			cout << edges[i][j].size()<<endl;
		}
	}
}*/
}

//默认构造函数
graph::graph() {
	//无
}

//所有的方案可行的前提都是他的时间要比给定的晚，而不能早
// 比较time1加上等待时间是否小于等于time2，这里加上比较时长，是为了便于后面处理中转站需要等待的情况
bool graph::timecheck(times time1, times time2, int wait_hours) {
	// 首先将等待时间加到time1上
	time1.hour += wait_hours;
	time1.day += time1.hour / 24; // 超过24小时则增加一天
	time1.hour %= 24; // 调整小时数

	if (time1.day < time2.day) {
		return true;
	}
	else if (time1.day == time2.day) {
		if (time1.hour < time2.hour) {
			return true;
		}
		else if (time1.hour == time2.hour) {
			return time1.minute <= time2.minute;
		}
	}
	return false;
}

//时间转换函数的定义
double graph::time_transfer(int hour, int minute)
{
	double a;
	a = hour + minute / 60.0;
	a = static_cast<int>(a * 10 + 0.5);
	return a / 10.0;
}

//可以得到邻接矩阵某点向量时间的最小值对应的交通方式
//同样的算某两地之间的最小方式，是需要考虑上一次的交通方式，因为中转的等待时间有要求且不同
vehicle graph::getmin(vector<vehicle> ve, times current_time, string last_vehicle_type, string last_vehicle_name) {//最近一次的交通工具
	double min = INF; // 最小费用初始化为无穷大
	int minnum = -1; // 最小编号
	int wait_hours; 
	
	// 火车等待1小时，飞机等待2小时，其他情况不等待（如果是起始地，则没有上一工具，故等待时长为0）

	for (int i = 0; i < ve.size(); i++) {
		if (last_vehicle_name == "") {
			wait_hours = 0;//第一次的方式不存在上一方式，所以上一交通方式为0
		}
		else if (last_vehicle_name != ""&& ve[i].name != last_vehicle_name ) { //第一次列车没有上一车次说法
			wait_hours = (last_vehicle_type == "train") ? 1 : 2 ;//是飞机则为2小时
		}
		else if (last_vehicle_name != "" && ve[i].name == last_vehicle_name) {
			wait_hours = 0;
		}
		//current_times是上一次的到达时间
		if (timecheck(current_time, ve[i].time1, wait_hours) && ve[i].consume < min) { 
			// 如果该方式的出发时间满足条件并且耗时更小
			minnum = i;
			min = ve[i].consume;
		}
	}

	if (min == INF) { // 如果所有的时间都不符合，则返回无限大交通类
		times timetmp1, timetmp2;
		return vehicle("MAX", "MAX", timetmp1, INF, timetmp2, INF);
	}
	return ve[minnum]; // 返回最小交通方式
}

//通过此算法可得到最小时间路径（游客接受中转）
void graph::Time_Dijkstra(int v, int n, times current_time) {
	vector<vehicle> dist(number);//这里变为times型，是为了方便找到它的除了耗时其他的信息
	vector<int> path(number);
	vector<int> S(number);

	vector<times> arrival_time(number);
	vector<string> vehicle_type(number);//第i次的交通类型
	vector<string> vehicle_name(number);//第i次的交通名称

	for (int i = 0; i < number; i++) {			 
			dist[i] = getmin(edges[v][i], current_time, "", "");//此时wait_hours 为0
			S[i] = 0;
			if (dist[i].consume != 0 && dist[i].consume < INF)
				path[i] = v;
			else
				path[i] = -1;
	}
	S[v] = 1;
	vehicle mindis;//每一次的最小情况
	int u = -1;
	for (int i = 0; i < number - 1; i++) {
		mindis.consume = INF;
		for (int j = 0; j < number; j++) 
			if (S[j] == 0 && dist[j].consume < mindis.consume) {
				u = j;
				mindis = dist[j];
			}
		S[u] = 1; //此时选出的最小点不可更改
		//此时需要将最小的信息添加到上一信息当中，因为要对下一次的出发时间进行筛选
		arrival_time.push_back(mindis.time2);
		vehicle_type.push_back(mindis.type);
		vehicle_name.push_back(mindis.name);
		//修改不在S中顶点的距离

	}
}


void graph::dispaly(vector<double> dist, vector<int> path, vector<bool> S, int v, int n, vector<times> arrival_time, vector<string> last_vehicle_type) {
	if (S[n]) { // 如果从v到n存在路径
		cout << "从出发地到目的地的最快方式如下：" << endl;
		vector<int> apath;
		int current = n;
		//回顾狄克斯特拉算法寻找路径的过程，他是通过n点找到他的前一个点，再找他前面的，直到找到出发点
		while (current != v) { 
			apath.push_back(current);
			current = path[current];
		}
		apath.push_back(v); // 添加起始点

		//因为apath里面是倒着找的，那么倒着输出就是从原点处输出
		// 反向遍历apath，输出路径
		for (int i = apath.size() - 1; i > 0; i--) {
			int from = apath[i], to = apath[i - 1];
			// 假设每个城市间只有一条最快路径，因此我们只取第一条
			vehicle& v = edges[from][to][0];
			cout << "从" << mycity.name[from] << "出发,到" << mycity.name[to] << ",类型："
				<< v.type << ",编号：" << v.name << ",在"
				<< v.time1.day << "号" << v.time1.hour << "时" << v.time1.minute << "分出发，耗时"
				<< v.consume << "小时，预估" << v.time2.day << "号" << v.time2.hour << "时" << v.time2.minute << "分到达，费用："
				<< v.money << "元" << endl;
		}

		// 最后显示到达目的地的时间
		cout << "预计到达时间：" << arrival_time[n].day << "号 "
			<< arrival_time[n].hour << "时 " << arrival_time[n].minute << "分" << endl;
	}
	else {
		cout << "没有找到从出发地到目的地的路径。" << endl;
	}
}


//最优方案定义
void graph::optimal() {
	string city_name1, city_name2;
	cout << "请输入您的出发地与目的地（地点的格式：北京 Beijing）：" << endl;
	cout << "请输入出发地：" << endl;
	cin >> city_name1;
	cout << "请输入目的地：" << endl;
	cin >> city_name2;

	if (traffic_map.find(city_name1) == traffic_map.end() || traffic_map.find(city_name2) == traffic_map.end()) {
		cout << "输入的城市不存在，请重新输入。" << endl;
		return;
	}

	int start = traffic_map[city_name1];
	int destination = traffic_map[city_name2];

	// 让用户输入出发时间（只包括日、时、分）
	int day, hour, minute;
	cout << "请输入出发时间（日 时 分，例如 6 15 30表示本月的6日15点30分）：" << endl;
	cin >> day >> hour >> minute;

	// 创建一个times对象来表示用户输入的出发时间
	times currentTime(day, hour, minute);

	// 调用Time_Dijkstra函数计算最优路径
	Time_Dijkstra(start, destination, currentTime); // 假设这个函数接受times对象作为参数
}