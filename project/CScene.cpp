#include "WmlSphere3.h"
#include "WmlVector3.h"
#include "WmlBox3.h"
using namespace Wml;
#include "log.h"
#include "CScene.h"

bool CScene::addObject(CObject* newObject)
{
	m_sceneObjects[m_numObjects++] = newObject;
	return true;
}

void CScene::release()
{
	// free memory allocated for all the objects
	for(int i=0;i<m_numObjects;i++) {
		delete m_sceneObjects[i];
	}

	m_quadTree.release();
}

CQuadTree* CScene::getQuadTree()
{

	return &m_quadTree;
}

void CScene::importScene(char* filename, char* directory)
{
	char buf[512];
	char tempFilename[128];
	FILE* fp;

	char defaultDirectory[128] = ".\\";
	char defaultFilename[128] = "bos";
	char objectsExt[16] = ".objects";
	char mapExt[16] = ".map";
	char treeExt[16] = ".tree";

	if(strlen(directory) == 0) {
		strcpy(directory, defaultDirectory);
	}

	if(strlen(filename) == 0) {
		strcpy(filename, defaultFilename);
	}

	sprintf(tempFilename, "%s%s", filename, mapExt);
	sprintf(buf, "%s%s", directory, tempFilename);

	fp = fopen(buf, "r");

	if(!fp) {
		//cout << "Error CScene::importScene >> Unable to open file: " << buf << endl;
	}

	importMapfile(fp, filename, directory);

	fclose(fp);
}

void CScene::importMapfile(FILE* fp, char* filename, char* directory)
{
	char buf[512];
	char seps[] = " \n.";
	char* token;

	while(fgets(buf, sizeof(buf), fp)) {
		token = strtok(buf, seps);

		if(!strcmp(token, "<include>")) {
			token = strtok(NULL, seps);
			token = strtok(NULL, seps);

			if(!strcmp(token, "objects")) {
				importObjects(filename, directory);
			}
			else if(!strcmp(token, "tree")) {
				importTree(filename, directory);
			}
		}
	}


}

void CScene::importObjects(char* filename, char* directory)
{
	FILE* fp;
	char buf[512];
	char tempFilename[512];
	char* token;
	char seps[] = " \n";
	int i;

	sprintf(tempFilename, "%s.objects", filename);
	sprintf(buf, "%s%s", directory, tempFilename);

	fp = fopen(buf, "r");

	if(!fp) {
		//cout << "Error CScene::importObjects >> Unable to open file: " << buf << endl;
	}

	float temp[3];
	Box3f tempBox;
	Sphere3f tempSphere;
	CObject *newObject = NULL;

	while(fgets(buf, sizeof(buf), fp)) {
		token = strtok(buf, seps);
		if(token == NULL) {
			continue;
		}
		if(!strcmp(token, "<newObject>")) {
			newObject = new CObject;
			while(fgets(buf, sizeof(buf), fp)) {
				token = strtok(buf, seps);
				if(!strcmp(token, "<type>")) {
					token = strtok(NULL, seps);
					newObject->setType(atoi(token));
					continue;
				}
				if(!strcmp(token, "<id>")) {
					token = strtok(NULL, seps);
					newObject->setId(atoi(token));
					continue;
				}
				if(!strcmp(token, "<name>")) {
					token = strtok(NULL, seps);
					newObject->setName(token);
					continue;
				}
				if(!strcmp(token, "<translate>")) {
					for(i=0;i<3;i++) {
						token = strtok(NULL, seps);
						temp[i] = atof(token);
					}
					newObject->setTranslate(Vector3f(temp[0], temp[1], temp[2]));
					continue;
				}
				if(!strcmp(token, "<rotate>")) {
					for(i=0;i<3;i++) {
						token = strtok(NULL, seps);
						temp[i] = atof(token);
					}
					newObject->setRotate(Vector3f(temp[0], temp[1], temp[2]));
					continue;
				}
				if(!strcmp(token, "<scale>")) {
					for(i=0;i<3;i++) {
						token = strtok(NULL, seps);
						temp[i] = atof(token);
					}
					newObject->setScale(Vector3f(temp[0], temp[1], temp[2]));
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
					newObject->setBoundingBox(tempBox);
					continue;
				}
				if(!strcmp(token, "<sphereCenter>")) {
					for(i=0;i<3;i++) {
						token = strtok(NULL, seps);
						temp[i] = atof(token);
					}
					tempSphere.Center() = Vector3f(temp[0], temp[1], temp[2]);
					continue;
				}
				if(!strcmp(token, "<sphereRadius>")) {
					token = strtok(NULL, buf);
					tempSphere.Radius() = atof(token);
					newObject->setBoundingSphere(tempSphere);

					addObject(newObject);
#ifdef _DEBUG
					CLog::GetLog().Write(LOG_MISC, "<id> %d", newObject->getId());
					CLog::GetLog().Write(LOG_MISC, "<name> %s", newObject->getName());
					CLog::GetLog().Write(LOG_MISC, "<translate> %f %f %f", newObject->getTranslate().X(), newObject->getTranslate().Y(), newObject->getTranslate().Z());
					CLog::GetLog().Write(LOG_MISC, "<scale> %f %f %f", newObject->getScale().X(), newObject->getScale().Y(), newObject->getScale().Z());
					CLog::GetLog().Write(LOG_MISC, "<rotate> %f %f %f", newObject->getRotate().X(), newObject->getRotate().Y(), newObject->getRotate().Z());
					CLog::GetLog().Write(LOG_MISC, "<OBBCenter> %f %f %f", newObject->getBoundingBox().Center().X(), newObject->getBoundingBox().Center().Y(), newObject->getBoundingBox().Center().Z());
					CLog::GetLog().Write(LOG_MISC, "<OBBAxis1> %f %f %f", newObject->getBoundingBox().Axis(0).X(), newObject->getBoundingBox().Axis(0).Y(), newObject->getBoundingBox().Axis(0).Z());
					CLog::GetLog().Write(LOG_MISC, "<OBBAxis2> %f %f %f", newObject->getBoundingBox().Axis(1).X(), newObject->getBoundingBox().Axis(1).Y(), newObject->getBoundingBox().Axis(1).Z());
					CLog::GetLog().Write(LOG_MISC, "<OBBAxis3> %f %f %f", newObject->getBoundingBox().Axis(2).X(), newObject->getBoundingBox().Axis(2).Y(), newObject->getBoundingBox().Axis(2).Z());
					CLog::GetLog().Write(LOG_MISC, "<OBBExtent1> %f", newObject->getBoundingBox().Extent(0));
					CLog::GetLog().Write(LOG_MISC, "<OBBExtent2> %f", newObject->getBoundingBox().Extent(1));
					CLog::GetLog().Write(LOG_MISC, "<OBBExtent3> %f", newObject->getBoundingBox().Extent(2));
					CLog::GetLog().Write(LOG_MISC, "<sphereCenter> %f %f %f", newObject->getBoundingSphere().Center().X(), newObject->getBoundingSphere().Center().Y(), newObject->getBoundingSphere().Center().Z());
					CLog::GetLog().Write(LOG_MISC, "<sphereRadius> %f", newObject->getBoundingSphere().Radius());
#endif
					break;
				}
			}
		}
	}  //endwhile

	fclose(fp);
}


void CScene::importTree(char* filename, char* directory)
{
	FILE* fp;
	char buf[1024];
	char tempFilename[512];
	char* token;
	char seps[] = " \n";
	int i;

	sprintf(tempFilename, "%s.tree", filename);
	sprintf(buf, "%s%s", directory, tempFilename);

	fp = fopen(buf, "r");

	if(!fp) {
		//cout << "Error CScene::importTree >> Unable to open file: " << buf << endl;
	}

	fgets(buf, sizeof(buf), fp);
	fgets(buf, sizeof(buf), fp);

	m_quadTree.getRoot()->importNode(fp, m_sceneObjects);

	fclose(fp);

}