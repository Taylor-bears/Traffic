#include "LineEdit.h"

LineEdit::LineEdit(int x, int y, int w, int h):BasicWidget(x,y,w,h)
{
	
}

void LineEdit::show()
{

	setfillcolor(cur_c);
	::fillroundrect(m_x, m_y, m_x + m_w, m_y + m_h, 10, 10);
	//把文字居中显示在按钮中间
	settextcolor(BLACK);
	settextstyle(23, 0, "楷体");
	int ty = m_y + (m_h - textheight(m_text.c_str())) / 2;
	::outtextxy(m_x+5, ty, m_text.c_str());
	//点击自己弹出对话框

	if (isClicked()) {
		char buf[128];
		InputBox(buf, 128, m_hittext.data(), m_title.data());
		m_text = buf;
	}
}

