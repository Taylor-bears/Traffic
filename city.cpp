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
                if (i == name.size() - 1) {
                    name.push_back(city_name1);//���name��û��city_name1�������vector��
                }
                
                int i;
                for (i = 0; i < name.size(); i++) {
                    if (city_name2 == name[i])
                        break;
                }
                if (i == name.size() - 1) {
                    name.push_back(city_name2);//���name��û��city_name2�������vector��
                }

                //��ȡ���о�����Ϣ
                string distance;
                int distance_num;
                getline(input, distance, 'k');//100kmֻ����k
                input >> nosense >> nosense; //��k��m���룬�´ξͶ���(
                distance_num = stoi(distance);

                //�������������ϣ�������빹�ɹ�ϣ��
                pair<string, string> distances = make_pair(city_name1, city_name2);//������������Ϊһ��
                unordered_map<pair<string, string>, int> distance_map;
                distance_map[distances] = distance_num; //��ͬ����


            }
            else
                break;
        }

        input.close();
    }
    else {
        std::cerr << "Unable to open file" << std::endl;
    }


}