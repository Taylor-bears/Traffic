#pragma once
#include"Window.h"
#include<vector>
#include"PushButton.h"

#include"LineEdit.h"

#include<memory>
using namespace std;
class Management
{
	enum Operator {
		Addcity,
		Erasecity,
		Addvehicle,
		Erasevehicle,
		Findmessage,
		Menu=66


	 };


public:
	
	Management();

	//����������
	void run();
	int menu();
 //1,��ӳ���
	int addcity();
 //2,ɾ������
	int erasecity();
 //3,��ӽ�ͨ����
	int addvehicle();
 //4,ɾ����ͨ����
	int erasevehicle();
	
 //5,��ѯ��Ϣ
	int  findmessage();
	void drawBackground() const;
	void eventLoop();
	
private:
	IMAGE m_bk;
	std::vector<unique_ptr<PushButton>> menu_btns;
private://��ȡ�ļ�������ѧ����Ϣ
	std::string m_header;
	
private:
	//�鿴ѧ�����
	 
	std::unique_ptr<PushButton> m_caddBtn;//��ӳ��а�ť
	std::unique_ptr<LineEdit> m_caddEdit;//��ӳ��б༭��ť


	std::unique_ptr<PushButton> m_ceraseBtn;//����ɾ����ť
	std::unique_ptr<LineEdit> m_ceraseEdit;//����ɾ���༭��ť


	std::unique_ptr<PushButton> m_vaddBtn;//��ӽ�ͨ���߰�ť
	std::unique_ptr<LineEdit> m_vaddEdit;//��ӽ�ͨ���߱༭��ť


	std::unique_ptr<PushButton> m_veraseBtn;//ɾ����ͨ���߰�ť
	std::unique_ptr<LineEdit> m_veraseEdit;//ɾ����ͨ���߱༭��ť

	std::unique_ptr<PushButton> m_mfindBtn;//ɾ����ͨ���߰�ť
	std::unique_ptr<LineEdit> m_mfindEdit;//ɾ����ͨ���߱༭��ť
	







};

