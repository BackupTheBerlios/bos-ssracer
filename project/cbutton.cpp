#include "cbutton.h"
#include "log.h"

CButton::CButton()
{
	m_text.reserve(STD_TEXT_SIZE);
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
}

void CButton::onDeactivate()
{
	m_bDown = false;
}