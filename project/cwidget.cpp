#include "cwidget.h"

CWidget::CWidget()
{
	m_fX = m_fY = 0;
	m_fHeight = STD_WIDGET_HEIGHT;
	m_fWidth = STD_WIDGET_WIDTH;

	m_iType = WIDGET_NONE;
    m_dwDefaultColor = D3DCOLOR_ARGB(255,255,255,255);  // J:white 
    m_dwActiveColor = D3DCOLOR_ARGB(255,255,0,0);     // J:red
    m_dwCurrentColor = m_dwDefaultColor;
	m_name.erase();
}

CWidget::~CWidget()
{
	// nothing to do here
}

