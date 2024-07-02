#include "Student.h"
#include "Design_subject.h"
#include "Teacher.h"
#include "Function.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

extern Design_subject mysubject[50];
extern Student mystudent[200];
extern Teacher myteacher[4];
extern Basic_function Bf;
Student_function Sf;
Teacher_function Tf;

void studentMenu(int studentIndex) {
    int choice;
    do {
        cout << "\n=== 学生菜单 ===\n";
        cout << "1. 查看我的详细信息\n";
        cout << "2. 查看所有课程设计题目\n";
        cout << "3. 查看单个课程设计题目\n";
        cout << "4. 选择设计题目\n";
        cout << "5. 查看分数和排名\n";
        cout << "6. 提交反馈\n";
        cout << "7. 退出\n";
        cout << "请选择操作：";
        cin >> choice;
        switch (choice) {
        case 1:
             Sf.viewMyDetails(studentIndex);
            break;
        case 2:
             Bf.displayAllDesignSubjects();
            break;
        case 3:
            Bf.viewDesignSubjectDetails();
            break;
        case 4:
             Sf.chooseDesignSubject();
            break;
        case 5:
            Sf.viewScoreAndRank();
            break;
        case 6:
            Sf.submitFeedback();
            break;
        case 7:
            cout << "正在退出学生菜单...\n";
            break;
        default:
            cout << "无效选择，请重新输入。\n";
        }
    } while (choice != 7);
}

void teacherMenu() {
    int choice;
    do {
        cout << "\n=== 教师菜单 ===\n";
        cout << "1. 查看所有学生信息\n";
        cout << "2. 查看所有课程设计题目信息\n";
        cout << "3. 查看单个学生信息\n"; // 
        cout << "4. 查看单个课程信息\n";//
        cout << "5. 查看本班学生信息\n";
        cout << "6. 查看学生反馈\n";
        cout << "7. 输入学生完成状况\n";
        cout << "8. 输入学生分数\n";
        cout << "9. 编辑学生记录\n";
        cout << "10. 编辑课程信息\n";
        cout << "11. 删除记录（学生信息或课程信息）\n";
        cout << "12. 统计选择同一个选题的学生信息\n";    
        cout << "13. 单个添加学生或课程信息\n";
        cout << "14. 批量添加学生信息\n";
        cout << "15. 批量添加课程设计题目信息\n";
        cout << "16. 统计学生成绩排序信息\n";
        cout << "17. 统计学生成绩平均信息\n";
        cout << "18. 退出\n";
        cout << "请选择操作：";
        cin >> choice;
        switch (choice) {
        case 1:
            Tf.displayAllStudents();
            break;
        case 2:
            Bf.displayAllDesignSubjects();
            break;
        case 3:
            Tf.queryStudent(); // 调用查询单个学生信息的功能
            break;
        case 4:
            Bf.viewDesignSubjectDetails();
            break;
        case 5:
            Tf.queryStudentsInMyClass(); // 调用查询本班学生信息的功能   //4
            break;
        case 6:
            Tf.viewStudentFeedback();
            break;
        case 7:
            Tf.inputStudentCondition();
            break;
        case 8:
            Tf.inputStudentGrade();
            break;
        case 9:
            Tf.editRecord();
            break;
        case 10:
            Tf.editDesignSubjectRecord();
            break;
        case 11:
            Tf.removeRecord();
            break;
        case 12:
            Tf.statisticBySubjectName();
            break;
        case 13:
            Tf.addRecord();
            break;
        case 14:
            Tf.batchAddStudents();
            break;
        case 15:
            Tf.batchAddDesignSubjects();
            break;      
        case 16:
            Tf.sortStudents();
            break;
        case 17:
            Tf.calculateAverage();
            break;
        case 18:
            cout << "正在退出教师菜单...\n";
            break;
        default:
            cout << "无效选择，请重新输入。\n";
        }
    } while (choice != 18);
}


int main() {
    cout << "欢迎使用课程设计管理系统\n";
    Bf.read(); // 首先读取数据
    Bf.readD();

    int enter = Bf.entry(); // 用户登录

    // 根据用户的身份（学生或老师），调用相应的菜单
    if (enter >= 0) { // 学生
        studentMenu(enter);
    }
    else if (enter >= -5 && enter <= -2) { // 老师
        teacherMenu();
    }
    else {
        cout << "未登录或选择退出。\n";
    }

    Bf.preserve(); // 保存数据
    Bf.preserveD();
    cout << "谢谢使用，再见！\n";
    return 0;
}
