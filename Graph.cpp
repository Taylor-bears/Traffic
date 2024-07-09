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
vehicle graph::getmin(const vector<vehicle>& ve, const times& current_time, const string& 
	required_vehicle_type, const string& last_vehicle_name) {
	double min = INF;
	int minnum = -1;
	int wait_hours = 0;

	for (int i = 0; i < ve.size(); i++) {
		// 如果指定了交通工具类型，并且当前交通工具类型与要求的不符，则跳过
		if (!required_vehicle_type.empty() && ve[i].type != required_vehicle_type) {
			continue;
		}

		// 根据上一次的交通方式确定等待时间
		if (last_vehicle_name.empty()) {
			wait_hours = 0; // 如果没有上一次交通方式，等待时间为0
		}
		else if (!last_vehicle_name.empty() && ve[i].name != last_vehicle_name) {
			wait_hours = (ve[i].type == "train") ? 1 : 2; // 根据当前交通方式确定等待时间
		}
		else if (!last_vehicle_name.empty() && ve[i].name == last_vehicle_name) {
			wait_hours = 0; // 同一交通工具不等待
		}

		// 计算考虑等待时间后的出发时间
		times adjusted_departure_time = current_time;
		adjusted_departure_time.addMinutes(wait_hours * 60); // 假设addMinutes是一个添加分钟的方法

		// 确保出发时间晚于上一次到达时间加上等待时间
		if (timecheck(adjusted_departure_time, ve[i].time1, 0) && ve[i].consume < min) {
			minnum = i;
			min = ve[i].consume;
		}
	}

	if (min == INF) {
		times timetmp1, timetmp2;
		return vehicle("MAX", "MAX", timetmp1, INF, timetmp2, INF); // 返回一个表示无效结果的特殊vehicle对象
	}
	return ve[minnum];
}


//通过此算法可得到最小时间路径（游客接受中转）
void graph::Time_Dijkstra(int v, int n, times current_time) {
	// 分别为火车和飞机初始化
	vector<vector<times>> dist(2, vector<times>(number, times(INF, INF, INF))); // 初始化所有为无穷大
	vector<vector<int>> path(2, vector<int>(number, -1)); // 初始化路径
	vector<bool> S(number, false); // 标记数组，false表示未被访问
	vector<vector<times>> arrival_time(2, vector<times>(number, times(INF, INF, INF))); // 记录到每个顶点的到达时间
	vector<vector<string>> last_vehicle_type(2, vector<string>(number)); // 记录到每个顶点最后乘坐的交通工具类型
	vector<vector<string>> last_vehicle_name(2, vector<string>(number));

	// 初始化，分别对火车和飞机进行
	for (int mode = 0; mode < 2; ++mode) { // mode: 0为火车, 1为飞机
		string initialType = mode == 0 ? "train" : "fly";
		dist[mode][v] = times(0, 0, 0); // 自己到自己为0
		arrival_time[mode][v] = current_time; // 出发点的到达时间就是当前时间

		// 更新初始点到各顶点的最短路径
		for (int i = 0; i < number; i++) {
			if (!edges[v][i].empty()) {
				vehicle minVehicle = getmin(edges[v][i], current_time, initialType, "");
				if (minVehicle.type == initialType) {
					dist[mode][i] = minVehicle.time2;
					path[mode][i] = v;
					arrival_time[mode][i] = minVehicle.time2;
					last_vehicle_type[mode][i] = minVehicle.type;
					last_vehicle_name[mode][i] = minVehicle.name;
				}
			}
		}
	}

	// 对每种模式（火车、飞机）执行Dijkstra算法
	for (int mode = 0; mode < 2; ++mode) {
		fill(S.begin(), S.end(), false); // 重置S数组

		for (int count = 0; count < number - 1; count++) {
			// 寻找当前未处理的最小dist顶点
			times minTime(INF, INF, INF);
			int u = -1;
			for (int j = 0; j < number; j++) {
				if (!S[j] && dist[mode][j] < minTime) { // 使用重载的<运算符或者自定义比较函数
					u = j;
					minTime = dist[mode][j];
				}
			}
			if (u == -1) break; // 如果没有找到，跳出循环

			S[u] = true;

			// 更新dist数组
			for (int j = 0; j < number; j++) {
				if (!S[j] && !edges[u][j].empty()) {
					vehicle minVehicle = getmin(edges[u][j], arrival_time[mode][u], last_vehicle_type[mode][u], last_vehicle_name[mode][u]);
					if (minVehicle.type == last_vehicle_type[mode][u]) { // 保持交通工具不变
						// 计算到达时间，包括中转等待时间
						times new_arrival_time = minVehicle.time2;
						if (arrival_time[mode][u] + minVehicle.time1 < new_arrival_time) {
							dist[mode][j] = new_arrival_time;
							path[mode][j] = u;
							arrival_time[mode][j] = new_arrival_time;
							last_vehicle_type[mode][j] = minVehicle.type;
							last_vehicle_name[mode][j] = minVehicle.name;
						}
					}
				}
			}
		}
	}

	// 比较火车和飞机的最优解
	if (dist[0][n] < dist[1][n]) {
		// 火车更快
		dispaly(dist[0], path[0], S, v, n, arrival_time[0], last_vehicle_type[0], last_vehicle_name[0]);
	}
	else {
		// 飞机更快或相等
		dispaly(dist[1], path[1], S, v, n, arrival_time[1], last_vehicle_type[1], last_vehicle_name[1]);
	}
}


void graph::dispaly(vector<times> dist, vector<int> path, vector<bool> S, int v, int n,
	vector<times> arrival_time, vector<string> vehicle_type, vector<string> vehicle_name) {
	if (!S[n]) { // 如果从v到n不存在路径
		cout << "没有找到从出发地到目的地的路径。" << endl;
		return;
	}

	cout << "从出发地到目的地的最快方式如下：" << endl;
	vector<int> apath;
	int current = n;
	while (current != v) {
		apath.push_back(current);
		current = path[current];
	}
	apath.push_back(v); // 添加起始点

	for (int i = apath.size() - 2; i >= 0; i--) { // 注意这里的遍历方式和索引
		int from = apath[i + 1], to = apath[i];
		vehicle& v = edges[from][to][0]; // 假设每个城市间只有一条最快路径
		cout << "从" << mycity.name[from] << "出发, 到" << mycity.name[to] << ", 类型："
			<< v.type << ", 编号：" << v.name << ", 在"
			<< v.time1.day << "号" << v.time1.hour << "点" << v.time1.minute << "分出发，耗时"
			<< v.consume << "小时，预估" << v.time2.day << "号" << v.time2.hour << "点" << v.time2.minute << "分到达，费用："
			<< v.money << "元" << endl;
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
	cout << "请输入出发时间（日 时 分，例如 6 15 30表示本月的6号15点30分）：" << endl;
	cin >> day >> hour >> minute;

	// 创建一个times对象来表示用户输入的出发时间
	times currentTime(day, hour, minute);

	// 调用Time_Dijkstra函数计算最优路径
	Time_Dijkstra(start, destination, currentTime); // 假设这个函数接受times对象作为参数
}


//调试用
void graph::show() {
	for (int i = 0; i < number; i++) {
		cout << mycity.name[i]<<endl;
	}
	for (int i = 0; i < number; i++) {
		for (int j = 0; j < number; j++) {
			for(auto k:edges[i][j]){
				cout << mycity.name[i] << " " << mycity.name[j] << " " << k.type << " " << k.name << " " << k.time1.day << ":" << k.time1.hour << ":" << k.time1.minute << " "
					<< k.consume << " " << k.time2.day << ":" << k.time2.hour << ":" << k.time2.minute << endl;
			}
		}
	}
}


//调试用
void graph::tiaoshi() {
	for (int i = 0; i < number; i++) {
		for (int j = 0; j < number; j++) {
			for (auto k : edges[i][j]) {
				if (!timecheck(k.time1, k.time2, 0)) {
					cout << mycity.name[i] << " " << mycity.name[j] << " " << k.type << " " << k.name << " " << k.time1.day << ":" << k.time1.hour << ":" << k.time1.minute << " "
						<< k.consume << k.time2.day << ":" << k.time2.hour << ":" << k.time2.minute << endl;
				}
			}
		}
	}
}