#include "LineEdit.h"

LineEdit::LineEdit(int x, int y, int w, int h):BasicWidget(x,y,w,h)
{
	
}

void LineEdit::show()
{

	setfillcolor(cur_c);
	::fillroundrect(m_x, m_y, m_x + m_w, m_y + m_h, 10, 10);
	//�����־�����ʾ�ڰ�ť�м�
	settextcolor(BLACK);
	settextstyle(23, 0, "����");
	int ty = m_y + (m_h - textheight(m_text.c_str())) / 2;
	::outtextxy(m_x+5, ty, m_text.c_str());
	//����Լ������Ի���

	if (isClicked()) {
		char buf[128];
		InputBox(buf, 128, m_hittext.data(), m_title.data());
		m_text = buf;
	}
}

