#include "cwidget.h"

CWidget::CWidget()
{
	m_iX = m_iY = 0;
	m_iHeight = STD_WIDGET_HEIGHT;
	m_iWidth = STD_WIDGET_WIDTH;

	m_iType = WIDGET_NONE;
	m_name.erase();
}

CWidget::~CWidget()
{
	// nothing to do here
}

