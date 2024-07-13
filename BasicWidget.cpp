#include "BasicWidget.h"
#include"Window.h"
BasicWidget::BasicWidget(int x, int y, int w, int h):
	m_x(x),m_y(y),m_w(w),m_h(h)
{
}
bool BasicWidget::isin()
{

	auto& m_msg = Window::getMsg();
	if (m_msg.x >= m_x && m_msg.x < m_x + m_w && m_msg.y >= m_y && m_msg.y <= m_y + m_h) {
		return true;
	}
	return false;
}

bool BasicWidget::isClicked()
{
	if (isin()) {
		auto& m_msg = Window::getMsg();
		if (m_msg.message == WM_LBUTTONDOWN)
		{
			return true;
		}

	}
	return false;
}

int BasicWidget::width()
{
	return m_w;
}

int BasicWidget::height()
{
	return m_h;
}

void BasicWidget::SetFixedSize(int w, int h)
{
	this->m_w = w;
	this->m_h= h;
}

int BasicWidget::x()
{
	return m_x;
}

int BasicWidget::y()
{
	return m_y;
}

void BasicWidget::move(int x, int y)
{
	this->m_x = x;
	this->m_y = y;
}
void BasicWidget::event()
{

	//如果鼠标没有在按钮上
	if (!isin()) {
		cur_c = normal_c;

	}
	else {
		cur_c = hover_c;
	}
}

void BasicWidget::setBackgroundColor(COLORREF c)
{
	normal_c = c;
}

void BasicWidget::setHoverColor(COLORREF c)
{
	hover_c = c;
}
