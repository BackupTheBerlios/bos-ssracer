#include "cbutton.h"
#include "log.h"
#include "renderer.h"

CButton::CButton()
{
	m_text.reserve(STD_BTEXT_SIZE);
	m_text.erase();
	m_text.append("Click Me!");
	m_bDown = false;
}

CButton::~CButton()
{
// nothing to do here	
}

void CButton::onActivate()
{
	m_bDown = true;
    m_dwCurrentColor = m_dwActiveColor;  // set color
}

void CButton::onDeactivate()
{
	m_bDown = false;
    m_dwCurrentColor = m_dwDefaultColor;  // reset color

}

void CButton::draw()
{
    //$$$TEMp draw static text for now
    //CRenderer::GetRendererPtr()->Draw3DTextScaled(-0.9,-0.9,0,D3DCOLOR_ARGB(255,255,0,0), "Quit", 0.1, 0.1);
    CRenderer::GetRendererPtr()->Draw3DTextScaled(m_fX,m_fY,0,m_dwCurrentColor, (char *)m_text.data(), 0.1, 0.1);
}