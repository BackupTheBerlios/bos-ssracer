#ifndef CLABEL_H
#define CLABEL_H

#include "cwidget.h"

// for m_text
#define STD_TEXT_SIZE 10
#define STD_TEXT_LENGTH 64

// for m_iFont
#define FONT_NONE 0
#define FONT_ARIAL 1
#define FONT_COURIER 2
#define FONT_TIMES_NEW_ROMAN 3
#define FONT_SYSTEM 4
#define FONT_VERDANA 5
#define MAX_FONTS 5

// for m_iBackground_color & m_iForeground_color
#define COLOR_NONE 0
#define COLOR_BLACK 1
#define COLOR_WHITE 2
#define COLOR_RED 3
#define COLOR_BLUE 4
#define COLOR_GREEN 5
#define COLOR_YELLOW 6
#define COLOR_ORANGE 7
#define COLOR_VIOLET 8
#define COLOR_GRAY 9
#define COLOR_BROWN 10
#define COLOR_TIRQUOID 11
#define COLOR_PINK 12

class CLabel : public CWidget {
public:
	CLabel();
	~CLabel();

	int autoAdjust();
	void clearText() {m_text.erase();}

	// can't really activate a label
	void onActivate() {}
	void onDeactivate() {}

	int setText(std::string text);
	int setText(char* text);
	int setFont(int font);
	int setSize(int size);
	int setBackgroundColor(int background_color);
	int setForegroundColor(int foreground_color);

	std::string* Text() {return &m_text;}
	int Font() {return m_iFont;}
	int Size() {return m_iSize;}
	int BackgroundColor() {return m_iBackground_color;}
	int ForegroundColor() {return m_iForeground_color;}

protected:
	std::string m_text;
	int m_iFont;
	int m_iSize;
	int m_iBackground_color;
	int m_iForeground_color;

private:

};

#endif