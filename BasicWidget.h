#pragma once
#include<Easyx.h>
class BasicWidget
{public:
	BasicWidget(int x, int y, int w, int h);
	virtual ~BasicWidget() {};
	int width();
	int height();
	void SetFixedSize(int w, int h);
	int x();
	int y();
	void move(int x, int y);
	virtual void show() = 0;
	virtual void event() ;
	bool isin();//�ж�����Ƿ��ڵ�ǰ��ť��
	bool isClicked();//�ж�����Ƿ����˵�ǰ��ť

	void setBackgroundColor(COLORREF c);
	void setHoverColor(COLORREF c);
protected:
	int m_x;
	int m_y;
	int m_w;
	int m_h;
	COLORREF cur_c = RGB(232, 232, 236);
	COLORREF normal_c = RGB(232, 232, 236);
	COLORREF hover_c = RED;
};

