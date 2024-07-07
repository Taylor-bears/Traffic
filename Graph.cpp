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
vehicle graph::getmin(vector<vehicle> ve, times current_time, string last_vehicle_type, string last_vehicle_name) {//���һ�εĽ�ͨ����
	double min = INF; // ��С���ó�ʼ��Ϊ�����
	int minnum = -1; // ��С���
	int wait_hours; 
	
	// �𳵵ȴ�1Сʱ���ɻ��ȴ�2Сʱ������������ȴ����������ʼ�أ���û����һ���ߣ��ʵȴ�ʱ��Ϊ0��

	for (int i = 0; i < ve.size(); i++) {
		if (last_vehicle_name == "") {
			wait_hours = 0;//��һ�εķ�ʽ��������һ��ʽ��������һ��ͨ��ʽΪ0
		}
		else if (last_vehicle_name != ""&& ve[i].name != last_vehicle_name ) { //��һ���г�û����һ����˵��
			wait_hours = (last_vehicle_type == "train") ? 1 : 2 ;//�Ƿɻ���Ϊ2Сʱ
		}
		else if (last_vehicle_name != "" && ve[i].name == last_vehicle_name) {
			wait_hours = 0;
		}
		//current_times����һ�εĵ���ʱ��
		if (timecheck(current_time, ve[i].time1, wait_hours) && ve[i].consume < min) { 
			// ����÷�ʽ�ĳ���ʱ�������������Һ�ʱ��С
			minnum = i;
			min = ve[i].consume;
		}
	}

	if (min == INF) { // ������е�ʱ�䶼�����ϣ��򷵻����޴�ͨ��
		times timetmp1, timetmp2;
		return vehicle("MAX", "MAX", timetmp1, INF, timetmp2, INF);
	}
	return ve[minnum]; // ������С��ͨ��ʽ
}

//ͨ�����㷨�ɵõ���Сʱ��·�����οͽ�����ת��
void graph::Time_Dijkstra(int v, int n, times current_time) {
	vector<vehicle> dist(number);//�����Ϊtimes�ͣ���Ϊ�˷����ҵ����ĳ��˺�ʱ��������Ϣ
	vector<int> path(number);
	vector<int> S(number);

	vector<times> arrival_time(number);
	vector<string> vehicle_type(number);//��i�εĽ�ͨ����
	vector<string> vehicle_name(number);//��i�εĽ�ͨ����

	for (int i = 0; i < number; i++) {			 
			dist[i] = getmin(edges[v][i], current_time, "", "");//��ʱwait_hours Ϊ0
			S[i] = 0;
			if (dist[i].consume != 0 && dist[i].consume < INF)
				path[i] = v;
			else
				path[i] = -1;
	}
	S[v] = 1;
	vehicle mindis;//ÿһ�ε���С���
	int u = -1;
	for (int i = 0; i < number - 1; i++) {
		mindis.consume = INF;
		for (int j = 0; j < number; j++) 
			if (S[j] == 0 && dist[j].consume < mindis.consume) {
				u = j;
				mindis = dist[j];
			}
		S[u] = 1; //��ʱѡ������С�㲻�ɸ���
		//��ʱ��Ҫ����С����Ϣ��ӵ���һ��Ϣ���У���ΪҪ����һ�εĳ���ʱ�����ɸѡ
		arrival_time.push_back(mindis.time2);
		vehicle_type.push_back(mindis.type);
		vehicle_name.push_back(mindis.name);
		//�޸Ĳ���S�ж���ľ���

	}
}


void graph::dispaly(vector<double> dist, vector<int> path, vector<bool> S, int v, int n, vector<times> arrival_time, vector<string> last_vehicle_type) {
	if (S[n]) { // �����v��n����·��
		cout << "�ӳ����ص�Ŀ�ĵص���췽ʽ���£�" << endl;
		vector<int> apath;
		int current = n;
		//�ع˵ҿ�˹�����㷨Ѱ��·���Ĺ��̣�����ͨ��n���ҵ�����ǰһ���㣬������ǰ��ģ�ֱ���ҵ�������
		while (current != v) { 
			apath.push_back(current);
			current = path[current];
		}
		apath.push_back(v); // �����ʼ��

		//��Ϊapath�����ǵ����ҵģ���ô����������Ǵ�ԭ�㴦���
		// �������apath�����·��
		for (int i = apath.size() - 1; i > 0; i--) {
			int from = apath[i], to = apath[i - 1];
			// ����ÿ�����м�ֻ��һ�����·�����������ֻȡ��һ��
			vehicle& v = edges[from][to][0];
			cout << "��" << mycity.name[from] << "����,��" << mycity.name[to] << ",���ͣ�"
				<< v.type << ",��ţ�" << v.name << ",��"
				<< v.time1.day << "��" << v.time1.hour << "ʱ" << v.time1.minute << "�ֳ�������ʱ"
				<< v.consume << "Сʱ��Ԥ��" << v.time2.day << "��" << v.time2.hour << "ʱ" << v.time2.minute << "�ֵ�����ã�"
				<< v.money << "Ԫ" << endl;
		}

		// �����ʾ����Ŀ�ĵص�ʱ��
		cout << "Ԥ�Ƶ���ʱ�䣺" << arrival_time[n].day << "�� "
			<< arrival_time[n].hour << "ʱ " << arrival_time[n].minute << "��" << endl;
	}
	else {
		cout << "û���ҵ��ӳ����ص�Ŀ�ĵص�·����" << endl;
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