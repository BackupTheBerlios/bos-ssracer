#ifndef CLIST_H
#define CLIST_H

#include "cwidget.h"

//#define STL_USING_ALL
//#include "stl.h" // for vectors

#define STD_LIST_SIZE 10
#define STD_LIST_ITEM_SIZE 16
#define STD_LIST_CHAR_HEIGHT 10
#define STD_LIST_CHAR_WIDTH 10

class CList : public CWidget {
public:
	CList();
	~CList();

	void onActivate();
	void onDeactivate();
	void draw();

	int addItem(char* item);
	int addItem(std::string item);
	int deleteItem(int i);
	int getNItems() {return m_items.size();}
	void clearItems() {m_items.clear();}
	int incCurItems();
	int decCurItems();
	void autoAdjust();
	void printItems(int where);

	std::vector<std::string>* Items() {return &m_items;}
	std::vector<std::string>::iterator* CurItem() {return &m_curItem;}

	int setItems(std::vector<std::string> items);
	int setCurItem(std::vector<std::string>::iterator curItem);
	int setCurItem(int i);

protected:

private:
	std::vector<std::string> m_items;
	std::vector<std::string>::iterator m_curItem;

};

#endif