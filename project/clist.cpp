#include "clist.h"

CList::CList()
{
	m_items.reserve(STD_LIST_ITEM_SIZE);
	m_items.clear();
	m_curItem = NULL;
}

CList::~CList()
{
	// nothing to do here
}

void CList::onActivate()
{
	// if we knew which item was clicked, we'd set m_curItem to it.
}

void CList::onDeactivate()
{
	m_curItem = NULL;
}

int CList::addItem(char* item)
{
	// assuming item is null terminated
	if (!item) return NULL_POINTER;
	m_items.push_back(item);
	return OK;
}

int CList::addItem(std::string item)
{
	m_items.push_back(item);
	return OK;
}

int CList::deleteItem(int i)
{
	if (i < 0 || i >= m_items.size())
		return INDEX_OUT_OF_RANGE;

	// first, adjust curItem
	std::vector<std::string>::iterator it = &m_items[i];
	if (m_curItem >= it) {
		if (m_curItem > m_items.begin())
			m_curItem--;
		else m_curItem = NULL;
	}

	m_items.erase(it);
	return OK;
}

int CList::incCurItems()
{
	if (m_curItem != m_items.end()-1 && m_curItem != 0)
		m_curItem++;
	return OK;
}

int CList::decCurItems()
{
	if (m_curItem != m_items.begin() && m_curItem != 0)
		m_curItem--;
	return OK;
}

int CList::setItems(std::vector<std::string> items)
{
	m_items.clear();
	m_items = items;
	m_curItem = 0;
	return OK;
}

int CList::setCurItem(std::vector<std::string>::iterator curItem)
{
	if (curItem < m_items.begin() || curItem >= m_items.end())
		return INDEX_OUT_OF_RANGE;
	m_curItem = curItem;
}

int CList::setCurItem(int i) 
{
	if (i < 0 || i >= m_items.size())
		return INDEX_OUT_OF_RANGE;
	m_curItem = &m_items[i];
}

void CList::autoAdjust()
{
	int h = m_items.size();
	int w = 0;

	for (int i = 0; i < h; i++)
		if (m_items[i].size() > w) w = m_items[i].size();

	m_iHeight = h*(STD_LIST_CHAR_HEIGHT + 4); 
	m_iWidth = w*(STD_LIST_CHAR_WIDTH + 4);
}

void CList::printItems(int where)
{
	for (int i = 0; i < m_items.size(); i++)
		CLog::GetLog().Write(where, "%s", m_items[i].begin());
}

void CList::draw()
{
	// To be implemented
	//	CLog::GetLog().Write(LOG_USER, "list draw");
}