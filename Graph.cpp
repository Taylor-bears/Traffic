#pragma once
#include "graph.h"
#include <iostream>
#include<string>
#include<fstream>
#include<vector>
#include<stack>
const int INF = 0x3f3f3f3f;

using namespace std;

//���ι��캯��
//���������У���Ҫʹ��"city.txt"��""��ʼ��
graph::graph(const string& file_path1, const string& file_path2, const string& file_path3) {
	mycity = city(file_path1, file_path2);//������Ҫ��ֵ
	number = mycity.name.size();
	edges.resize(number, vector<vector<vehicle>>(number));//��ʱ��������ά���飬ǰ��ά�ĳ������ɳ�������ȷ��

	//������ÿһ�����ж�Ӧһ����ţ����ں��������ÿ������
	for (int i = 0; i < number; i++) {
		this->traffic_map[mycity.name[i]] = i;
	}

	//���潨��ͼ����Ҫ��ȡ��ͨ�����ļ�����Ҳ�Ǳ���������Ҫ�Ĵ��沿��
	ifstream input(file_path3);
	char nosense;//���ڱ������õķ���
	string city_name1;
	string city_name2;
	//������vehicle���������
	string type;
	string identifier;
	times mytime1;
	double consume;
	times mytime2;
	double money;

	while (input >> nosense) { //��ȡ��
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
			getline(input, city_name1, ',');//��ȡ Beijing               
			getline(input, city_name2, ')');//��ȡ Wuhan    
			int num1 = traffic_map[city_name1];
			int num2 = traffic_map[city_name2];
			input >> nosense;//��ȡ","
			getline(input, type, ',');//1��Ϊ���ʹ洢
			getline(input, identifier, ',');//2��Ϊ��Ŵ洢
			getline(input, day1, '.');
			getline(input, hour1, ':');
			getline(input, minute1, ',');
			mytime1 = times(stoi(day1), stoi(hour1), stoi(minute1));//3��Ϊʱ��1�洢
			getline(input, hour_past, ':');
			getline(input, minute_past, ',');
			consume = time_transfer(stoi(hour_past), stoi(minute_past));//4��Ϊ��ʱ��Ҫ����
			getline(input, day2, '.');
			getline(input, hour2, ':');
			getline(input, minute2, ',');
			mytime2 = times(stoi(day2), stoi(hour2), stoi(minute2));//5��Ϊʱ��1�洢
			getline(input, cost);
			money = stod(cost);//6��Ϊ���ô洢
			vehicle myvehicle(type, identifier, mytime1, consume, mytime2, money);//�Ѿ���ȡ����һ��������
			//�����߶���ߵ������У����ڽӾ���ĵ���
			edges[num1][num2].push_back(myvehicle);//num1��num2���������еı�ţ�ע������������ͼ�������Գƣ�
		}
	}
	//ͨ�����ϲ���ֻ�ǽ���������ͨ�����ص����ӣ�
	//ͼ�л�Ҫ����0�͡������������
	for (int i = 0; i < number; i++) {
		for (int j = 0; j < number; j++) {
			if (edges[i][j].empty()) {//���Ϊ�գ���
				if (i == j) {
					vehicle myvehicle;
					edges[i][j].push_back(myvehicle);
				}
				//��ʱ����Ĭ�Ϲ��캯����ÿ��ֵ��Ϊ0��ͨ��ʶ��""�մ�(type)����֪��
				else {
					times timetmp1;//����Ĭ�Ϲ��죬�ڲ���Ա��Ϊ0
					times timetmp2;
					edges[i][j].push_back(vehicle("MAX", "MAX", timetmp1, INF, timetmp2, INF));
					//��ʱ��������������ֵ��ͨ��ʶ��"MAX"(type)����֪��
				}
			}
		}
	}
	/*����������cout << number;
	����������for (int i = 0; i < number; i++) {
		for (int j = 0; j < number; j++) {
			cout << edges[i][j].size()<<endl;
		}
	}
}*/
}

void graph::update(const string& file_path1, const string& file_path2, const string& file_path3) {
	mycity = city();
	number = 0;
	edges.clear();
	traffic_map.clear();

	mycity = city(file_path1, file_path2);//������Ҫ��ֵ
	number = mycity.name.size();
	edges.resize(number, vector<vector<vehicle>>(number));//��ʱ��������ά���飬ǰ��ά�ĳ������ɳ�������ȷ��

	//������ÿһ�����ж�Ӧһ����ţ����ں��������ÿ������
	for (int i = 0; i < number; i++) {
		this->traffic_map[mycity.name[i]] = i;
	}

	//���潨��ͼ����Ҫ��ȡ��ͨ�����ļ�����Ҳ�Ǳ���������Ҫ�Ĵ��沿��
	ifstream input(file_path3);
	char nosense;//���ڱ������õķ���
	string city_name1;
	string city_name2;
	//������vehicle���������
	string type;
	string identifier;
	times mytime1;
	double consume;
	times mytime2;
	double money;

	while (input >> nosense) { //��ȡ��
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
			getline(input, city_name1, ',');//��ȡ Beijing               
			getline(input, city_name2, ')');//��ȡ Wuhan    
			int num1 = traffic_map[city_name1];
			int num2 = traffic_map[city_name2];
			input >> nosense;//��ȡ","
			getline(input, type, ',');//1��Ϊ���ʹ洢
			getline(input, identifier, ',');//2��Ϊ��Ŵ洢
			getline(input, day1, '.');
			getline(input, hour1, ':');
			getline(input, minute1, ',');
			mytime1 = times(stoi(day1), stoi(hour1), stoi(minute1));//3��Ϊʱ��1�洢
			getline(input, hour_past, ':');
			getline(input, minute_past, ',');
			consume = time_transfer(stoi(hour_past), stoi(minute_past));//4��Ϊ��ʱ��Ҫ����
			getline(input, day2, '.');
			getline(input, hour2, ':');
			getline(input, minute2, ',');
			mytime2 = times(stoi(day2), stoi(hour2), stoi(minute2));//5��Ϊʱ��1�洢
			getline(input, cost);
			money = stod(cost);//6��Ϊ���ô洢
			vehicle myvehicle(type, identifier, mytime1, consume, mytime2, money);//�Ѿ���ȡ����һ��������
			//�����߶���ߵ������У����ڽӾ���ĵ���
			edges[num1][num2].push_back(myvehicle);//num1��num2���������еı�ţ�ע������������ͼ�������Գƣ�
		}
	}
	//ͨ�����ϲ���ֻ�ǽ���������ͨ�����ص����ӣ�
	//ͼ�л�Ҫ����0�͡������������
	for (int i = 0; i < number; i++) {
		for (int j = 0; j < number; j++) {
			if (edges[i][j].empty()) {//���Ϊ�գ���
				if (i == j) {
					vehicle myvehicle;
					edges[i][j].push_back(myvehicle);
				}
				//��ʱ����Ĭ�Ϲ��캯����ÿ��ֵ��Ϊ0��ͨ��ʶ��""�մ�(type)����֪��
				else {
					times timetmp1;//����Ĭ�Ϲ��죬�ڲ���Ա��Ϊ0
					times timetmp2;
					edges[i][j].push_back(vehicle("MAX", "MAX", timetmp1, INF, timetmp2, INF));
					//��ʱ��������������ֵ��ͨ��ʶ��"MAX"(type)����֪��
				}
			}
		}
	}
}

//Ĭ�Ϲ��캯��
graph::graph() {
	number = 0;
}


bool graph::timecheck(times time1, times time2, int wait_hours) {
	// ���Ƚ��ȴ�ʱ��ӵ�time1��
	time1.hour += wait_hours;
	time1.day += time1.hour / 24; // ����24Сʱ������һ��
	time1.hour %= 24; // ����Сʱ��

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


//ʱ��ת�������Ķ���
double graph::time_transfer(int hour, int minute)
{
	double a;
	a = hour + minute / 60.0;
	a = static_cast<int>(a * 10 + 0.5);
	return a / 10.0;
}


//ʱ��ģ��
//(�������м�任��ͨ����)
//���Եõ��ڽӾ���ĳ������ʱ�����Сֵ��Ӧ�Ľ�ͨ��ʽ
//ͬ������ĳ����֮�����С��ʽ������Ҫ������һ�εĽ�ͨ��ʽ����Ϊ��ת�ĵȴ�ʱ����Ҫ���Ҳ�ͬ
vehicle graph::getmin(vector<vehicle>& ve, times current_time, string type, string last_vehicle_name) {
	times minTime = times(INF, INF, INF);
	vehicle minVehicle;
	for (auto& v : ve) {
		if (v.type != type) continue; // ȷ����ͨ��������ƥ��

		times adjusted_time;
		adjusted_time = current_time; // ������ĵ���ʱ��

		// �������һ�εĽ�ͨ���ߣ��������Ʋ�ͬ�������������ӵȴ�ʱ��
		if (!last_vehicle_name.empty() && v.name != last_vehicle_name) {
			int wait_time = (type == "fly") ? 120 : 60; // �ɻ����˵ȴ�2Сʱ���𳵻��˵ȴ�1Сʱ(����Ϊ����)
			adjusted_time.addMinutes(wait_time);
		}

		// �����ǰʱ�����ڵ�����ĳ���ʱ�䣬���������ͨ����
		if ( adjusted_time > v.time1) continue;

		// ���㵽��ʱ�䣬�������ĿǰΪֹ�ҵ������·��������minTime��minVehicle
		times k;
		k = v.time2;
		if (k < minTime) {
			minTime = k;
			minVehicle = v;
		}
	}
	return minVehicle;
}


//ͨ�����㷨�ɵõ���Сʱ��·�����οͽ�����ת��
void graph::Time_Dijkstra(int v, int n, times current_time, string type) {
	//ԭ�ҿ�˹�����㷨���֣����������Ҹı�������
	vector<bool> visited(number, false);
	vector<times> dist(number, times(INF, INF, INF));
	vector<PathStep> path(number); // ʹ��PathStep�滻֮ǰ��prev����
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
				if (minVeh.name.empty()) continue; // ���û�к��ʵĽ�ͨ���ߣ�����

				times arrivalTime;
			    arrivalTime = minVeh.time2;
				if (dist[u] < arrivalTime && arrivalTime < dist[j]) {
					dist[j] = arrivalTime;
					path[j] = PathStep(u, minVeh); // �洢ǰһ���ڵ��ʹ�õĽ�ͨ������Ϣ
				}
			}
		}
	}

	display(dist, path, visited, v, n, type);
}


//����任��ͨ���ߣ�ʱ��ģ�飩
vehicle graph::getmin2(vector<vehicle>& ve, times current_time, string last_vehicle_type, string last_vehicle_name) {
	times minTime = times(INF, INF, INF);
	vehicle minVehicle;
	//���ﲻ�������Ͳ�ͬ���ˣ�����Ȼ��Ҫ��¼���ͣ���Ϊ���;�������ת��ʱ��
	for (auto& v : ve) {
		times adjusted_time;
		adjusted_time = current_time; // ������ĵ���ʱ��

		int wait_time = 0;
		// �������һ�εĽ�ͨ���ߣ��������Ʋ�ͬ�������������ӵȴ�ʱ��
		if (!last_vehicle_name.empty() && v.name != last_vehicle_name) {
			if (last_vehicle_type == "train" && v.type== "fly")
				wait_time = 120;
			else if (last_vehicle_type == "train" && v.type== "train")
				wait_time = 60;
			else if (last_vehicle_type == "fly" && v.type== "fly")
				wait_time = 120;
			else if (last_vehicle_type == "fly" && v.type== "train")
				wait_time = 60;
		}
		adjusted_time.addMinutes(wait_time);

		// �����ǰʱ�����ڵ�����ĳ���ʱ�䣬���������ͨ����
		if (adjusted_time > v.time1) continue;

		// ���㵽��ʱ�䣬�������ĿǰΪֹ�ҵ������·��������minTime��minVehicle
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
	vector<PathStep> path(number); // ʹ��PathStep�滻֮ǰ��prev����
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
				if (minVeh.name.empty()) continue; // ���û�к��ʵĽ�ͨ���ߣ�����

				times arrivalTime;
				arrivalTime = minVeh.time2;
				if (dist[u] < arrivalTime && arrivalTime < dist[j]) {
					dist[j] = arrivalTime;
					path[j] = PathStep(u, minVeh); // �洢ǰһ���ڵ��ʹ�õĽ�ͨ������Ϣ
				}
			}
		}
	}

	display(dist, path, visited, v, n, "");
}


//ֱ�ʱ����̣�
void graph::DFS(int v, int end, const string& type, const string& vehicleName, vector<PathStep3>& path,
	times& current_time, vector<PathStep3>& bestPath, times& bestTime) {
	if (v == end) { // ����Ŀ�ĵ�
		if (current_time < bestTime || bestTime.day == INF) {
			bestTime = current_time;// �������ʱ��
			bestPath = path;// ��������·��
		}
		return;
	}

	for (int j = 0; j < edges[v].size(); j++) {
		for (auto& veh : edges[v][j]) {
			if (veh.type != type) continue; // ��ͨ�������Ͳ�ƥ��
			// ȷ����ͨ��������ƥ�����·���ĵ�һ��

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



//�������ڷɻ����г��У���������ѡ����ʱ�����һ��ʹ֮���Էֱ���ʾ������
void graph::findBestPath(int start, int end, const times& preset_time, const string& type) {
	vector<PathStep3> bestPath;
	times bestTime(INF, INF, INF); // ��ʼ�����ʱ��Ϊ�����

	vector<PathStep3> path;
	times current_time = preset_time;
	// ����DFSʱ��vehicleName����Ϊ���ַ�������ʾ��û��ѡ��ͨ����
	DFS(start, end, type, "", path, current_time, bestPath, bestTime);

	// �������·��
	cout << "Best Path from " << mycity.name[start] << " to " << mycity.name[end] << " starting after preset time:" << endl;
	if (bestPath.empty()) {
		cout << "No path found." << endl;
		return;
	}
	for (auto& step : bestPath) {
		cout << "��" << mycity.name[step.prev] << "����, ��" << mycity.name[step.next]
			<< ", ����: " << step.veh.type << ", ���:" << step.veh.name << ", ��7��"
			<< step.veh.time1.day << "��" << step.veh.time1.hour << "��" << step.veh.time1.minute
			<< "�ֳ�������ʱ" << step.veh.consume << "Сʱ��Ԥ��7��" << step.veh.time2.day << "��"
			<< step.veh.time2.hour << "��" << step.veh.time2.minute << "�ֵ�����ã�" << step.veh.money << "Ԫ" << endl;
	}
}



//����ģ��
//���ɻ�����
vehicle graph::getminmoney(vector<vehicle>& ve, times current_time, string type, string last_vehicle_name) {
	int minMoney = INF;
	vehicle minVehicle;
	for (auto& v : ve) {
		if (v.type != type) continue; // ȷ����ͨ��������ƥ��

		times adjusted_time;
		adjusted_time = current_time; // ������ĵ���ʱ��

		// �������һ�εĽ�ͨ���ߣ��������Ʋ�ͬ�������������ӵȴ�ʱ��
		if (!last_vehicle_name.empty() && v.name != last_vehicle_name) {
			int wait_time = (type == "fly") ? 120 : 60; // �ɻ����˵ȴ�2Сʱ���𳵻��˵ȴ�1Сʱ(����Ϊ����)
			adjusted_time.addMinutes(wait_time);
		}

		// �����ǰʱ�����ڵ�����ĳ���ʱ�䣬���������ͨ����
		if (adjusted_time > v.time1) continue;

		// ���㵽��ʱ�䣬�������ĿǰΪֹ�ҵ������·��������minTime��minVehicle
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
	vector<PathStep> path(number); // ʹ��PathStep�滻֮ǰ��prev����
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
				vehicle minVeh = getminmoney(edges[u][j], dist[u], type, path[u].veh.name); // ʹ��getminmoney�����ҳ���������˵Ľ�ͨ����
				if (minVeh.name.empty()) continue; // ���û�к��ʵĽ�ͨ���ߣ�����

				times arrivalTime;
				arrivalTime = minVeh.time2;
				if (dist[u] < arrivalTime && arrivalTime < dist[j]) {
					dist[j] = arrivalTime;
					path[j] = PathStep(u, minVeh); // �洢ǰһ���ڵ��ʹ�õĽ�ͨ������Ϣ
				}
			}
		}
	}

	display(dist, path, visited, v, n, type);
}


//�õ�����ʱ���µ���ʡǮ·��
vehicle graph::getminmoney_limit(vector<vehicle>& ve, times current_time, string type, string last_vehicle_name, int extra_day) {
	int minMoney = INF;
	vehicle minVehicle;
	for (auto& v : ve) {
		if (v.type != type) continue; // ȷ����ͨ��������ƥ��

		times adjusted_time;
		adjusted_time = current_time; // ������ĵ���ʱ��

		// �������һ�εĽ�ͨ���ߣ��������Ʋ�ͬ�������������ӵȴ�ʱ��
		if (!last_vehicle_name.empty() && v.name != last_vehicle_name) {
			int wait_time = (type == "fly") ? 120 : 60; // �ɻ����˵ȴ�2Сʱ���𳵻��˵ȴ�1Сʱ(����Ϊ����)
			adjusted_time.addMinutes(wait_time);
		}

		if (last_vehicle_name.empty()) {
			times max_time = current_time;
			max_time.addMinutes(extra_day * 24 * 60);
			if (adjusted_time > v.time1 || v.time1 > max_time) continue;
		}

		// �����ǰʱ�����ڵ�����ĳ���ʱ�䣬���������ͨ����
		else if (adjusted_time > v.time1) continue;


		// ���㵽��ʱ�䣬�������ĿǰΪֹ�ҵ������·��������minTime��minVehicle
		int k;
		k = v.money;
		if (k < minMoney) {
			minMoney = k;
			minVehicle = v;
		}
	}
	return minVehicle;
}


//�õ�����ʱ���µ���ʡǮ·���������һ���㷨
void graph::Money_Dijkstra_limit(int v, int n, times current_time, string type, int extra_hour) {
	vector<bool> visited(number, false);
	vector<times> dist(number, times(INF, INF, INF));
	vector<PathStep> path(number); // ʹ��PathStep�滻֮ǰ��prev����
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
				vehicle minVeh = getminmoney_limit(edges[u][j], dist[u], type, path[u].veh.name, extra_hour); // ʹ��getminmoney�����ҳ���������˵Ľ�ͨ����
				if (minVeh.name.empty()) continue; // ���û�к��ʵĽ�ͨ���ߣ�����

				times arrivalTime;
				arrivalTime = minVeh.time2;
				if (dist[u] < arrivalTime && arrivalTime < dist[j]) {
					dist[j] = arrivalTime;
					path[j] = PathStep(u, minVeh); // �洢ǰһ���ڵ��ʹ�õĽ�ͨ������Ϣ
				}
			}
		}
	}

	display(dist, path, visited, v, n, type);
}


//�ɻ����ߣ��������٣�
vehicle graph::getminmoney2(vector<vehicle>& ve, times current_time, string last_vehicle_type, string last_vehicle_name) {
	int minMoney = INF;
	vehicle minVehicle;
	//���ﲻ�������Ͳ�ͬ���ˣ�����Ȼ��Ҫ��¼���ͣ���Ϊ���;�������ת��ʱ��
	for (auto& v : ve) {
		times adjusted_time;
		adjusted_time = current_time; // ������ĵ���ʱ��

		int wait_time = 0;
		// �������һ�εĽ�ͨ���ߣ��������Ʋ�ͬ�������������ӵȴ�ʱ��
		if (!last_vehicle_name.empty() && v.name != last_vehicle_name) {
			if (last_vehicle_type == "train" && v.type == "fly")
				wait_time = 120;
			else if (last_vehicle_type == "train" && v.type == "train")
				wait_time = 60;
			else if (last_vehicle_type == "fly" && v.type == "fly")
				wait_time = 120;
			else if (last_vehicle_type == "fly" && v.type == "train")
				wait_time = 60;
		}
		adjusted_time.addMinutes(wait_time);

		// �����ǰʱ�����ڵ�����ĳ���ʱ�䣬���������ͨ����
		if (adjusted_time > v.time1) continue;

		// ���㵽��ʱ�䣬�������ĿǰΪֹ�ҵ������·��������minTime��minVehicle
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
	vector<PathStep> path(number); // ʹ��PathStep�滻֮ǰ��prev����
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
				if (minVeh.name.empty()) continue; // ���û�к��ʵĽ�ͨ���ߣ�����

				times arrivalTime;
				arrivalTime = minVeh.time2;
				if (dist[u] < arrivalTime && arrivalTime < dist[j]) {
					dist[j] = arrivalTime;
					path[j] = PathStep(u, minVeh); // �洢ǰһ���ڵ��ʹ�õĽ�ͨ������Ϣ
				}
			}
		}
	}

	display(dist, path, visited, v, n, "");
}


//����ʱ��������
vehicle graph::getminmoney2_limit(vector<vehicle>& ve, times current_time, string last_vehicle_type, string last_vehicle_name, int extra_day) {
	int minMoney = INF;
	vehicle minVehicle;
	//���ﲻ�������Ͳ�ͬ���ˣ�����Ȼ��Ҫ��¼���ͣ���Ϊ���;�������ת��ʱ��
	for (auto& v : ve) {
		times adjusted_time;
		adjusted_time = current_time; // ������ĵ���ʱ��

		// �������һ�εĽ�ͨ���ߣ��������Ʋ�ͬ�������������ӵȴ�ʱ��
		if (!last_vehicle_name.empty() && v.name != last_vehicle_name) {
			int wait_time = (last_vehicle_type == "fly") ? 120 : 60; // �ɻ����˵ȴ�2Сʱ���𳵻��˵ȴ�1Сʱ(����Ϊ����)
			adjusted_time.addMinutes(wait_time);
		}

		if (last_vehicle_name.empty()) {
			times max_time = current_time;
			max_time.addMinutes(extra_day * 24 * 60);
			if (adjusted_time > v.time1 || v.time1 > max_time) continue;
		}

		// �����ǰʱ�����ڵ�����ĳ���ʱ�䣬���������ͨ����
		if (adjusted_time > v.time1) continue;

		// ���㵽��ʱ�䣬�������ĿǰΪֹ�ҵ������·��������minTime��minVehicle
		int k;
		k = v.money;
		if (k < minMoney) {
			minMoney = k;
			minVehicle = v;
		}
	}
	return minVehicle;
}


//����ʱ�������£������һ�㷨
void graph::Money_Dijkstra2_limit(int v, int n, times current_time,int extra_time) {
	vector<bool> visited(number, false);
	vector<times> dist(number, times(INF, INF, INF));
	vector<PathStep> path(number); // ʹ��PathStep�滻֮ǰ��prev����
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
				if (minVeh.name.empty()) continue; // ���û�к��ʵĽ�ͨ���ߣ�����

				times arrivalTime;
				arrivalTime = minVeh.time2;
				if (dist[u] < arrivalTime && arrivalTime < dist[j]) {
					dist[j] = arrivalTime;
					path[j] = PathStep(u, minVeh); // �洢ǰһ���ڵ��ʹ�õĽ�ͨ������Ϣ
				}
			}
		}
	}

	display(dist, path, visited, v, n, "");
}



//����չʾ
void graph::display(vector<times>& dist, vector<PathStep>& path, vector<bool>& S, int v, int n, string type) {
	cout << "Path from " << mycity.name[v] << " to " << mycity.name[n] << ":" << endl;
	int current = n;
	stack<vehicle> reversePath; // ʹ��vehicle���洢�����Ľ�ͨ������Ϣ
	stack<string> cities; // �洢�����ĳ�������

	while (current != v) {
		if (current == -1) {
			cout << "No path found." << endl;
			return;
		}
		reversePath.push(path[current].veh);
		cities.push(mycity.name[current]); // ��¼�����ĳ���
		current = path[current].prev;
	}
	cities.push(mycity.name[v]); // �����ʼ����

	// ���·����Ϣ
	string startCity = cities.top();
	cities.pop(); // ������ʼ����

	while (!reversePath.empty()) {
		vehicle veh = reversePath.top();
		reversePath.pop();

		cout << "��" << startCity << "����, ��" << cities.top() << ", ���ͣ�"
			<< veh.type << ", ��ţ�" << veh.name << ", ��7��"
			<< veh.time1.day << "��" << veh.time1.hour << "��" << veh.time1.minute << "�ֳ�������ʱ"
			<< veh.consume << "Сʱ��Ԥ��7��" << veh.time2.day << "��" << veh.time2.hour << "��" <<
			veh.time2.minute << "�ֵ�����ã�" << veh.money << "Ԫ" << endl;


		startCity = cities.top(); // ������ʼ����Ϊ��ǰ�������
		cities.pop(); // �����Ѿ�����ĳ���
	}
}


//ֱ��������٣�
void graph::DFS2(int v, int end, const string& type, const string& vehicleName, vector<PathStep3>& path,
	times& current_time, vector<PathStep3>& bestPath, times& bestTime, double& cheapestCost) {
	if (v == end) { //���ò�ͬ��ʱ�����ڣ���Ҫ����Ǯ���ϵ��ۼӣ��õ������ܽ����ܱȽ�
		//��ʱ��ֻ��Ҫ�Ƚ����һ�˵ĵ���ʱ����֪���������
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
		cout << "��" << mycity.name[step.prev] << "����, ��" << mycity.name[step.next]
			<< ", ����: " << step.veh.type << ", ���:" << step.veh.name << ", ��7��"
			<< step.veh.time1.day << "��" << step.veh.time1.hour << "��" << step.veh.time1.minute
			<< "�ֳ�������ʱ" << step.veh.consume << "Сʱ��Ԥ��7��" << step.veh.time2.day << "��"
			<< step.veh.time2.hour << "��" << step.veh.time2.minute << "�ֵ�����ã�" << step.veh.money << "Ԫ" << endl;
	}
}


//������ʱ��
void graph::DFS2_limit(int v, int end, const string& type, const string& vehicleName, vector<PathStep3>& path,
	times& current_time, vector<PathStep3>& bestPath, times& bestTime, double& cheapestCost,int extra_day) {
	if (v == end) { //���ò�ͬ��ʱ�����ڣ���Ҫ����Ǯ���ϵ��ۼӣ��õ������ܽ����ܱȽ�
		//��ʱ��ֻ��Ҫ�Ƚ����һ�˵ĵ���ʱ����֪���������
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
				max_time.addMinutes(extra_day * 24 * 60);
			}

			if (current_time < veh.time1 || path.empty()) {
				if (path.empty() && veh.time1 < max_time) {
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
}


//������ʱ�䣨��Ӧ��һ������
void graph::findBestPath2_limit(int start, int end, const times& preset_time, const string& type, int extra_day) {
	vector<PathStep3> bestPath;
	times bestTime(INF, INF, INF);
	double cheapestCost = INF;

	vector<PathStep3> path;
	times current_time = preset_time;

	DFS2_limit(start, end, type, "", path, current_time, bestPath, bestTime, cheapestCost, extra_day);

	cout << "Cheapest Path from " << mycity.name[start] << " to " << mycity.name[end] << " starting after preset time:" << endl;
	if (bestPath.empty()) {
		cout << "No path found." << endl;
		return;
	}
	for (auto& step : bestPath) {
		cout << "��" << mycity.name[step.prev] << "����, ��" << mycity.name[step.next]
			<< ", ����: " << step.veh.type << ", ���:" << step.veh.name << ", ��7��"
			<< step.veh.time1.day << "��" << step.veh.time1.hour << "��" << step.veh.time1.minute
			<< "�ֳ�������ʱ" << step.veh.consume << "Сʱ��Ԥ��7��" << step.veh.time2.day << "��"
			<< step.veh.time2.hour << "��" << step.veh.time2.minute << "�ֵ�����ã�" << step.veh.money << "Ԫ" << endl;
	}
}


//��type�������ŷ�������
//�����type����·�� Time_Dijkstra
void graph::optimal() {
	string city_name1, city_name2, transport_type;
	cout << "���������ĳ�������Ŀ�ĵأ��ص�ĸ�ʽ������ Beijing����" << endl;
	cout << "����������أ�" << endl;
	cin >> city_name1;
	cout << "������Ŀ�ĵأ�" << endl;
	cin >> city_name2;

	if (traffic_map.find(city_name1) == traffic_map.end() || traffic_map.find(city_name2) == traffic_map.end()) {
		cout << "����ĳ��в����ڣ����������롣" << endl;
		return;
	}

	int start = traffic_map[city_name1];
	int destination = traffic_map[city_name2];

	int day, hour, minute;
	cout << "���������ʱ�䣨�� ʱ �֣����� 6 15 30��ʾ���µ�6��15��30�֣���" << endl;
	cin >> day >> hour >> minute;

	times currentTime(day, hour, minute);

	cout << "��ѡ��ͨ�������ͣ�train/fly����" << endl;
	cin >> transport_type;

	if (transport_type != "train" && transport_type != "fly") {
		cout << "����Ľ�ͨ�������Ͳ���ȷ�����������롣" << endl;
		return;
	}

	cout << "����" << (transport_type == "train" ? "��" : "�ɻ�") << "�����·��..." << endl;
	cout << "��;�в����Ը�����ͨ���������£��������·������" << endl;
	Time_Dijkstra(start, destination, currentTime, transport_type);
}


void graph::optimal( string city1, string city2, string transport_type, int day, int hour, int minute) {
	if (traffic_map.find(city1) == traffic_map.end() || traffic_map.find(city2) == traffic_map.end()) {
		cout << "����ĳ��в����ڣ����������롣" << endl;
		return;
	}

	int start = traffic_map[city1];
	int destination = traffic_map[city2];

	times currentTime(day, hour, minute);

	if (transport_type != "train" && transport_type != "fly") {
		cout << "����Ľ�ͨ�������Ͳ���ȷ�����������롣" << endl;
		return;
	}

	cout << "����" << (transport_type == "train" ? "��" : "�ɻ�") << "�����·��..." << endl;
	cout << "��;�в����Ը�����ͨ���������£��������·������" << endl;
	Time_Dijkstra(start, destination, currentTime, transport_type);
}


//��ʡǮ��type����·�� Money_Dijkstra
void graph::optimal_money() {
	string city_name1, city_name2, transport_type;
	cout << "���������ĳ�������Ŀ�ĵأ��ص�ĸ�ʽ������ Beijing����" << endl;
	cout << "����������أ�" << endl;
	cin >> city_name1;
	cout << "������Ŀ�ĵأ�" << endl;
	cin >> city_name2;

	if (traffic_map.find(city_name1) == traffic_map.end() || traffic_map.find(city_name2) == traffic_map.end()) {
		cout << "����ĳ��в����ڣ����������롣" << endl;
		return;
	}

	int start = traffic_map[city_name1];
	int destination = traffic_map[city_name2];

	int day, hour, minute;
	cout << "���������ʱ�䣨�� ʱ �֣����� 6 15 30��ʾ���µ�6��15��30�֣���" << endl;
	cin >> day >> hour >> minute;

	times currentTime(day, hour, minute);

	cout << "��ѡ��ͨ�������ͣ�train/fly����" << endl;
	cin >> transport_type;

	if (transport_type != "train" && transport_type != "fly") {
		cout << "����Ľ�ͨ�������Ͳ���ȷ�����������롣" << endl;
		return;
	}

	cout << "����" << (transport_type == "train" ? "��" : "�ɻ�") << "����ʡǮ·��..." << endl;
	cout << "��;�в����Ը�����ͨ���������£�������ʡǮ·������" << endl;
	Money_Dijkstra(start, destination, currentTime, transport_type);
}


void graph::optimal_money( string city1, string city2, string transport_type, int day, int hour, int minute) {
	if (traffic_map.find(city1) == traffic_map.end() || traffic_map.find(city2) == traffic_map.end()) {
		cout << "����ĳ��в����ڣ����������롣" << endl;
		return;
	}

	int start = traffic_map[city1];
	int destination = traffic_map[city2];

	times currentTime(day, hour, minute);

	if (transport_type != "train" && transport_type != "fly") {
		cout << "����Ľ�ͨ�������Ͳ���ȷ�����������롣" << endl;
		return;
	}

	cout << "����" << (transport_type == "train" ? "��" : "�ɻ�") << "����ʡǮ·��..." << endl;
	cout << "��;�в����Ը�����ͨ���������£�������ʡǮ·������" << endl;
	Money_Dijkstra(start, destination, currentTime, transport_type);
}


//��type�������ŷ�������
//�����type����·�� Time_Dijkstra2
void graph::optimal_notype() {
	string city_name1, city_name2;
	cout << "���������ĳ�������Ŀ�ĵأ��ص�ĸ�ʽ������ Beijing����" << endl;
	cout << "����������أ�" << endl;
	cin >> city_name1;
	cout << "������Ŀ�ĵأ�" << endl;
	cin >> city_name2;

	if (traffic_map.find(city_name1) == traffic_map.end() || traffic_map.find(city_name2) == traffic_map.end()) {
		cout << "����ĳ��в����ڣ����������롣" << endl;
		return;
	}

	int start = traffic_map[city_name1];
	int destination = traffic_map[city_name2];

	int day, hour, minute;
	cout << "���������ʱ�䣨�� ʱ �֣����� 6 15 30��ʾ���µ�6��15��30�֣���" << endl;
	cin >> day >> hour >> minute;

	times currentTime(day, hour, minute);

	cout << "�������·��..." << endl;
	cout << "��;�п��Ը�����ͨ���������£��������·������" << endl;
	Time_Dijkstra2(start, destination, currentTime);
}


void graph::optimal_notype( string city1, string city2, int day, int hour, int minute) {
	if (traffic_map.find(city1) == traffic_map.end() || traffic_map.find(city2) == traffic_map.end()) {
		cout << "����ĳ��в����ڣ����������롣" << endl;
		return;
	}

	int start = traffic_map[city1];
	int destination = traffic_map[city2];

	times currentTime(day, hour, minute);

	cout << "�������·��..." << endl;
	cout << "��;�п��Ը�����ͨ���������£��������·������" << endl;
	Time_Dijkstra2(start, destination, currentTime);
}


//�����type����·�� Money_Dijkstra2
void graph::optimal_money_notype() {
	string city_name1, city_name2;
	cout << "���������ĳ�������Ŀ�ĵأ��ص�ĸ�ʽ������ Beijing����" << endl;
	cout << "����������أ�" << endl;
	cin >> city_name1;
	cout << "������Ŀ�ĵأ�" << endl;
	cin >> city_name2;

	if (traffic_map.find(city_name1) == traffic_map.end() || traffic_map.find(city_name2) == traffic_map.end()) {
		cout << "����ĳ��в����ڣ����������롣" << endl;
		return;
	}

	int start = traffic_map[city_name1];
	int destination = traffic_map[city_name2];

	int day, hour, minute;
	cout << "���������ʱ�䣨�� ʱ �֣����� 6 15 30��ʾ���µ�6��15��30�֣���" << endl;
	cin >> day >> hour >> minute;

	times currentTime(day, hour, minute);

	cout << "������ʡǮ·��..." << endl;
	cout << "��;�п��Ը�����ͨ���������£�������ʡǮ·������" << endl;
	Money_Dijkstra2(start, destination, currentTime);
}


void graph::optimal_money_notype(string city1, string city2, int day, int hour, int minute) {
	if (traffic_map.find(city1) == traffic_map.end() || traffic_map.find(city2) == traffic_map.end()) {
		cout << "����ĳ��в����ڣ����������롣" << endl;
		return;
	}

	int start = traffic_map[city1];
	int destination = traffic_map[city2];

	times currentTime(day, hour, minute);

	cout << "������ʡǮ·��..." << endl;
	cout << "��;�п��Ը�����ͨ���������£�������ʡǮ·������" << endl;
	Money_Dijkstra2(start, destination, currentTime);
}


//��ʡǮ��type������time����·�� Money_Dijkstra_limit
void graph::optimal_money_limit() {
	string city_name1, city_name2, transport_type;
	cout << "���������ĳ�������Ŀ�ĵأ��ص�ĸ�ʽ������ Beijing����" << endl;
	cout << "����������أ�" << endl;
	cin >> city_name1;
	cout << "������Ŀ�ĵأ�" << endl;
	cin >> city_name2;

	if (traffic_map.find(city_name1) == traffic_map.end() || traffic_map.find(city_name2) == traffic_map.end()) {
		cout << "����ĳ��в����ڣ����������롣" << endl;
		return;
	}

	int start = traffic_map[city_name1];
	int destination = traffic_map[city_name2];
	int extra_day;

	int day, hour, minute;
	cout << "���������ʱ�䣨�� ʱ �֣����� 6 15 30��ʾ���µ�6��15��30�֣���" << endl;
	cin >> day >> hour >> minute;
	cout << "��������������" << endl;
	cin >> extra_day;

	times currentTime(day, hour, minute);

	cout << "��ѡ��ͨ�������ͣ�train/fly����" << endl;
	cin >> transport_type;

	if (transport_type != "train" && transport_type != "fly") {
		cout << "����Ľ�ͨ�������Ͳ���ȷ�����������롣" << endl;
		return;
	}

	cout << "����" << (transport_type == "train" ? "��" : "�ɻ�") << "����ʡǮ·��..." << endl;
	cout << "��;�в����Ը�����ͨ���������£�������ʡǮ·������" << endl;
	Money_Dijkstra_limit(start, destination, currentTime, transport_type, extra_day);
}


void graph::optimal_money_limit(string city1, string city2, int day, int hour, int minute, string transport_type, int extra_day) {
	if (traffic_map.find(city1) == traffic_map.end() || traffic_map.find(city2) == traffic_map.end()) {
		cout << "����ĳ��в����ڣ����������롣" << endl;
		return;
	}

	int start = traffic_map[city1];
	int destination = traffic_map[city2];

	times currentTime(day, hour, minute);

	if (transport_type != "train" && transport_type != "fly") {
		cout << "����Ľ�ͨ�������Ͳ���ȷ�����������롣" << endl;
		return;
	}

	cout << "����" << (transport_type == "train" ? "��" : "�ɻ�") << "����ʡǮ·��..." << endl;
	cout << "��;�в����Ը�����ͨ���������£�������ʡǮ·������" << endl;
	Money_Dijkstra_limit(start, destination, currentTime, transport_type, extra_day);
}


//��ʡǮ��type������time����·�� Money_Dijkstra2_limit
void graph::optimal_money_notype_limit() {
	string city_name1, city_name2, transport_type;
	cout << "���������ĳ�������Ŀ�ĵأ��ص�ĸ�ʽ������ Beijing����" << endl;
	cout << "����������أ�" << endl;
	cin >> city_name1;
	cout << "������Ŀ�ĵأ�" << endl;
	cin >> city_name2;

	if (traffic_map.find(city_name1) == traffic_map.end() || traffic_map.find(city_name2) == traffic_map.end()) {
		cout << "����ĳ��в����ڣ����������롣" << endl;
		return;
	}

	int start = traffic_map[city_name1];
	int destination = traffic_map[city_name2];
	int extra_day;

	int day, hour, minute;
	cout << "���������ʱ�䣨�� ʱ �֣����� 6 15 30��ʾ���µ�6��15��30�֣���" << endl;
	cin >> day >> hour >> minute;
	cout << "��������������" << endl;
	cin >> extra_day;

	times currentTime(day, hour, minute);

	cout << "������ʡǮ·��..." << endl;
	cout << "��;�в����Ը�����ͨ���������£�������ʡǮ·������" << endl;
	Money_Dijkstra2_limit(start, destination, currentTime, extra_day);
}


void graph::optimal_money_notype_limit(string city1, string city2, int day, int hour, int minute, int extra_day) {
	if (traffic_map.find(city1) == traffic_map.end() || traffic_map.find(city2) == traffic_map.end()) {
		cout << "����ĳ��в����ڣ����������롣" << endl;
		return;
	}

	int start = traffic_map[city1];
	int destination = traffic_map[city2];

	times currentTime(day, hour, minute);

	cout << "������ʡǮ·��..." << endl;
	cout << "��;�в����Ը�����ͨ���������£�������ʡǮ·������" << endl;
	Money_Dijkstra2_limit(start, destination, currentTime, extra_day);
}


//ֱ��
//���ֱ��·�� findBestPath
void graph::optimal_DFS() {
	string city_name1, city_name2, transport_type;
	cout << "���������ĳ�������Ŀ�ĵأ��ص�ĸ�ʽ������ Beijing����" << endl;
	cout << "����������أ�" << endl;
	cin >> city_name1;
	cout << "������Ŀ�ĵأ�" << endl;
	cin >> city_name2;

	if (traffic_map.find(city_name1) == traffic_map.end() || traffic_map.find(city_name2) == traffic_map.end()) {
		cout << "����ĳ��в����ڣ����������롣" << endl;
		return;
	}

	int start = traffic_map[city_name1];
	int destination = traffic_map[city_name2];

	int day, hour, minute;
	cout << "���������ʱ�䣨�� ʱ �֣����� 6 15 30��ʾ���µ�6��15��30�֣���" << endl;
	cin >> day >> hour >> minute;

	cout << "��ѡ��ͨ�������ͣ�train/fly����" << endl;
	cin >> transport_type;

	times currentTime(day, hour, minute);

	cout << "����" << (transport_type == "train" ? "��" : "�ɻ�") << "������·��..." << endl;
	cout << "��ֱ���£��������·������" << endl;
	findBestPath(start, destination, currentTime, transport_type);
}


void graph::optimal_DFS(string city1, string city2, string transport_type, int day, int hour, int minute) {
	if (traffic_map.find(city1) == traffic_map.end() || traffic_map.find(city2) == traffic_map.end()) {
		cout << "����ĳ��в����ڣ����������롣" << endl;
		return;
	}

	int start = traffic_map[city1];
	int destination = traffic_map[city2];

	times currentTime(day, hour, minute);

	cout << "����" << (transport_type == "train" ? "��" : "�ɻ�") << "������·��..." << endl;
	cout << "��ֱ���£��������·������" << endl;
	findBestPath(start, destination, currentTime, transport_type);
}


//��ʡǮֱ��·�� findBestPath2
void graph::optimal_DFS_money() {
	string city_name1, city_name2, transport_type;
	cout << "���������ĳ�������Ŀ�ĵأ��ص�ĸ�ʽ������ Beijing����" << endl;
	cout << "����������أ�" << endl;
	cin >> city_name1;
	cout << "������Ŀ�ĵأ�" << endl;
	cin >> city_name2;

	if (traffic_map.find(city_name1) == traffic_map.end() || traffic_map.find(city_name2) == traffic_map.end()) {
		cout << "����ĳ��в����ڣ����������롣" << endl;
		return;
	}

	int start = traffic_map[city_name1];
	int destination = traffic_map[city_name2];

	int day, hour, minute;
	cout << "���������ʱ�䣨�� ʱ �֣����� 6 15 30��ʾ���µ�6��15��30�֣���" << endl;
	cin >> day >> hour >> minute;

	cout << "��ѡ��ͨ�������ͣ�train/fly����" << endl;
	cin >> transport_type;

	times currentTime(day, hour, minute);

	cout << "����" << (transport_type == "train" ? "��" : "�ɻ�") << "������·��..." << endl;
	cout << "��ֱ���£�������ʡǮ·������" << endl;
	findBestPath2(start, destination, currentTime, transport_type);
}


void graph::optimal_DFS_money(string city1, string city2, string transport_type, int day, int hour, int minute) {
	if (traffic_map.find(city1) == traffic_map.end() || traffic_map.find(city2) == traffic_map.end()) {
		cout << "����ĳ��в����ڣ����������롣" << endl;
		return;
	}

	int start = traffic_map[city1];
	int destination = traffic_map[city2];

	times currentTime(day, hour, minute);

	cout << "����" << (transport_type == "train" ? "��" : "�ɻ�") << "������·��..." << endl;
	cout << "��ֱ���£�������ʡǮ·������" << endl;
	findBestPath2(start, destination, currentTime, transport_type);
}


//��ʡǮ��time����ֱ��·�� findBestPath2_limit
void graph::optimal_DFS_money_limit() {
	string city_name1, city_name2, transport_type;
	cout << "���������ĳ�������Ŀ�ĵأ��ص�ĸ�ʽ������ Beijing����" << endl;
	cout << "����������أ�" << endl;
	cin >> city_name1;
	cout << "������Ŀ�ĵأ�" << endl;
	cin >> city_name2;

	if (traffic_map.find(city_name1) == traffic_map.end() || traffic_map.find(city_name2) == traffic_map.end()) {
		cout << "����ĳ��в����ڣ����������롣" << endl;
		return;
	}

	int start = traffic_map[city_name1];
	int destination = traffic_map[city_name2];
	int extra_day;

	int day, hour, minute;
	cout << "���������ʱ�䣨�� ʱ �֣����� 6 15 30��ʾ���µ�6��15��30�֣���" << endl;
	cin >> day >> hour >> minute;

	cout << "��ѡ��ͨ�������ͣ�train/fly����" << endl;
	cin >> transport_type;

	times currentTime(day, hour, minute);
	cout << "��������������" << endl;
	cin >> extra_day;

	cout << "����" << (transport_type == "train" ? "��" : "�ɻ�") << "������·��..." << endl;
	cout << "��ֱ���£�������ʡǮ·������" << endl;
	findBestPath2_limit(start, destination, currentTime, transport_type, extra_day);
}


void graph::optimal_DFS_money_limit(string city1, string city2, int day, int hour, int minute, string transport_type, int extra_day) {
	if (traffic_map.find(city1) == traffic_map.end() || traffic_map.find(city2) == traffic_map.end()) {
		cout << "����ĳ��в����ڣ����������롣" << endl;
		return;
	}

	int start = traffic_map[city1];
	int destination = traffic_map[city2];
	
	times currentTime(day, hour, minute);
	
	cout << "����" << (transport_type == "train" ? "��" : "�ɻ�") << "������·��..." << endl;
	cout << "��ֱ���£�������ʡǮ·������" << endl;
	findBestPath2_limit(start, destination, currentTime, transport_type, extra_day);
}


//������
void graph::show() {
	cout << "���еĳ������£�" << endl;
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


//������
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



//��ѯ����
void graph::find_city() {

	ifstream input("city_pre.txt");
	string m;
	cout << "��������Ҫ��ѯ�ĳ��У�" << endl;
	string city;
	cin >> city;
	for (auto k : mycity.name) {
		if (k == city) {
			cout << "�ó������ļ�����" << endl;
			while (input >> m) {
				if (m != k) {
					input >> m;
					input >> m;
				}
				else if (m == k)
					break;
			}
			cout << "�ó��е���ϸ��Ϣ����" << endl;
			cout << "��������" << m << "����γ��";
			input >> m;
			cout<<m<< "��������";
			input >> m;
			cout << m << endl;
		}
	}
	int i = 0;
	for (; i < mycity.name.size(); i++)
		if (city == mycity.name[i])
			break;
	if (i == mycity.name.size())
		cout << "�ó��в����ļ�����" << endl;
	return;
}


void graph::find_twocity() {
	cout << "��������Ҫ��ѯ���������У�" << endl;
	string city1, city2;
	cout << "����1��";
	cin >> city1;
	cout << endl;
	cout << "����2��";
	cin >> city2;
	cout << endl;
	int i = 0;
	for (; i < mycity.name.size(); i++)
		if (city1 == mycity.name[i])
			break;
	if (i == mycity.name.size()) {
		cout << "�ó��в����ļ�����" << endl;
		return;
	}
	int j = 0;
	for (; j < mycity.name.size(); j++)
		if (city2 == mycity.name[j])
			break;
	if (j == mycity.name.size()) {
		cout << "�ó��в����ļ�����" << endl;
		return;
	}
	cout << "�������м��ֱ�߾���Ϊ��" << mycity.distance_map[make_pair(city1, city2)] << "km" << endl;
	if (mycity.dist[i][j] != 0) {
		cout << "�������м�������ͨ����Ϊ��" << mycity.dist[i][j] << "km" << endl;
	}
	else if (mycity.dist[i][j] == 0) {
		cout << "��������δ��ͨ" << endl;
	}
}


//��ѯ��ͨ����
void graph::find_vehicle() {
	cout << "����������Ҫ��ѯ����������" << endl;
	string city1, city2;
	cout << "����1�� ";
	cin >> city1;
	cout << endl;
	cout << "����2�� ";
	cin >> city2;
	cout << endl;
	int i = 0;
	for (; i < mycity.name.size(); i++)
		if (city1 == mycity.name[i])
			break;
	if (i == mycity.name.size()) {
		cout << "�ó��в����ļ�����" << endl;
		return;
	}
	int j = 0;
	for (; j < mycity.name.size(); j++)
		if (city2 == mycity.name[j])
			break;
	if (j == mycity.name.size()) {
		cout << "�ó��в����ļ�����" << endl;
		return;
	}
	i = traffic_map[city1];
	j = traffic_map[city2];
	for (auto n : edges[i][j]) {
		if (n.type != "MAX" && n.type != "") {
				cout << "��" << city1 << "����, ��" << city2
				<< ", ����: " << n.type << ", ���:" << n.name << ", ��7��"
				<< n.time1.day << "��" << n.time1.hour << "��" << n.time1.minute
				<< "�ֳ�������ʱ" << n.consume << "Сʱ��Ԥ��7��" << n.time2.day << "��"
				<< n.time2.hour << "��" << n.time2.minute << "�ֵ�����ã�" << n.money << "Ԫ" << endl;
		}
	}
	int u;
	for ( u = 0; u < edges[i][j].size(); u++) {
		if (edges[i][j][u].type != "MAX" && edges[i][j][u].type != "")
			break;
	}
	if (u == edges[i][j].size())
		cout << "�������������֮��û�н�ͨ·��" << endl;
}



//��ѯ��ͨ���ߣ���time���ƣ�
void graph::find_vehicle_limit() {
	string city1, city2;
	int day1, hour1, minute1;
	int day2, hour2, minute2;
	cout << "����������Ҫ��ѯ����������" << endl;
	cout << "����1�� ";
	cin >> city1;
	cout << endl;
	cout << "����2�� ";
	cin >> city2;
	cout << endl;
	cout << "�����������ѯ��ʱ�䷶Χ" << endl;
	cout << "��ʼʱ�䣨�� ʱ �֣����� 6 15 30��ʾ���µ�6��15��30�֣��� ";
	cin >> day1 >> hour1 >> minute1;
	cout << "��ֹʱ�䣨�� ʱ �֣����� 6 15 30��ʾ���µ�6��15��30�֣��� ";
	cin >> day2 >> hour2 >> minute2;
	times start(day1, hour1, minute1);
	times end(day2, hour2, minute2);
	int i = 0;
	for (; i < mycity.name.size(); i++)
		if (city1 == mycity.name[i])
			break;
	if (i == mycity.name.size()) {
		cout << "�ó��в����ļ�����" << endl;
		return;
	}
	int j = 0;
	for (; j < mycity.name.size(); j++)
		if (city2 == mycity.name[j])
			break;
	if (j == mycity.name.size()) {
		cout << "�ó��в����ļ�����" << endl;
		return;
	}
	i = traffic_map[city1];
	j = traffic_map[city2];
	for (auto n : edges[i][j]) {
		if (n.type != "MAX" && n.type != "" && (start < n.time1 && n.time1 < end)) {
			cout << "��" << city1 << "����, ��" << city2
				<< ", ����: " << n.type << ", ���:" << n.name << ", ��7��"
				<< n.time1.day << "��" << n.time1.hour << "��" << n.time1.minute
				<< "�ֳ�������ʱ" << n.consume << "Сʱ��Ԥ��7��" << n.time2.day << "��"
				<< n.time2.hour << "��" << n.time2.minute << "�ֵ�����ã�" << n.money << "Ԫ" << endl;
		}
	}
	int u;
	for (u = 0; u < edges[i][j].size(); u++) {
		if (edges[i][j][u].type != "MAX" && edges[i][j][u].type != ""&& (start < edges[i][j][u].time1 && edges[i][j][u].time1 < end))
			break;
	}
	if (u == edges[i][j].size())
		cout << "�������������֮��û�н�ͨ·��" << endl;
}