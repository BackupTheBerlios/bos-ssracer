#include "CQuadTree.h"

CTreeNode* CQuadTree::getRoot()
{
	return &m_root;
}

void CQuadTree::release()
{
	m_root.release();
}
