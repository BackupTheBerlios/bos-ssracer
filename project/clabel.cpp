#include "clabel.h"

CLabel::CLabel()
{
	m_text.reserve(STD_TEXT_LENGTH);
	m_text.erase();
	m_iSize = STD_TEXT_SIZE;
	m_iHeight = STD_TEXT_SIZE + 4; 
	m_iFont = FONT_NONE;
	m_iBackground_color = COLOR_NONE;
	m_iForeground_color = COLOR_BLACK;
}

CLabel::~CLabel() 
{
	// nothing to do here
}

int CLabel::setText(std::string text)
{
	m_text.erase();
	m_text = text;
	return OK;
}

int CLabel::setText(char* text)
{
	// assuming it's null terminated
	if (!text) return NULL_POINTER;
	m_text.erase();
	m_text.append(text);
	return OK;
}

int CLabel::setFont(int font) 
{
	if (font < 0) return NEGATIVE_VALUE;
	m_iFont = font;
	return OK;
}

int CLabel::setSize(int size)
{
	if (size < 0) return NEGATIVE_VALUE;
	m_iSize = size;
	return OK;
}

int CLabel::setBackgroundColor(int background_color)
{
	if (background_color < 0) return NEGATIVE_VALUE;
	m_iBackground_color = background_color;
	return OK;
}

int CLabel::setForegroundColor(int foreground_color)
{
	if (foreground_color < 0) return NEGATIVE_VALUE;
	m_iForeground_color = foreground_color;
	return OK;
}

// auto adjust heigh and width to size
int CLabel::autoAdjust()
{
	m_iHeight = m_iSize + 4;
	m_iWidth = (m_iSize + 4) * m_text.length();
	return OK;
}

void CLabel::draw()
{
	// To be implemented
	//	CLog::GetLog().Write(LOG_USER, "label draw");
}