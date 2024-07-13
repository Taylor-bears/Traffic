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
	::settextstyle(20, 0, "����");
	//�����水ť��ʼ��
	menu_btns.emplace_back(new PushButton("��ӳ���"));
	menu_btns.emplace_back(new PushButton("ɾ������"));
	menu_btns.emplace_back(new PushButton("��ӹ���"));
	menu_btns.emplace_back(new PushButton("ɾ������"));
	menu_btns.emplace_back(new PushButton("��ѯ��Ϣ"));
	menu_btns.emplace_back(new PushButton("�˳�ϵͳ"));
	for (int i = 0; i < menu_btns.size(); i++) {
		menu_btns[i]->SetFixedSize(250, 50);
		int bx = (Window::width() - menu_btns[i]->width()) / 2;
		int vspace = (Window::height()- menu_btns[i]->width()) / 2;
		int by = vspace+ i* menu_btns[i]->height();
		menu_btns[i]->move(bx, by);
	}
	
	
	m_caddBtn.reset(new PushButton("���",670,260,80,40));
	m_caddEdit.reset(new LineEdit(150,260,500,40));
	m_caddEdit->setTitle("�����������Ϣ");
	m_caddEdit->setHitText("�밴��\n\t<���� λ�� ���>\n��ʽ���������Ϣ");
	//��ӳ��г�ʼ��

	m_ceraseBtn.reset(new PushButton("ɾ��", 670, 260, 80, 40));
	m_ceraseEdit.reset(new LineEdit(150, 260, 500, 40));
	m_ceraseEdit->setTitle("������Ҫɾ���ĳ�������");
	m_ceraseEdit->setHitText("�밴��\n\t<���� Beijing>\n��ʽ�����������");
	//ɾ�����г�ʼ��

	m_vaddBtn.reset(new PushButton("���", 670, 260, 80, 40));
	m_vaddEdit.reset(new LineEdit(150, 260, 500, 40));
	m_vaddEdit->setTitle("�����뽻ͨ��������");
	m_vaddEdit->setHitText("�밴��\n\t<�ɻ� plane>��ʽ���뽻ͨ��������");
	//��ӽ�ͨ���߳�ʼ��

	m_veraseBtn.reset(new PushButton("ɾ��", 670, 260, 80, 40));
	m_veraseEdit.reset(new LineEdit(150, 260, 500, 40));
	m_veraseEdit->setTitle("�����뽻ͨ��������");
	m_veraseEdit->setHitText("�밴��\n\t<�ɻ� plane>��ʽ���뽻ͨ��������");
	//ɾ����ͨ���߳�ʼ��
	m_mfindBtn.reset(new PushButton("��ѯ", 670, 260, 80, 40));
	m_mfindEdit.reset(new LineEdit(150, 260, 500, 40));
	m_mfindEdit->setTitle("������������������");
	m_mfindEdit->setHitText("�밴��\n\t<���� �Ϻ�>��ʽ�����������");
	//��ѯ���ܳ�ʼ��
}

void Management::run()
{
	//��ȡ�˵��ķ���ֵ
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
			case   WM_KEYDOWN://��������
				//��ESC�˳�����������������
				if (Window::getMsg().vkcode == VK_ESCAPE)
				{
					op = Menu;
				}
				break;
			default://������
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

{//���ݰ�ť�ĵ�������ز���
	::settextstyle(20, 0, "����");
	
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
	const char* title = "������Ҫ��ӵĳ�����Ϣ<���� λ�� ���>";
	settextstyle(36, 0, "����");
	outtextxy((Window::width() - textwidth(title)) / 2, 150, title);

	m_caddBtn->show();
	m_caddEdit->show();
	
	if (m_caddBtn->isClicked()) {


		std::cout << m_caddEdit->text()<<" ��ӳɹ�" << std::endl;
		return Menu;
	}
	return 0;
}

int Management::erasecity()
{
	const char* title = "������Ҫɾ���ĳ�������";
	settextstyle(36, 0, "����");
	outtextxy((Window::width() - textwidth(title)) / 2, 150, title);

	m_ceraseBtn->show();
	m_ceraseEdit->show();
	if (m_ceraseBtn->isClicked()) {


		std::cout << m_ceraseEdit->text()<<" �ѱ�ɾ��" << std::endl;
		return Menu;
	}
	return 1;
}

int Management::addvehicle()
{
	const char* title = "������Ҫ��ӵĽ�ͨ��������";
	settextstyle(36, 0, "����");
	outtextxy((Window::width() - textwidth(title)) / 2, 150, title);

	m_vaddBtn->show();
	m_vaddEdit->show();
	if (m_vaddBtn->isClicked()) {


		std::cout << m_vaddEdit->text() << " �ѳɹ����" << std::endl;
		return Menu;
	}
	return 2;
}

int Management::erasevehicle()
{
	const char* title = "������Ҫɾ���Ľ�ͨ��������";
	settextstyle(36, 0, "����");
	outtextxy((Window::width() - textwidth(title)) / 2, 150, title);

	m_veraseBtn->show();
	m_veraseEdit->show();
	if (m_veraseBtn->isClicked()) {


		std::cout << m_veraseEdit->text() << " �ѳɹ�ɾ��" << std::endl;
		return Menu;
	}

	return 3;


}

int Management::findmessage()
{
	const char* title = "������Ҫ��ѯ�ĳ�������";
	settextstyle(36, 0, "����");
	outtextxy((Window::width() - textwidth(title)) / 2, 150, title);

	m_mfindBtn->show();
	m_mfindEdit->show();
	if (m_mfindBtn->isClicked()) {


		std::cout << m_mfindEdit->text() << " �ľ�����Ϣ����:" << std::endl;
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
	//��ӳ��а�ť��ɫ
	m_ceraseBtn->event();
	m_ceraseEdit->event();
	//ɾ�����а�ť��ɫ
	m_vaddBtn ->event();
	m_vaddEdit->event();
	//��ӽ�ͨ���߰�ť��ɫ
	m_veraseBtn->event();
	 m_veraseEdit->event();
	 //ɾ����ͨ���߰�ť��ɫ
	 m_mfindBtn->event();
	 m_mfindEdit->event();
	 //��ѯ��Ϣ��ť��ɫ

}

