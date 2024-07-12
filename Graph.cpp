#pragma once
#include "graph.h"
#include <iostream>
#include<string>
#include<fstream>
#include<vector>
#include<stack>
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
	number = 0;
}


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


//时间模块
//(不允许中间变换交通工具)
//可以得到邻接矩阵某点向量时间的最小值对应的交通方式
//同样的算某两地之间的最小方式，是需要考虑上一次的交通方式，因为中转的等待时间有要求且不同
vehicle graph::getmin(vector<vehicle>& ve, times current_time, string type, string last_vehicle_name) {
	times minTime = times(INF, INF, INF);
	vehicle minVehicle;
	for (auto& v : ve) {
		if (v.type != type) continue; // 确保交通工具类型匹配

		times adjusted_time;
		adjusted_time = current_time; // 调整后的到达时间

		// 如果有上一次的交通工具，并且名称不同，则根据类型添加等待时间
		if (!last_vehicle_name.empty() && v.name != last_vehicle_name) {
			int wait_time = (type == "fly") ? 120 : 60; // 飞机换乘等待2小时，火车换乘等待1小时(换算为分钟)
			adjusted_time.addMinutes(wait_time);
		}

		// 如果当前时间晚于调整后的出发时间，跳过这个交通工具
		if ( adjusted_time > v.time1) continue;

		// 计算到达时间，如果这是目前为止找到的最快路径，更新minTime和minVehicle
		times k;
		k = v.time2;
		if (k < minTime) {
			minTime = k;
			minVehicle = v;
		}
	}
	return minVehicle;
}


//通过此算法可得到最小时间路径（游客接受中转）
void graph::Time_Dijkstra(int v, int n, times current_time, string type) {
	//原狄克斯特拉算法部分，根据需求我改变了类型
	vector<bool> visited(number, false);
	vector<times> dist(number, times(INF, INF, INF));
	vector<PathStep> path(number); // 使用PathStep替换之前的prev数组
	dist[v] = current_time;

	for (int i = 0; i < number; ++i) {
		int u = -1;
		times minTime(INF, INF, INF);
		for (int j = 0; j < number; j++) {
			if (!visited[j] && dist[j] < minTime) {
				u = j;
				minTime = dist[j];
			}
		}

		if (u == -1) break;
		visited[u] = true;

		for (int j = 0; j < edges[u].size(); j++) {
			for (auto& v : edges[u][j]) {
				if (v.type != type) continue;
				vehicle minVeh = getmin(edges[u][j], dist[u], type, path[u].veh.name);
				if (minVeh.name.empty()) continue; // 如果没有合适的交通工具，跳过

				times arrivalTime;
			    arrivalTime = minVeh.time2;
				if (dist[u] < arrivalTime && arrivalTime < dist[j]) {
					dist[j] = arrivalTime;
					path[j] = PathStep(u, minVeh); // 存储前一个节点和使用的交通工具信息
				}
			}
		}
	}

	display(dist, path, visited, v, n, type);
}


//允许变换交通工具（时间模块）
vehicle graph::getmin2(vector<vehicle>& ve, times current_time, string last_vehicle_type, string last_vehicle_name) {
	times minTime = times(INF, INF, INF);
	vehicle minVehicle;
	//这里不跳过类型不同的了，但仍然需要记录类型，因为类型决定了中转的时间
	for (auto& v : ve) {
		times adjusted_time;
		adjusted_time = current_time; // 调整后的到达时间

		// 如果有上一次的交通工具，并且名称不同，则根据类型添加等待时间
		if (!last_vehicle_name.empty() && v.name != last_vehicle_name) {
			int wait_time = (last_vehicle_type == "fly") ? 120 : 60; // 飞机换乘等待2小时，火车换乘等待1小时(换算为分钟)
			adjusted_time.addMinutes(wait_time);
		}

		// 如果当前时间晚于调整后的出发时间，跳过这个交通工具
		if (adjusted_time > v.time1) continue;

		// 计算到达时间，如果这是目前为止找到的最快路径，更新minTime和minVehicle
		times k;
		k = v.time2;
		if (k < minTime) {
			minTime = k;
			minVehicle = v;
		}
	}
	return minVehicle;
}


void graph::Time_Dijkstra2(int v, int n, times current_time) {
	vector<bool> visited(number, false);
	vector<times> dist(number, times(INF, INF, INF));
	vector<PathStep> path(number); // 使用PathStep替换之前的prev数组
	dist[v] = current_time;

	for (int i = 0; i < number; i++) {
		int u = -1;
		times minTime(INF, INF, INF);
		for (int j = 0; j < number; j++) {
			if (!visited[j] && dist[j] < minTime) {
				u = j;
				minTime = dist[j];
			}
		}

		if (u == -1) break;
		visited[u] = true;

		for (int j = 0; j < edges[u].size(); ++j) {
			for (auto& v : edges[u][j]) {
				vehicle minVeh = getmin2(edges[u][j], dist[u], path[u].veh.type, path[u].veh.name);
				if (minVeh.name.empty()) continue; // 如果没有合适的交通工具，跳过

				times arrivalTime;
				arrivalTime = minVeh.time2;
				if (dist[u] < arrivalTime && arrivalTime < dist[j]) {
					dist[j] = arrivalTime;
					path[j] = PathStep(u, minVeh); // 存储前一个节点和使用的交通工具信息
				}
			}
		}
	}

	display2(dist, path, visited, v, n);
}


//直达（时间最短）
void graph::DFS(int v, int end, const string& type, const string& vehicleName, vector<PathStep3>& path,
	times& current_time, vector<PathStep3>& bestPath, times& bestTime) {
	if (v == end) { // 到达目的地
		if (current_time < bestTime || bestTime.day == INF) {
			bestTime = current_time;// 更新最短时间
			bestPath = path;// 更新最优路径
		}
		return;
	}

	for (int j = 0; j < edges[v].size(); j++) {
		for (auto& veh : edges[v][j]) {
			if (veh.type != type) continue; // 交通工具类型不匹配
			// 确保交通工具名称匹配或是路径的第一步

			if (!path.empty() && vehicleName != "" && veh.name != vehicleName) continue;

			if (current_time < veh.time1 || path.empty()) {
				times arrivalTime;
				arrivalTime = veh.time2;
				path.push_back(PathStep3(v, j, veh));
				string nextVehicleName = vehicleName == "" ? veh.name : vehicleName;
				DFS(j, end, type, nextVehicleName, path, arrivalTime, bestPath, bestTime);
				path.pop_back();
			}
		}
	}
}



//这里是在飞机和列车中，进行了挑选，到时候调整一下使之可以分别显示两个的
void graph::findBestPath(int start, int end, const times& preset_time, const string& type) {
	vector<PathStep3> bestPath;
	times bestTime(INF, INF, INF); // 初始化最短时间为无穷大

	vector<PathStep3> path;
	times current_time = preset_time;
	// 调用DFS时，vehicleName参数为空字符串，表示还没有选择交通工具
	DFS(start, end, type, "", path, current_time, bestPath, bestTime);

	// 输出最优路径
	cout << "Best Path from " << mycity.name[start] << " to " << mycity.name[end] << " starting after preset time:" << endl;
	if (bestPath.empty()) {
		cout << "No path found." << endl;
		return;
	}
	for (auto& step : bestPath) {
		cout << "从" << mycity.name[step.prev] << "出发, 到" << mycity.name[step.next]
			<< ", 类型: " << step.veh.type << ", 编号:" << step.veh.name << ", 在7月"
			<< step.veh.time1.day << "号" << step.veh.time1.hour << "点" << step.veh.time1.minute
			<< "分出发，耗时" << step.veh.consume << "小时，预估7月" << step.veh.time2.day << "号"
			<< step.veh.time2.hour << "点" << step.veh.time2.minute << "分到达，费用：" << step.veh.money << "元" << endl;
	}
}



//费用模块
//不可换工具
vehicle graph::getminmoney(vector<vehicle>& ve, times current_time, string type, string last_vehicle_name) {
	int minMoney = INF;
	vehicle minVehicle;
	for (auto& v : ve) {
		if (v.type != type) continue; // 确保交通工具类型匹配

		times adjusted_time;
		adjusted_time = current_time; // 调整后的到达时间

		// 如果有上一次的交通工具，并且名称不同，则根据类型添加等待时间
		if (!last_vehicle_name.empty() && v.name != last_vehicle_name) {
			int wait_time = (type == "fly") ? 120 : 60; // 飞机换乘等待2小时，火车换乘等待1小时(换算为分钟)
			adjusted_time.addMinutes(wait_time);
		}

		// 如果当前时间晚于调整后的出发时间，跳过这个交通工具
		if (adjusted_time > v.time1) continue;

		// 计算到达时间，如果这是目前为止找到的最快路径，更新minTime和minVehicle
		int k;
		k = v.money;
		if (k < minMoney) {
			minMoney = k;
			minVehicle = v;
		}
	}
	return minVehicle;
}


void graph::Money_Dijkstra(int v, int n, times current_time, string type) {
	vector<bool> visited(number, false);
	vector<times> dist(number, times(INF, INF, INF));
	vector<PathStep> path(number); // 使用PathStep替换之前的prev数组
	dist[v] = current_time;

	for (int i = 0; i < number; ++i) {
		int u = -1;
		times minTime(INF, INF, INF);
		for (int j = 0; j < number; j++) {
			if (!visited[j] && dist[j] < minTime) {
				u = j;
				minTime = dist[j];
			}
		}

		if (u == -1) break;
		visited[u] = true;

		for (int j = 0; j < edges[u].size(); j++) {
			for (auto& v : edges[u][j]) {
				if (v.type != type) continue;
				vehicle minVeh = getminmoney(edges[u][j], dist[u], type, path[u].veh.name); // 使用getminmoney函数找出费用最便宜的交通工具
				if (minVeh.name.empty()) continue; // 如果没有合适的交通工具，跳过

				times arrivalTime;
				arrivalTime = minVeh.time2;
				if (dist[u] < arrivalTime && arrivalTime < dist[j]) {
					dist[j] = arrivalTime;
					path[j] = PathStep(u, minVeh); // 存储前一个节点和使用的交通工具信息
				}
			}
		}
	}

	display(dist, path, visited, v, n, type);
}


//得到限制时间下的最省钱路径
vehicle graph::getminmoney_limit(vector<vehicle>& ve, times current_time, string type, string last_vehicle_name, int extra_hour) {
	int minMoney = INF;
	vehicle minVehicle;
	for (auto& v : ve) {
		if (v.type != type) continue; // 确保交通工具类型匹配

		times adjusted_time;
		adjusted_time = current_time; // 调整后的到达时间

		// 如果有上一次的交通工具，并且名称不同，则根据类型添加等待时间
		if (!last_vehicle_name.empty() && v.name != last_vehicle_name) {
			int wait_time = (type == "fly") ? 120 : 60; // 飞机换乘等待2小时，火车换乘等待1小时(换算为分钟)
			adjusted_time.addMinutes(wait_time);
		}

		if (last_vehicle_name.empty()) {
			times max_time = current_time;
			max_time.addMinutes(extra_hour * 60);
			if (adjusted_time > v.time1 || v.time1 > max_time) continue;
		}

		// 如果当前时间晚于调整后的出发时间，跳过这个交通工具
		else if (adjusted_time > v.time1) continue;


		// 计算到达时间，如果这是目前为止找到的最快路径，更新minTime和minVehicle
		int k;
		k = v.money;
		if (k < minMoney) {
			minMoney = k;
			minVehicle = v;
		}
	}
	return minVehicle;
}


//得到限制时间下的最省钱路径，配合上一个算法
void graph::Money_Dijkstra_limit(int v, int n, times current_time, string type, int extra_hour) {
	vector<bool> visited(number, false);
	vector<times> dist(number, times(INF, INF, INF));
	vector<PathStep> path(number); // 使用PathStep替换之前的prev数组
	dist[v] = current_time;

	for (int i = 0; i < number; ++i) {
		int u = -1;
		times minTime(INF, INF, INF);
		for (int j = 0; j < number; j++) {
			if (!visited[j] && dist[j] < minTime) {
				u = j;
				minTime = dist[j];
			}
		}

		if (u == -1) break;
		visited[u] = true;

		for (int j = 0; j < edges[u].size(); j++) {
			for (auto& v : edges[u][j]) {
				if (v.type != type) continue;
				vehicle minVeh = getminmoney_limit(edges[u][j], dist[u], type, path[u].veh.name, extra_hour); // 使用getminmoney函数找出费用最便宜的交通工具
				if (minVeh.name.empty()) continue; // 如果没有合适的交通工具，跳过

				times arrivalTime;
				arrivalTime = minVeh.time2;
				if (dist[u] < arrivalTime && arrivalTime < dist[j]) {
					dist[j] = arrivalTime;
					path[j] = PathStep(u, minVeh); // 存储前一个节点和使用的交通工具信息
				}
			}
		}
	}

	display(dist, path, visited, v, n, type);
}


//可换工具（费用最少）
vehicle graph::getminmoney2(vector<vehicle>& ve, times current_time, string last_vehicle_type, string last_vehicle_name) {
	int minMoney = INF;
	vehicle minVehicle;
	//这里不跳过类型不同的了，但仍然需要记录类型，因为类型决定了中转的时间
	for (auto& v : ve) {
		times adjusted_time;
		adjusted_time = current_time; // 调整后的到达时间

		// 如果有上一次的交通工具，并且名称不同，则根据类型添加等待时间
		if (!last_vehicle_name.empty() && v.name != last_vehicle_name) {
			int wait_time = (last_vehicle_type == "fly") ? 120 : 60; // 飞机换乘等待2小时，火车换乘等待1小时(换算为分钟)
			adjusted_time.addMinutes(wait_time);
		}

		// 如果当前时间晚于调整后的出发时间，跳过这个交通工具
		if (adjusted_time > v.time1) continue;

		// 计算到达时间，如果这是目前为止找到的最快路径，更新minTime和minVehicle
		int k;
		k = v.money;
		if (k < minMoney) {
			minMoney = k;
			minVehicle = v;
		}
	}
	return minVehicle;
}


void graph::Money_Dijkstra2(int v, int n, times current_time) {
	vector<bool> visited(number, false);
	vector<times> dist(number, times(INF, INF, INF));
	vector<PathStep> path(number); // 使用PathStep替换之前的prev数组
	dist[v] = current_time;

	for (int i = 0; i < number; i++) {
		int u = -1;
		times minTime(INF, INF, INF);
		for (int j = 0; j < number; j++) {
			if (!visited[j] && dist[j] < minTime) {
				u = j;
				minTime = dist[j];
			}
		}

		if (u == -1) break;
		visited[u] = true;

		for (int j = 0; j < edges[u].size(); j++) {
			for (auto& v : edges[u][j]) {
				vehicle minVeh = getminmoney2(edges[u][j], dist[u], path[u].veh.type, path[u].veh.name);
				if (minVeh.name.empty()) continue; // 如果没有合适的交通工具，跳过

				times arrivalTime;
				arrivalTime = minVeh.time2;
				if (dist[u] < arrivalTime && arrivalTime < dist[j]) {
					dist[j] = arrivalTime;
					path[j] = PathStep(u, minVeh); // 存储前一个节点和使用的交通工具信息
				}
			}
		}
	}

	display2(dist, path, visited, v, n);
}


//限制时间条件下
vehicle graph::getminmoney2_limit(vector<vehicle>& ve, times current_time, string last_vehicle_type, string last_vehicle_name, int extra_hour) {
	int minMoney = INF;
	vehicle minVehicle;
	//这里不跳过类型不同的了，但仍然需要记录类型，因为类型决定了中转的时间
	for (auto& v : ve) {
		times adjusted_time;
		adjusted_time = current_time; // 调整后的到达时间

		// 如果有上一次的交通工具，并且名称不同，则根据类型添加等待时间
		if (!last_vehicle_name.empty() && v.name != last_vehicle_name) {
			int wait_time = (last_vehicle_type == "fly") ? 120 : 60; // 飞机换乘等待2小时，火车换乘等待1小时(换算为分钟)
			adjusted_time.addMinutes(wait_time);
		}

		if (last_vehicle_name.empty()) {
			times max_time = current_time;
			max_time.addMinutes(extra_hour * 60);
			if (adjusted_time > v.time1 || v.time1 > max_time) continue;
		}

		// 如果当前时间晚于调整后的出发时间，跳过这个交通工具
		if (adjusted_time > v.time1) continue;

		// 计算到达时间，如果这是目前为止找到的最快路径，更新minTime和minVehicle
		int k;
		k = v.money;
		if (k < minMoney) {
			minMoney = k;
			minVehicle = v;
		}
	}
	return minVehicle;
}


//限制时间条件下，配合上一算法
void graph::Money_Dijkstra2_limit(int v, int n, times current_time,int extra_time) {
	vector<bool> visited(number, false);
	vector<times> dist(number, times(INF, INF, INF));
	vector<PathStep> path(number); // 使用PathStep替换之前的prev数组
	dist[v] = current_time;

	for (int i = 0; i < number; i++) {
		int u = -1;
		times minTime(INF, INF, INF);
		for (int j = 0; j < number; j++) {
			if (!visited[j] && dist[j] < minTime) {
				u = j;
				minTime = dist[j];
			}
		}

		if (u == -1) break;
		visited[u] = true;

		for (int j = 0; j < edges[u].size(); j++) {
			for (auto& v : edges[u][j]) {
				vehicle minVeh = getminmoney2_limit(edges[u][j], dist[u], path[u].veh.type, path[u].veh.name, extra_time);
				if (minVeh.name.empty()) continue; // 如果没有合适的交通工具，跳过

				times arrivalTime;
				arrivalTime = minVeh.time2;
				if (dist[u] < arrivalTime && arrivalTime < dist[j]) {
					dist[j] = arrivalTime;
					path[j] = PathStep(u, minVeh); // 存储前一个节点和使用的交通工具信息
				}
			}
		}
	}

	display2(dist, path, visited, v, n);
}



//公共展示
void graph::display(vector<times>& dist, vector<PathStep>& path, vector<bool>& S, int v, int n, string type) {
	cout << "Path from " << mycity.name[v] << " to " << mycity.name[n] << ":" << endl;
	int current = n;
	stack<vehicle> reversePath; // 使用vehicle来存储完整的交通工具信息
	stack<string> cities; // 存储经过的城市名称

	while (current != v) {
		if (current == -1) {
			cout << "No path found." << endl;
			return;
		}
		reversePath.push(path[current].veh);
		cities.push(mycity.name[current]); // 记录经过的城市
		current = path[current].prev;
	}
	cities.push(mycity.name[v]); // 添加起始城市

	// 输出路径信息
	string startCity = cities.top();
	cities.pop(); // 弹出起始城市

	while (!reversePath.empty()) {
		vehicle veh = reversePath.top();
		reversePath.pop();

		cout << "从" << startCity << "出发, 到" << cities.top() << ", 类型："
			<< veh.type << ", 编号：" << veh.name << ", 在7月"
			<< veh.time1.day << "号" << veh.time1.hour << "点" << veh.time1.minute << "分出发，耗时"
			<< veh.consume << "小时，预估7月" << veh.time2.day << "号" << veh.time2.hour << "点" <<
			veh.time2.minute << "分到达，费用：" << veh.money << "元" << endl;


		startCity = cities.top(); // 更新起始城市为当前到达城市
		cities.pop(); // 弹出已经输出的城市
	}
}


void graph::display2(vector<times>& dist, vector<PathStep>& path, vector<bool>& S, int v, int n) {
	cout << "Path from " << mycity.name[v] << " to " << mycity.name[n] << ":" << endl;
	int current = n;
	stack<vehicle> reversePath; // 使用vehicle来存储完整的交通工具信息
	vector<string> cities; // 存储经过的城市名称

	while (current != v) {
		if (current == -1) {
			cout << "No path found." << endl;
			return;
		}
		reversePath.push(path[current].veh);
		cities.push_back(mycity.name[current]); // 记录经过的城市
		current = path[current].prev;
	}
	cities.push_back(mycity.name[v]); // 添加起始城市

	// 输出路径信息
	string startCity = cities.back();
	cities.pop_back(); // 弹出起始城市

	while (!reversePath.empty()) {
		vehicle veh = reversePath.top();
		reversePath.pop();

		cout << "从" << startCity << "出发, 到" << cities.back() << ", 类型："
			<< veh.type << ", 编号：" << veh.name << ", 在7月"
			<< veh.time1.day << "号" << veh.time1.hour << "点" << veh.time1.minute << "分出发，耗时"
			<< veh.consume << "小时，预估7月" << veh.time2.day << "号" << veh.time2.hour << "点" <<
			veh.time2.minute << "分到达，费用：" << veh.money << "元" << endl;


		startCity = cities.back(); // 更新起始城市为当前到达城市
		cities.pop_back(); // 弹出已经输出的城市
	}
}


//直达（费用最少）
void graph::DFS2(int v, int end, const string& type, const string& vehicleName, vector<PathStep3>& path,
	times& current_time, vector<PathStep3>& bestPath, times& bestTime, double& cheapestCost) {
	if (v == end) { //费用不同于时间在于，需要将金钱不断地累加，得到最后的总金额才能比较
		//而时间只需要比较最后一趟的到达时间便可知道哪种最快
		double currentCost = 0;
		for (auto& step : path) {
			currentCost += step.veh.money;
		}

		if (currentCost < cheapestCost || cheapestCost == INF) {
			cheapestCost = currentCost;
			bestTime = current_time;
			bestPath = path;
		}
		return;
	}

	for (int j = 0; j < edges[v].size(); j++) {
		for (auto& veh : edges[v][j]) {
			if (veh.type != type) continue;
			if (!path.empty() && vehicleName != "" && veh.name != vehicleName) continue;

			if (current_time < veh.time1 || path.empty()) {
				times arrivalTime;
				arrivalTime = veh.time2;
				path.push_back(PathStep3(v, j, veh));
				string nextVehicleName = vehicleName == "" ? veh.name : vehicleName;
				DFS2(j, end, type, nextVehicleName, path, arrivalTime, bestPath, bestTime, cheapestCost);
				path.pop_back();
			}
		}
	}
}


void graph::findBestPath2(int start, int end, const times& preset_time, const string& type) {
	vector<PathStep3> bestPath;
	times bestTime(INF, INF, INF);
	double cheapestCost = INF;

	vector<PathStep3> path;
	times current_time = preset_time;

	DFS2(start, end, type, "", path, current_time, bestPath, bestTime, cheapestCost);

	cout << "Cheapest Path from " << mycity.name[start] << " to " << mycity.name[end] << " starting after preset time:" << endl;
	if (bestPath.empty()) {
		cout << "No path found." << endl;
		return;
	}
	for (auto& step : bestPath) {
		cout << "从" << mycity.name[step.prev] << "出发, 到" << mycity.name[step.next]
			<< ", 类型: " << step.veh.type << ", 编号:" << step.veh.name << ", 在7月"
			<< step.veh.time1.day << "号" << step.veh.time1.hour << "点" << step.veh.time1.minute
			<< "分出发，耗时" << step.veh.consume << "小时，预估7月" << step.veh.time2.day << "号"
			<< step.veh.time2.hour << "点" << step.veh.time2.minute << "分到达，费用：" << step.veh.money << "元" << endl;
	}
}


//可限制时间
void graph::DFS2_limit(int v, int end, const string& type, const string& vehicleName, vector<PathStep3>& path,
	times& current_time, vector<PathStep3>& bestPath, times& bestTime, double& cheapestCost,int extra_hour) {
	if (v == end) { //费用不同于时间在于，需要将金钱不断地累加，得到最后的总金额才能比较
		//而时间只需要比较最后一趟的到达时间便可知道哪种最快
		double currentCost = 0;
		for (auto& step : path) {
			currentCost += step.veh.money;
		}

		if (currentCost < cheapestCost || cheapestCost == INF) {
			cheapestCost = currentCost;
			bestTime = current_time;
			bestPath = path;
		}
		return;
	}

	for (int j = 0; j < edges[v].size(); j++) {
		for (auto& veh : edges[v][j]) {
			if (veh.type != type) continue;
			if (!path.empty() && vehicleName != "" && veh.name != vehicleName) continue;

			times max_time = current_time;

			if (path.empty()) {
				max_time.addMinutes(extra_hour * 60);
			}

			if (current_time < veh.time1 || (path.empty()&& veh.time1 < max_time)) {
					times arrivalTime;
					arrivalTime = veh.time2;
					path.push_back(PathStep3(v, j, veh));
					string nextVehicleName = vehicleName == "" ? veh.name : vehicleName;
					DFS2(j, end, type, nextVehicleName, path, arrivalTime, bestPath, bestTime, cheapestCost);
					path.pop_back();
			}
		}
	}
}


//可限制时间（对应上一函数）
void graph::findBestPath2_limit(int start, int end, const times& preset_time, const string& type, int extra_hour) {
	vector<PathStep3> bestPath;
	times bestTime(INF, INF, INF);
	double cheapestCost = INF;

	vector<PathStep3> path;
	times current_time = preset_time;

	DFS2_limit(start, end, type, "", path, current_time, bestPath, bestTime, cheapestCost, extra_hour);

	cout << "Cheapest Path from " << mycity.name[start] << " to " << mycity.name[end] << " starting after preset time:" << endl;
	if (bestPath.empty()) {
		cout << "No path found." << endl;
		return;
	}
	for (auto& step : bestPath) {
		cout << "从" << mycity.name[step.prev] << "出发, 到" << mycity.name[step.next]
			<< ", 类型: " << step.veh.type << ", 编号:" << step.veh.name << ", 在7月"
			<< step.veh.time1.day << "号" << step.veh.time1.hour << "点" << step.veh.time1.minute
			<< "分出发，耗时" << step.veh.consume << "小时，预估7月" << step.veh.time2.day << "号"
			<< step.veh.time2.hour << "点" << step.veh.time2.minute << "分到达，费用：" << step.veh.money << "元" << endl;
	}
}


//最优方案定义
void graph::optimal() {
	string city_name1, city_name2, transport_type;
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

	int day, hour, minute;
	cout << "请输入出发时间（日 时 分，例如 6 15 30表示本月的6号15点30分）：" << endl;
	cin >> day >> hour >> minute;

	times currentTime(day, hour, minute);

	cout << "请选择交通工具类型（train/fly）：" << endl;
	cin >> transport_type;

	if (transport_type != "train" && transport_type != "fly") {
		cout << "输入的交通工具类型不正确，请重新输入。" << endl;
		return;
	}

	cout << "计算" << (transport_type == "train" ? "火车" : "飞机") << "的最优路径..." << endl;
	Time_Dijkstra(start, destination, currentTime, transport_type);
}


void graph::optimal2() {
	string city_name1, city_name2, transport_type;
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

	int day, hour, minute;
	cout << "请输入出发时间（日 时 分，例如 6 15 30表示本月的6号15点30分）：" << endl;
	cin >> day >> hour >> minute;

	cout << "请选择交通工具类型（train/fly）：" << endl;
	cin >> transport_type;

	times currentTime(day, hour, minute);

	cout << "计算" << (transport_type == "train" ? "火车" : "飞机") << "的最优路径..." << endl;
	findBestPath(start, destination, currentTime, transport_type);
}



//自驾情况
void selfdrive() {

}


//调试用
void graph::show() {
	for (int i = 0; i < number; i++) {
		cout << mycity.name[i] << endl;
	}
	for (int i = 0; i < number; i++) {
		for (int j = 0; j < number; j++) {
			for (auto k : edges[i][j]) {
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
