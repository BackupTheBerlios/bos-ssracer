#include "CTreeNode.h"
void CTreeNode::setQuad1(CTreeNode *newQuadPtr)
{
	m_quad1 = newQuadPtr;
}

void CTreeNode::setQuad2(CTreeNode *newQuadPtr)
{
	m_quad2 = newQuadPtr;
}

void CTreeNode::setQuad3(CTreeNode *newQuadPtr)
{
	m_quad3 = newQuadPtr;
}

void CTreeNode::setQuad4(CTreeNode *newQuadPtr)
{
	m_quad4 = newQuadPtr;
}

void CTreeNode::setParent(CTreeNode *newParentPtr)
{
	m_parent = newParentPtr;
}

void CTreeNode::addObject(CObject* newObjectPtr)
{
	m_objectList.push_back(newObjectPtr);
}

int CTreeNode::getNumObjects()
{
	return m_objectList.size();
}

CObject* CTreeNode::getObjectAt(int i)
{
	return m_objectList[i];
}

CTreeNode* CTreeNode::getQuad1()
{
	return m_quad1;
}

CTreeNode* CTreeNode::getQuad2()
{
	return m_quad2;
}

CTreeNode* CTreeNode::getQuad3()
{
	return m_quad3;
}

CTreeNode* CTreeNode::getQuad4()
{
	return m_quad4;
}

CTreeNode* CTreeNode::getParent()
{
	return m_parent;
}

void CTreeNode::removeObjectAt(int i)
{
	m_objectList.erase(m_objectList.begin() + i);
}

bool CTreeNode::hasChildren()
{
	if(m_quad1 == NULL && m_quad2 == NULL &&
	   m_quad3 == NULL && m_quad4 == NULL) {
		return false;
	}
	else {
		return true;
	}
}

void CTreeNode::release()
{
	if(!m_quad1->hasChildren()) {
			delete m_quad1;
			m_quad1 = NULL;
	}
	else {
		m_quad1->release();
		delete m_quad1;
		m_quad1 = NULL;
	}

	if(!m_quad2->hasChildren()) {
			delete m_quad2;
			m_quad2 = NULL;
	}
	else {
		m_quad2->release();
		delete m_quad2;
		m_quad1 = NULL;
	}

	if(!m_quad3->hasChildren()) {
			delete m_quad3;
			m_quad3 = NULL;
	}
	else {
		m_quad3->release();
		delete m_quad3;
		m_quad3 = NULL;
	}

	if(!m_quad4->hasChildren()) {
			delete m_quad4;
			m_quad4 = NULL;
	}
	else {
		m_quad4->release();
		delete m_quad4;
		m_quad4 = NULL;
	}

	return;	
}


void CTreeNode::setBoundingBox(Box3f &rect)
{
	m_box = rect;

}

Box3f* CTreeNode::getBoundingBox()
{
	return &m_box;
}

void CTreeNode::importNode(FILE* fp, CObject* objects[])
{
	char buf[1024];
	char seps[] = " \n\t";
	char* token;
	int numChildrenRead = 0;
	int i;
	float temp[3];
	Box3f tempBox;


	while(fgets(buf, sizeof(buf), fp)) {
		token = strtok(buf, seps);
		if(token == NULL) {
			continue;
		}
		if(!strcmp(token, "}")) {
			return;
		}
		if(!strcmp(token, "<newNode>")) {
			fgets(buf, sizeof(buf), fp);
			switch(numChildrenRead) {

			case 0:
				m_quad1 = new CTreeNode;
				m_quad1->importNode(fp, objects);
				numChildrenRead++;
				break;

			case 1:
				m_quad2 = new CTreeNode;
				m_quad2->importNode(fp, objects);
				numChildrenRead++;
				break;

			case 2:
				m_quad3 = new CTreeNode;
				m_quad3->importNode(fp, objects);
				numChildrenRead++;
				break;

			case 3:
				m_quad4 = new CTreeNode;
				m_quad4->importNode(fp, objects);
				numChildrenRead++;
				break;
			};
		}
		if(!strcmp(token, "<objectIDs>")) {
			token = strtok(NULL, seps);
			while(token != NULL) {
				m_objectList.push_back(objects[atoi(token)]);
				token = strtok(NULL, seps);
			}
			continue;
		}
		if(!strcmp(token, "<OBBCenter>")) {
			for(i=0;i<3;i++) {
				token = strtok(NULL, seps);
				temp[i] = atof(token);
			}
			tempBox.Center() = Vector3f(temp[0], temp[1], temp[2]);
			continue;
		}
		if(!strcmp(token, "<OBBAxis1>")) {
			for(i=0;i<3;i++) {
				token = strtok(NULL, seps);
				temp[i] = atof(token);
			}
			tempBox.Axis(0) = Vector3f(temp[0], temp[1], temp[2]);
			continue;
		}
		if(!strcmp(token, "<OBBAxis2>")) {
			for(i=0;i<3;i++) {
				token = strtok(NULL, seps);
				temp[i] = atof(token);
			}
			tempBox.Axis(1) = Vector3f(temp[0], temp[1], temp[2]);
			continue;
		}
		if(!strcmp(token, "<OBBAxis3>")) {
			for(i=0;i<3;i++) {
				token = strtok(NULL, seps);
				temp[i] = atof(token);
			}
			tempBox.Axis(2) = Vector3f(temp[0], temp[1], temp[2]);
			continue;
		}
		if(!strcmp(token, "<OBBExtent1>")) {
			token = strtok(NULL, seps);
			tempBox.Extent(0) = atof(token);
			continue;
		}
		if(!strcmp(token, "<OBBExtent2>")) {
			token = strtok(NULL, seps);
			tempBox.Extent(1) = atof(token);
			continue;
		}
		if(!strcmp(token, "<OBBExtent3>")) {
			token = strtok(NULL, seps);
			tempBox.Extent(2) = atof(token);
			m_box = tempBox;
			continue;
		}
	} //endwhile
}