#ifndef _CSCENE_H
#define _CSCENE_H

//#include "main.h"
#include "CObject.h"
#include "CQuadTree.h"


#include <stdio.h>

#define STL_USING_ALL
#include "stl.h"
using namespace std;


using namespace Wml;

class CScene {

public:
	CScene() { m_numObjects = 0; };
	~CScene() {};
	bool addObject(CObject* newObject);
	CQuadTree* getQuadTree();
	void release();
	void importScene(char* filename, char* directory);
	int GetNumObjects() { return m_numObjects; } ;
	CObject * GetObject(int i)  { return m_sceneObjects[i]; };
	
private:

	void importMapfile(FILE* fp, char* filename, char* directory);
	void importObjects(char* filename, char* directory);
	void importTree(char* filename, char* directory);
	
	
	CObject *m_sceneObjects[MAX_OBJECTS];
	int m_numObjects;
	CQuadTree m_quadTree;

};

#endif