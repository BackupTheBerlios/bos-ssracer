#ifndef CTEXTFIELD_H
#define CTEXTFIELD_H

#include "cwidget.h"

#define STD_TF_BUF_SIZE 64
#define STD_TF_HEIGHT 10

class CTextField : public CWidget {
public:
	CTextField();
	~CTextField();

	void clearBuffer() {m_buffer.erase();}
	void addChar(char c);
	void deleteChar();

	void onActivate();
	void onDeactivate();

	bool isActive() {return m_bActive;}
	std::string* Buffer() {return &m_buffer;}
	void setActive(bool a) {m_bActive = a;}
	void toggle() {m_bActive = !m_bActive;}

protected:
	std::string m_buffer;
	bool m_bActive;

private:

};

#endif