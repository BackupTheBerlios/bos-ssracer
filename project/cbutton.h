#ifndef CBUTTON_H
#define CBUTTON_H

#include "cwidget.h"
//#define STL_USING_ALL
//#include "stl.h"
//Ramits MOD! DIDNT LIKE 2 STD_TEXT_SIZE
#define STD_BTEXT_SIZE 64

class CButton : public CWidget {
public:
	CButton();
	~CButton();

	void onActivate();
	void onDeactivate();
	void draw();

	bool isDown() {return m_bDown;}
	void clearText() {m_text.erase();}

	std::string* Text() {return &m_text;}

	void setText(char* text) {m_text.erase(); m_text.append(text);}
	void setDown(bool down) {m_bDown = down;}
	void toggle() {m_bDown = !m_bDown;}

protected:
	std::string m_text;
	bool m_bDown;

private:

};

#endif