#include "PushButton.h"

PushButton::PushButton(const std::string& text, int x, int y, int w, int h):
	BasicWidget(x,y,w,h),m_text(text)
{
}

void PushButton::show()
{ 
	setfillcolor(cur_c);
	::fillroundrect(m_x, m_y, m_x + m_w, m_y + m_h, 10, 10);
	//�����־�����ʾ�ڰ�ť�м�
	settextcolor(BLACK);
	int tx = m_x + (m_w - textwidth(m_text.c_str())) / 2;
	int ty= m_y + (m_h - textheight(m_text.c_str())) / 2;
	::outtextxy(tx, ty, m_text.c_str());
}



