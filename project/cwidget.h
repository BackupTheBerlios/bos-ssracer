#ifndef CWIDGET_H
#define CWIDGET_H

#define STL_USING_ALL
#include "stl.h"
#include "macros.h"
#include "log.h"
//J's edit
#include <d3d9types.h> //for color macros

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

    virtual void onSelected();
    virtual void onDeSelected();
	virtual void onActivate()=0;
	virtual void onDeactivate()=0;
	virtual void draw()=0;

    // J: XY parameters are in screen coords 
    // 0,0 = origin 
    // +1+1 = bottom left
    // -1+1 = bottom right
    // +1-1 = top left
    // -1-1 = top right
	float X() {return m_fX;}
	float Y() {return m_fY;}

    // J: scale is in the interval [0,1]
    // this adjusts automatically with screen size too

    float Width() {return m_fWidth;}
	float Height() {return m_fHeight;}
	int Type() {return m_iType;}
	std::string* Name() {return &m_name;}

	void setX(float x) {m_fX = x;}
	void setY(float y) {m_fY = y;}
	void setWidth(float w) {m_fWidth = w;}
    float getWidth() { return m_fWidth; }
	void setHeight(float h) {m_fHeight = h;}
    float getHeight() { return m_fHeight; }

	void setType(int t) {m_iType = t;}
	void setName(std::string str) {m_name = str;}
	void setName(char* str) {m_name.erase(); m_name.append(str);}

protected:
	float m_fX;
	float m_fY;
	float m_fWidth;
	float m_fHeight;
    DWORD m_dwDefaultColor; //J's edit needs a color attribute ARGB
    DWORD m_dwActiveColor;
    DWORD m_dwCurrentColor;


	// might come in handy, but don't have to use them:
	int m_iType;
	std::string m_name;

private:
    

};

#endif