#pragma once
#include "graph.h"
#include <iostream>
#include<string>
#include<fstream>
#include<vector>
const int INF = 0x3f3f3f3f;

using namespace std;

//���ι��캯��
//���������У���Ҫʹ��"city.txt"��""��ʼ��
graph::graph(const string& file_path1, const string& file_path2) {
	mycity = city(file_path1);//������Ҫ��ֵ
	number = mycity.name.size();
	edges.resize(number, vector<vector<vehicle>>(number));//��ʱ��������ά���飬ǰ��ά�ĳ������ɳ�������ȷ��

	//������ÿһ�����ж�Ӧһ����ţ����ں��������ÿ������
	for (int i = 0; i < number; i++) {
		this->traffic_map[mycity.name[i]] = i;
	}

	//���潨��ͼ����Ҫ��ȡ��ͨ�����ļ�����Ҳ�Ǳ���������Ҫ�Ĵ��沿��
	ifstream input("vehicle.txt");
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

//Ĭ�Ϲ��캯��
graph::graph() {
	//��
}

//���еķ������е�ǰ�ᶼ������ʱ��Ҫ�ȸ���������������
// �Ƚ�time1���ϵȴ�ʱ���Ƿ�С�ڵ���time2��������ϱȽ�ʱ������Ϊ�˱��ں��洦����תվ��Ҫ�ȴ������
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

//���Եõ��ڽӾ���ĳ������ʱ�����Сֵ��Ӧ�Ľ�ͨ��ʽ
//ͬ������ĳ����֮�����С��ʽ������Ҫ������һ�εĽ�ͨ��ʽ����Ϊ��ת�ĵȴ�ʱ����Ҫ���Ҳ�ͬ
vehicle graph::getmin(const vector<vehicle>& ve, const times& current_time, const string& 
	required_vehicle_type, const string& last_vehicle_name) {
	double min = INF;
	int minnum = -1;
	int wait_hours = 0;

	for (int i = 0; i < ve.size(); i++) {
		// ���ָ���˽�ͨ�������ͣ����ҵ�ǰ��ͨ����������Ҫ��Ĳ�����������
		if (!required_vehicle_type.empty() && ve[i].type != required_vehicle_type) {
			continue;
		}

		// ������һ�εĽ�ͨ��ʽȷ���ȴ�ʱ��
		if (last_vehicle_name.empty()) {
			wait_hours = 0; // ���û����һ�ν�ͨ��ʽ���ȴ�ʱ��Ϊ0
		}
		else if (!last_vehicle_name.empty() && ve[i].name != last_vehicle_name) {
			wait_hours = (ve[i].type == "train") ? 1 : 2; // ���ݵ�ǰ��ͨ��ʽȷ���ȴ�ʱ��
		}
		else if (!last_vehicle_name.empty() && ve[i].name == last_vehicle_name) {
			wait_hours = 0; // ͬһ��ͨ���߲��ȴ�
		}

		// ���㿼�ǵȴ�ʱ���ĳ���ʱ��
		times adjusted_departure_time = current_time;
		adjusted_departure_time.addMinutes(wait_hours * 60); // ����addMinutes��һ����ӷ��ӵķ���

		// ȷ������ʱ��������һ�ε���ʱ����ϵȴ�ʱ��
		if (timecheck(adjusted_departure_time, ve[i].time1, 0) && ve[i].consume < min) {
			minnum = i;
			min = ve[i].consume;
		}
	}

	if (min == INF) {
		times timetmp1, timetmp2;
		return vehicle("MAX", "MAX", timetmp1, INF, timetmp2, INF); // ����һ����ʾ��Ч���������vehicle����
	}
	return ve[minnum];
}


//ͨ�����㷨�ɵõ���Сʱ��·�����οͽ�����ת��
void graph::Time_Dijkstra(int v, int n, times current_time) {
	// �ֱ�Ϊ�𳵺ͷɻ���ʼ��
	vector<vector<times>> dist(2, vector<times>(number, times(INF, INF, INF))); // ��ʼ������Ϊ�����
	vector<vector<int>> path(2, vector<int>(number, -1)); // ��ʼ��·��
	vector<bool> S(number, false); // ������飬false��ʾδ������
	vector<vector<times>> arrival_time(2, vector<times>(number, times(INF, INF, INF))); // ��¼��ÿ������ĵ���ʱ��
	vector<vector<string>> last_vehicle_type(2, vector<string>(number)); // ��¼��ÿ�������������Ľ�ͨ��������
	vector<vector<string>> last_vehicle_name(2, vector<string>(number));

	// ��ʼ�����ֱ�Ի𳵺ͷɻ�����
	for (int mode = 0; mode < 2; ++mode) { // mode: 0Ϊ��, 1Ϊ�ɻ�
		string initialType = mode == 0 ? "train" : "fly";
		dist[mode][v] = times(0, 0, 0); // �Լ����Լ�Ϊ0
		arrival_time[mode][v] = current_time; // ������ĵ���ʱ����ǵ�ǰʱ��

		// ���³�ʼ�㵽����������·��
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

	// ��ÿ��ģʽ���𳵡��ɻ���ִ��Dijkstra�㷨
	for (int mode = 0; mode < 2; ++mode) {
		fill(S.begin(), S.end(), false); // ����S����

		for (int count = 0; count < number - 1; count++) {
			// Ѱ�ҵ�ǰδ�������Сdist����
			times minTime(INF, INF, INF);
			int u = -1;
			for (int j = 0; j < number; j++) {
				if (!S[j] && dist[mode][j] < minTime) { // ʹ�����ص�<����������Զ���ȽϺ���
					u = j;
					minTime = dist[mode][j];
				}
			}
			if (u == -1) break; // ���û���ҵ�������ѭ��

			S[u] = true;

			// ����dist����
			for (int j = 0; j < number; j++) {
				if (!S[j] && !edges[u][j].empty()) {
					vehicle minVehicle = getmin(edges[u][j], arrival_time[mode][u], last_vehicle_type[mode][u], last_vehicle_name[mode][u]);
					if (minVehicle.type == last_vehicle_type[mode][u]) { // ���ֽ�ͨ���߲���
						// ���㵽��ʱ�䣬������ת�ȴ�ʱ��
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

	// �Ƚϻ𳵺ͷɻ������Ž�
	if (dist[0][n] < dist[1][n]) {
		// �𳵸���
		dispaly(dist[0], path[0], S, v, n, arrival_time[0], last_vehicle_type[0], last_vehicle_name[0]);
	}
	else {
		// �ɻ���������
		dispaly(dist[1], path[1], S, v, n, arrival_time[1], last_vehicle_type[1], last_vehicle_name[1]);
	}
}


void graph::dispaly(vector<times> dist, vector<int> path, vector<bool> S, int v, int n,
	vector<times> arrival_time, vector<string> vehicle_type, vector<string> vehicle_name) {
	if (!S[n]) { // �����v��n������·��
		cout << "û���ҵ��ӳ����ص�Ŀ�ĵص�·����" << endl;
		return;
	}

	cout << "�ӳ����ص�Ŀ�ĵص���췽ʽ���£�" << endl;
	vector<int> apath;
	int current = n;
	while (current != v) {
		apath.push_back(current);
		current = path[current];
	}
	apath.push_back(v); // �����ʼ��

	for (int i = apath.size() - 2; i >= 0; i--) { // ע������ı�����ʽ������
		int from = apath[i + 1], to = apath[i];
		vehicle& v = edges[from][to][0]; // ����ÿ�����м�ֻ��һ�����·��
		cout << "��" << mycity.name[from] << "����, ��" << mycity.name[to] << ", ���ͣ�"
			<< v.type << ", ��ţ�" << v.name << ", ��"
			<< v.time1.day << "��" << v.time1.hour << "��" << v.time1.minute << "�ֳ�������ʱ"
			<< v.consume << "Сʱ��Ԥ��" << v.time2.day << "��" << v.time2.hour << "��" << v.time2.minute << "�ֵ�����ã�"
			<< v.money << "Ԫ" << endl;
	}

}



//���ŷ�������
void graph::optimal() {
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

	// ���û��������ʱ�䣨ֻ�����ա�ʱ���֣�
	int day, hour, minute;
	cout << "���������ʱ�䣨�� ʱ �֣����� 6 15 30��ʾ���µ�6��15��30�֣���" << endl;
	cin >> day >> hour >> minute;

	// ����һ��times��������ʾ�û�����ĳ���ʱ��
	times currentTime(day, hour, minute);

	// ����Time_Dijkstra������������·��
	Time_Dijkstra(start, destination, currentTime); // ���������������times������Ϊ����
}


//������
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