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

	//启动管理类
	void run();
	int menu();
 //1,添加城市
	int addcity();
 //2,删除城市
	int erasecity();
 //3,添加交通工具
	int addvehicle();
 //4,删除交通工具
	int erasevehicle();
	
 //5,查询信息
	int  findmessage();
	void drawBackground() const;
	void eventLoop();
	
private:
	IMAGE m_bk;
	std::vector<unique_ptr<PushButton>> menu_btns;
private://读取文件，保存学生信息
	std::string m_header;
	
private:
	//查看学生表格
	 
	std::unique_ptr<PushButton> m_caddBtn;//添加城市按钮
	std::unique_ptr<LineEdit> m_caddEdit;//添加城市编辑按钮


	std::unique_ptr<PushButton> m_ceraseBtn;//城市删除按钮
	std::unique_ptr<LineEdit> m_ceraseEdit;//城市删除编辑按钮


	std::unique_ptr<PushButton> m_vaddBtn;//添加交通工具按钮
	std::unique_ptr<LineEdit> m_vaddEdit;//添加交通工具编辑按钮


	std::unique_ptr<PushButton> m_veraseBtn;//删除交通工具按钮
	std::unique_ptr<LineEdit> m_veraseEdit;//删除交通工具编辑按钮

	std::unique_ptr<PushButton> m_mfindBtn;//删除交通工具按钮
	std::unique_ptr<LineEdit> m_mfindEdit;//删除交通工具编辑按钮
	







};

