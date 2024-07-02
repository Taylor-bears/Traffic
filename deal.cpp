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
        cout << "\n=== ѧ���˵� ===\n";
        cout << "1. �鿴�ҵ���ϸ��Ϣ\n";
        cout << "2. �鿴���пγ������Ŀ\n";
        cout << "3. �鿴�����γ������Ŀ\n";
        cout << "4. ѡ�������Ŀ\n";
        cout << "5. �鿴����������\n";
        cout << "6. �ύ����\n";
        cout << "7. �˳�\n";
        cout << "��ѡ�������";
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
            cout << "�����˳�ѧ���˵�...\n";
            break;
        default:
            cout << "��Чѡ�����������롣\n";
        }
    } while (choice != 7);
}

void teacherMenu() {
    int choice;
    do {
        cout << "\n=== ��ʦ�˵� ===\n";
        cout << "1. �鿴����ѧ����Ϣ\n";
        cout << "2. �鿴���пγ������Ŀ��Ϣ\n";
        cout << "3. �鿴����ѧ����Ϣ\n"; // 
        cout << "4. �鿴�����γ���Ϣ\n";//
        cout << "5. �鿴����ѧ����Ϣ\n";
        cout << "6. �鿴ѧ������\n";
        cout << "7. ����ѧ�����״��\n";
        cout << "8. ����ѧ������\n";
        cout << "9. �༭ѧ����¼\n";
        cout << "10. �༭�γ���Ϣ\n";
        cout << "11. ɾ����¼��ѧ����Ϣ��γ���Ϣ��\n";
        cout << "12. ͳ��ѡ��ͬһ��ѡ���ѧ����Ϣ\n";    
        cout << "13. �������ѧ����γ���Ϣ\n";
        cout << "14. �������ѧ����Ϣ\n";
        cout << "15. ������ӿγ������Ŀ��Ϣ\n";
        cout << "16. ͳ��ѧ���ɼ�������Ϣ\n";
        cout << "17. ͳ��ѧ���ɼ�ƽ����Ϣ\n";
        cout << "18. �˳�\n";
        cout << "��ѡ�������";
        cin >> choice;
        switch (choice) {
        case 1:
            Tf.displayAllStudents();
            break;
        case 2:
            Bf.displayAllDesignSubjects();
            break;
        case 3:
            Tf.queryStudent(); // ���ò�ѯ����ѧ����Ϣ�Ĺ���
            break;
        case 4:
            Bf.viewDesignSubjectDetails();
            break;
        case 5:
            Tf.queryStudentsInMyClass(); // ���ò�ѯ����ѧ����Ϣ�Ĺ���   //4
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
            cout << "�����˳���ʦ�˵�...\n";
            break;
        default:
            cout << "��Чѡ�����������롣\n";
        }
    } while (choice != 18);
}


int main() {
    cout << "��ӭʹ�ÿγ���ƹ���ϵͳ\n";
    Bf.read(); // ���ȶ�ȡ����
    Bf.readD();

    int enter = Bf.entry(); // �û���¼

    // �����û�����ݣ�ѧ������ʦ����������Ӧ�Ĳ˵�
    if (enter >= 0) { // ѧ��
        studentMenu(enter);
    }
    else if (enter >= -5 && enter <= -2) { // ��ʦ
        teacherMenu();
    }
    else {
        cout << "δ��¼��ѡ���˳���\n";
    }

    Bf.preserve(); // ��������
    Bf.preserveD();
    cout << "ллʹ�ã��ټ���\n";
    return 0;
}
