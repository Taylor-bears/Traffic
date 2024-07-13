#include "Management.h"

#include<iostream>





using namespace std;

//addcity,
//erasecity,
//addvehicle,
//erasevehicle,
//findmessage,

Management::Management()
{
	
	::loadimage(&m_bk, "./images/bk.jpg", Window::width(), Window::height());
	::settextstyle(20, 0, "宋体");
	//主界面按钮初始化
	menu_btns.emplace_back(new PushButton("添加城市"));
	menu_btns.emplace_back(new PushButton("删除城市"));
	menu_btns.emplace_back(new PushButton("添加工具"));
	menu_btns.emplace_back(new PushButton("删除工具"));
	menu_btns.emplace_back(new PushButton("查询信息"));
	menu_btns.emplace_back(new PushButton("退出系统"));
	for (int i = 0; i < menu_btns.size(); i++) {
		menu_btns[i]->SetFixedSize(250, 50);
		int bx = (Window::width() - menu_btns[i]->width()) / 2;
		int vspace = (Window::height()- menu_btns[i]->width()) / 2;
		int by = vspace+ i* menu_btns[i]->height();
		menu_btns[i]->move(bx, by);
	}
	
	
	m_caddBtn.reset(new PushButton("添加",670,260,80,40));
	m_caddEdit.reset(new LineEdit(150,260,500,40));
	m_caddEdit->setTitle("请输入城市信息");
	m_caddEdit->setHitText("请按照\n\t<名称 位置 面积>\n格式输入城市信息");
	//添加城市初始化

	m_ceraseBtn.reset(new PushButton("删除", 670, 260, 80, 40));
	m_ceraseEdit.reset(new LineEdit(150, 260, 500, 40));
	m_ceraseEdit->setTitle("请输入要删除的城市名字");
	m_ceraseEdit->setHitText("请按照\n\t<北京 Beijing>\n格式输入城市名字");
	//删除城市初始化

	m_vaddBtn.reset(new PushButton("添加", 670, 260, 80, 40));
	m_vaddEdit.reset(new LineEdit(150, 260, 500, 40));
	m_vaddEdit->setTitle("请输入交通工具名称");
	m_vaddEdit->setHitText("请按照\n\t<飞机 plane>格式输入交通工具名字");
	//添加交通工具初始化

	m_veraseBtn.reset(new PushButton("删除", 670, 260, 80, 40));
	m_veraseEdit.reset(new LineEdit(150, 260, 500, 40));
	m_veraseEdit->setTitle("请输入交通工具名称");
	m_veraseEdit->setHitText("请按照\n\t<飞机 plane>格式输入交通工具名字");
	//删除交通工具初始化
	m_mfindBtn.reset(new PushButton("查询", 670, 260, 80, 40));
	m_mfindEdit.reset(new LineEdit(150, 260, 500, 40));
	m_mfindEdit->setTitle("请输入两个城市名称");
	m_mfindEdit->setHitText("请按照\n\t<北京 上海>格式输入城市名字");
	//查询功能初始化
}

void Management::run()
{
	//获取菜单的返回值
	 int op = Menu;
	Window::beginDraw();

	while (true)
	{
		Window::clear();
		drawBackground();
		eventLoop();
		if (Window::hasMsg())
		{


			switch (Window::getMsg().message) {
			case   WM_KEYDOWN://按键按下
				//按ESC退出操作，返回主界面
				if (Window::getMsg().vkcode == VK_ESCAPE)
				{
					op = Menu;
				}
				break;
			default://鼠标操作
				eventLoop();
				break;
			}

		}



		switch (op)
		{
		case Menu:
			op = menu();
			break;
		case Management::Addcity:

			 op = addcity();
		

			break;
		case Management:: Erasecity:
			op= erasecity();
			break;
		case Management::Addvehicle:
			op= addvehicle();
			break;
		case Management::Erasevehicle:
			op= erasevehicle();
			break;
		case Management::Findmessage:
			op= findmessage();
			break;
		default:
			
			exit(666);
			break;

		}
		Window::flushDraw();
		Window::getMsg().message = { 0 };
		

	}Window::endDraw();
}

int Management::menu()

{//根据按钮的点击，返回操作
	::settextstyle(20, 0, "宋体");
	
	for (int i = 0; i < menu_btns.size(); i++) {
		menu_btns[i]->show();
		menu_btns[i]->event();
		if (menu_btns[i]->isClicked()) {
			return i;


		}
	}
	return Menu;
}

int Management::addcity()
{
	const char* title = "请输入要添加的城市信息<名字 位置 面积>";
	settextstyle(36, 0, "宋体");
	outtextxy((Window::width() - textwidth(title)) / 2, 150, title);

	m_caddBtn->show();
	m_caddEdit->show();
	
	if (m_caddBtn->isClicked()) {


		std::cout << m_caddEdit->text()<<" 添加成功" << std::endl;
		return Menu;
	}
	return 0;
}

int Management::erasecity()
{
	const char* title = "请输入要删除的城市名称";
	settextstyle(36, 0, "宋体");
	outtextxy((Window::width() - textwidth(title)) / 2, 150, title);

	m_ceraseBtn->show();
	m_ceraseEdit->show();
	if (m_ceraseBtn->isClicked()) {


		std::cout << m_ceraseEdit->text()<<" 已被删除" << std::endl;
		return Menu;
	}
	return 1;
}

int Management::addvehicle()
{
	const char* title = "请输入要添加的交通工具名称";
	settextstyle(36, 0, "宋体");
	outtextxy((Window::width() - textwidth(title)) / 2, 150, title);

	m_vaddBtn->show();
	m_vaddEdit->show();
	if (m_vaddBtn->isClicked()) {


		std::cout << m_vaddEdit->text() << " 已成功添加" << std::endl;
		return Menu;
	}
	return 2;
}

int Management::erasevehicle()
{
	const char* title = "请输入要删除的交通工具名称";
	settextstyle(36, 0, "宋体");
	outtextxy((Window::width() - textwidth(title)) / 2, 150, title);

	m_veraseBtn->show();
	m_veraseEdit->show();
	if (m_veraseBtn->isClicked()) {


		std::cout << m_veraseEdit->text() << " 已成功删除" << std::endl;
		return Menu;
	}

	return 3;


}

int Management::findmessage()
{
	const char* title = "请输入要查询的城市名称";
	settextstyle(36, 0, "宋体");
	outtextxy((Window::width() - textwidth(title)) / 2, 150, title);

	m_mfindBtn->show();
	m_mfindEdit->show();
	if (m_mfindBtn->isClicked()) {


		std::cout << m_mfindEdit->text() << " 的具体信息如下:" << std::endl;
		return Menu;
	}
	return 4;
}

void Management::drawBackground() const
{
	::putimage(0, 0, &m_bk);
}

void Management::eventLoop()
{
	
	m_caddBtn->event();
	m_caddEdit->event();
	//添加城市按钮变色
	m_ceraseBtn->event();
	m_ceraseEdit->event();
	//删除城市按钮变色
	m_vaddBtn ->event();
	m_vaddEdit->event();
	//添加交通工具按钮变色
	m_veraseBtn->event();
	 m_veraseEdit->event();
	 //删除交通工具按钮变色
	 m_mfindBtn->event();
	 m_mfindEdit->event();
	 //查询信息按钮变色

}

