#include "ctextfield.h"
#include "log.h"

CTextField::CTextField()
{
	m_buffer.reserve(STD_TF_BUF_SIZE);
	m_buffer.erase();
	m_bActive = false;
	m_iHeight = STD_TF_HEIGHT;
}

CTextField::~CTextField()
{
	// nothing to do here
}

// change this to take key codes (ints)
void CTextField::addChar(char c)
{
	if (c == '\b') {deleteChar(); return;}
	//if (c == '\n') onDeactivate(); // make this one into whatever you want
	if (c >= ' ' && c <= '~') m_buffer.append(&c, 1); // printable characters
}

void CTextField::addChar(int c)
{
	if (c == GAME_BACK) {deleteChar(); return;}
	if (c >= ' ' && c <= '~') m_buffer.append((char*)(&c), 1);
}

void CTextField::deleteChar()
{
	if (m_buffer.size() > 0)
		m_buffer.erase(m_buffer.end()-1);
}

void CTextField::onActivate()
{
	m_bActive = true;
}

void CTextField::onDeactivate()
{
	m_bActive = false;
}

void CTextField::draw()
{
	// To be implemented
	//	CLog::GetLog().Write(LOG_USER, "textfield draw");
}

void CTextField::printBuffer(int where)
{
#ifdef _DEBUG
	CLog::GetLog().Write(where, "%s", m_buffer.begin());
#endif
}