#ifndef _CTREENODE_H
#define _CTREENODE_H

//#include "main.h"
#include "CObject.h"



/*

  The tree is setup as follows:

	   (......root......)
	   /     /    \     \
	 quad1 quad2 quad3 quad4

  Where each node has up to 4 children.

  The spacial structuring of the tree consists of a root
  node which encompasses the entire world.  Each child 
  therefore contains 1/4 the area of the parent node.

  |^^^^^^^^|^^^^^^^^|
  |		   |        |
  |  Quad2 |  Quad1 |
  |        |        |
  |--------|--------|
  |		   |        |
  |  Quad3 |  Quad4 |
  |        |        |
  |--------|--------|

*/
class CTreeNode {

public:

	CTreeNode() {m_quad1 = m_quad2 = m_quad3 = m_quad4 = m_parent = NULL;};
	~CTreeNode() {};
	
	void setQuad1(CTreeNode* newQuadPtr);
	void setQuad2(CTreeNode* newQuadPtr);
	void setQuad3(CTreeNode* newQuadPtr);
	void setQuad4(CTreeNode* newQuadPtr);
	void setParent(CTreeNode* newParentPtr);
	void addObject(CObject* newObjectPtr);
	void removeObjectAt(int i);
	void setBoundingBox(Box3f &rect);
	
	int  getNumObjects();
	CObject* getObjectAt(int i);
	CTreeNode* getQuad1();
	CTreeNode* getQuad2();
	CTreeNode* getQuad3();
	CTreeNode* getQuad4();
	CTreeNode* getParent();
	Box3f* getBoundingBox();

	void importNode(FILE* fp, CObject* objects[]);

	void release();
	bool hasChildren();

private:

	vector<CObject*> m_objectList;
	CTreeNode *m_quad1, *m_quad2, *m_quad3, *m_quad4, *m_parent;

	Box3f m_box;
};

#endif
