#include "city.h"
#include <iostream>
#include<fstream>
#include<string>
#include<utility>
#include<unordered_map>

using namespace std;

//����ͷ�ļ��е�city���캯��
city::city(const string& file_path) {
	ifstream input(file_path); //������������ʵ��ӦΪ"city.txt"
    if (input.is_open()) { //ȷ���ļ�Ҫ����
        char nosense;//���ڱ������õķ���
        string city_name1;
        string city_name2;

        while (input >> nosense) {
            if (nosense == '(') {
                getline(input, city_name1, ',');//��ȡ ����               
                getline(input, city_name2, ')');//��ȡ �人                 

                //��ȡ�������е���Ϣ
                int i;
                for (i = 0; i < name.size(); i++) {
                    if (city_name1 == name[i])
                        break;
                }
                if (i == name.size()) {
                    name.push_back(city_name1);//���name��û��city_name1�������vector��
                }
                
                int j;
                for (j = 0; j < name.size(); j++) {
                    if (city_name2 == name[j])
                        break;
                }
                if (j == name.size()) {
                    name.push_back(city_name2);//���name��û��city_name2�������vector��
                }

                //��ȡ���о�����Ϣ
                string distance;
                int distance_num;
                getline(input, distance, 'k');//100kmֻ����k
                input >> nosense ; //��m���룬�´ξͶ���(
                distance_num = stoi(distance);

                //�������������ϣ�������빹�ɹ�ϣ��
                pair<string, string> distances = make_pair(city_name1, city_name2);//������������Ϊһ��               
                this->distance_map[distances] = distance_num; //��ͬ����֮��ľ������γɹ�ϣ��

            }
            else
                break;
        }
        // this->distance_map.find(make_pair("BeiJing", "ShangHai"))->second; ���Ҫ���������м���룬�����������
        input.close(); //�ر��ļ�
    }
    else {
        std::cerr << "Unable to open file" << std::endl; //�޷����򱨴�
    }


}