#ifndef CWIDGET_H
#define CWIDGET_H

#define STL_USING_ALL
#include "stl.h"
#include "macros.h"
#include "log.h"

#define STD_WIDGET_WIDTH 20
#define STD_WIDGET_HEIGHT 10

// for m_iType
#define WIDGET_NONE 0
#define WIDGET_BUTTON 1
#define WIDGET_TEXT_FIELD 2
#define WIDGET_LIST 3
#define WIDGET_LABEL 4

class CWidget {
public:
	CWidget();
	~CWidget();

	virtual void onActivate()=0;
	virtual void onDeactivate()=0;
	virtual void draw()=0;

	int X() {return m_iX;}
	int Y() {return m_iY;}
	int Width() {return m_iWidth;}
	int Height() {return m_iHeight;}
	int Type() {return m_iType;}
	std::string* Name() {return &m_name;}

	void setX(int x) {m_iX = x;}
	void setY(int y) {m_iY = y;}
	void setWidth(int w) {m_iWidth = w;}
	void setHeight(int h) {m_iHeight = h;}
	void setType(int t) {m_iType = t;}
	void setName(std::string str) {m_name = str;}
	void setName(char* str) {m_name.erase(); m_name.append(str);}

protected:
	int m_iX;
	int m_iY;
	int m_iWidth;
	int m_iHeight;

	// might come in handy, but don't have to use them:
	int m_iType;
	std::string m_name;

private:

};

#endif