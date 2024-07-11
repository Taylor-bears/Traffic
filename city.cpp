#include "city.h"
#include <iostream>
#include<fstream>
#include<string>
#include<utility>
#include<unordered_map>

using namespace std;

const int INF = 0x3f3f3f3f;

//补充头文件中的city构造函数
city::city(const string& file_path) {
	ifstream input(file_path); //后面主函数中实参应为"city.txt"
    if (input.is_open()) { //确保文件要被打开
        char nosense;//用于保存无用的符号
        string city_name1;
        string city_name2;

        while (input >> nosense) {
            if (nosense == '(') {
                getline(input, city_name1, ',');//读取 Beijing               
                getline(input, city_name2, ')');//读取 Wuhan                 

                //读取两座城市的信息
                int i;
                for (i = 0; i < name.size(); i++) {
                    if (city_name1 == name[i])
                        break;
                }
                if (i == name.size()) {
                    name.push_back(city_name1);//如果name中没有city_name1，则存入vector中
                }
                
                int j;
                for (j = 0; j < name.size(); j++) {
                    if (city_name2 == name[j])
                        break;
                }
                if (j == name.size()) {
                    name.push_back(city_name2);//如果name中没有city_name2，则存入vector中
                }

                //读取城市距离信息
                string distance;
                int distance_num;
                getline(input, distance, 'k');//100km只读到k
                input >> nosense ; //将m读入，下次就读入(
                distance_num = stoi(distance);

                //将城市与城市组合，并与距离构成哈希表
                pair<string, string> distances = make_pair(city_name1, city_name2);//以两个城市作为一组               
                this->distance_map[distances] = distance_num; //不同城市之间的距离已形成哈希表

            }
            else
                break;
        }
        /*测试用例：cout << this->distance_map.find(make_pair("Beijing", "Shanghai"))->second;
        测试用例：cout << name.size() << endl;
        for (auto i : name) {
            cout << i << endl;
        }*/

        // this->distance_map.find(make_pair("BeiJing", "ShangHai"))->second; 如果要查找两城市间距离，就用这个方法



        int number = name.size();
        //下面是初始化距离矩阵
        dist.resize(number, vector<int>(number,INF));
        for (int i = 0; i < number; i++) {
            for (int j = 0; j < number; j++) {
                if (i == j) {
                    dist[i][j] = 0;
                }
                else {
                    auto it = distance_map.find({ name[i], name[j] });
                    if (it != distance_map.end()) {
                        dist[i][j] = it->second;
                    }
                }
            }
        }

        //解决问题的关键：使用 Floyd-Warshall 算法来计算传递闭包
        for (int k = 0; k < number; k++) {
            for (int i = 0; i < number; i++) {
                for (int j = 0; j < number; j++) {
                    if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }

        input.close(); //关闭文件
    }
    else {
        std::cerr << "Unable to open file" << std::endl; //无法打开则报错
    }
}

//无参数时构造函数
city::city() {
    //无
}

