#ifndef _CQUADTREE_H
#define _CQUADTREE_H

//#include "main.h"


#include "CTreeNode.h"

#define STL_USING_ALL
#include "stl.h"
using namespace std;


// Maximum number of objects allowed in the map
#define MAX_OBJECTS				1024


using namespace Wml;



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

class CQuadTree {

public:

	CQuadTree() {};
	~CQuadTree() {};
	CTreeNode* getRoot();
	void constructTree(CObject *objectList[MAX_OBJECTS], int numObjects);
	void printTree();
	void release();

private:

	void placeObjectsInTree(CTreeNode* parentNode);

	CTreeNode m_root;

};



#endif