#include "scene.h"

#include "log.h"
#include "macros.h"


//static member declarations
vector<CD3DMesh*> CScene::m_vMeshes;
vector<CEntity*> CScene::m_vEntities;


int CScene::ReleaseScene()
{
	unsigned int i;

	// Free all the meshes
	for(i=0;i<m_vMeshes.size();i++) {
		FREE(m_vMeshes[i], "Error CScene::ReleaseScene >> Attempted to delete a null pointer");
	}

	// Clear the vector of mesh pointers
	m_vMeshes.clear();

	// Free all the entities
	for(i=0;i<m_vEntities.size();i++) {
		FREE(m_vEntities[i], "Error CScene::ReleaseScene >> Attempted to delete a null pointer");
	}

	// Clear the vector of entity pointers
	m_vEntities.clear();

	// Don't forget to set the player vehicle pointer to NULL
	// Also, clean up any other pointers that use the scene
	// AI player cars would have to be set to NULL as well.
	// Can't think of anything else right now.

	return 1;
}

int CScene::LoadScene(string* directory, string* filename)
{
	char buf[512];
	char tempFilename[128];
	FILE* fp;

	char objectsExt[16] = ".objects";
	char mapExt[16] = ".map";

	string path;

	path = directory->c_str();
	path.append("\\");
	path.append(filename->c_str());
	path.append(mapExt);


	string test;

	test.assign(tempFilename);


	fp = fopen(buf, "r");

	if(!fp) {
		#ifdef _DEBUG
		CLog::GetLog().Write(LOG_MISC, "Error CScene::importScene >> Unable to open file: ");
		#endif
		return 0;
    } 
    else {
		if(!ReleaseScene()) {
			#ifdef _DEBUG
				CLog::GetLog().Write(LOG_MISC, "Error CScene::LoadScene() >> Unable to release scene");
			#endif
			return 0;
		}
	    
		if(!LoadMap(fp, filename, directory)) {
			#ifdef _DEBUG
				CLog::GetLog().Write(LOG_MISC, "Error CScene::LoadScene() >> Unable to load scene %s", buf);
			#endif
			return 0;
		}

    }

	fclose(fp);

	return 1;

}


int CScene::LoadMap(FILE* fp, string* filename, string* directory)
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
				if(!LoadEntities(filename, directory)) {
					return 0;
				}
			}

			// Add more strcmp's here for other file types
			// that the map exporter might export
			// Maybe .aiPaths, .triggers
		}
	}

	return 1;
}

int CScene::LoadEntities(string* directory, string* filename)
{
	FILE* fp;
	char buf[512];
	char* token;
	char seps[] = " \n";
	int i;
	string path;

	path = directory->c_str();
	path.append("\\");
	path.append(filename->c_str());

	fp = fopen(path.c_str(), "r");

	if(!fp) {
		#ifdef _DEBUG
		CLog::GetLog().Write(LOG_GAMECONSOLE, "Error CScene::LoadEntities() >> Unable to open file");
		#endif
		return 0;
	}

	float temp[3];
	Box3f tempBox;
	Sphere3f tempSphere;
	CEntity *newObject = NULL;

	while(fgets(buf, sizeof(buf), fp)) {
		token = strtok(buf, seps);
		if(token == NULL) {
			continue;
		}
		if(!strcmp(token, "<newObject>")) {
			//newObject = new CEntity;


			NEW(newObject, CEntity, "Error CScene::LoadEntities >> new operator failed");
			while(fgets(buf, sizeof(buf), fp)) {
				token = strtok(buf, seps);
				/*	Set the Type of the object (MAP, STATIC, DYNAMIC)
				    NOT USED AS OF YET, MIGHT NEED IT LATER
				if(!strcmp(token, "<type>")) {
					token = strtok(NULL, seps);
					newObject->setType(atoi(token));
					continue;
				}
				*/
				if(!strcmp(token, "<id>")) {
					token = strtok(NULL, seps);
					newObject->SetId(atoi(token));
					continue;
				}
				if(!strcmp(token, "<name>")) {
					token = strtok(NULL, seps);
					newObject->SetName(token);
					continue;
				}
				if(!strcmp(token, "<translate>")) {
					for(i=0;i<3;i++) {
						token = strtok(NULL, seps);
						temp[i] = float(atof(token));
					}
					newObject->SetTranslate(Vector3f(temp[0], temp[1], temp[2]));
					continue;
				}
				if(!strcmp(token, "<rotate>")) {
					for(i=0;i<3;i++) {
						token = strtok(NULL, seps);
						temp[i] = float(atof(token));
					}
					newObject->SetRotate(Vector3f(temp[0], temp[1], temp[2]));
					continue;
				}
				if(!strcmp(token, "<scale>")) {
					for(i=0;i<3;i++) {
						token = strtok(NULL, seps);
						temp[i] = float(atof(token));
					}
					newObject->SetScale(Vector3f(temp[0], temp[1], temp[2]));
					continue;
				}
				if(!strcmp(token, "<OBBCenter>")) {
					for(i=0;i<3;i++) {
						token = strtok(NULL, seps);
						temp[i] = float(atof(token));
					}
					tempBox.Center() = Vector3f(temp[0], temp[1], temp[2]);
					continue;
				}
				if(!strcmp(token, "<OBBAxis1>")) {
					for(i=0;i<3;i++) {
						token = strtok(NULL, seps);
						temp[i] = float(atof(token));
					}
					tempBox.Axis(0) = Vector3f(temp[0], temp[1], temp[2]);
					continue;
				}
				if(!strcmp(token, "<OBBAxis2>")) {
					for(i=0;i<3;i++) {
						token = strtok(NULL, seps);
						temp[i] = float(atof(token));
					}
					tempBox.Axis(1) = Vector3f(temp[0], temp[1], temp[2]);
					continue;
				}
				if(!strcmp(token, "<OBBAxis3>")) {
					for(i=0;i<3;i++) {
						token = strtok(NULL, seps);
						temp[i] = float(atof(token));
					}
					tempBox.Axis(2) = Vector3f(temp[0], temp[1], temp[2]);
					continue;
				}
				if(!strcmp(token, "<OBBExtent1>")) {
					token = strtok(NULL, seps);
					tempBox.Extent(0) = float(atof(token));
					continue;
				}
				if(!strcmp(token, "<OBBExtent2>")) {
					token = strtok(NULL, seps);
					tempBox.Extent(1) = float(atof(token));
					continue;
				}
				if(!strcmp(token, "<OBBExtent3>")) {
					token = strtok(NULL, seps);
					tempBox.Extent(2) = float(atof(token));
					newObject->SetBoundingBox(tempBox);
					continue;
				}
				if(!strcmp(token, "<sphereCenter>")) {
					for(i=0;i<3;i++) {
						token = strtok(NULL, seps);
						temp[i] = float(atof(token));
					}
					tempSphere.Center() = Vector3f(temp[0], temp[1], temp[2]);
					continue;
				}
				if(!strcmp(token, "<sphereRadius>")) {
					token = strtok(NULL, buf);
					tempSphere.Radius() = float(atof(token));
					newObject->SetBoundingSphere(tempSphere);

					m_vEntities.push_back(newObject);
					break;
				}

                    /*
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
					*/
			}
		}
	}  //endwhile

	fclose(fp);

	return 1;
}

int CScene::LoadPlayerVehicle(string* directory, string* filename)
{
	FILE* fp;
	char path[1024];
	char buf[1024];
	char* token;
	char seps[] = " \t\n";
//	CPlayerVehicle* newCar;
	float temp[3];

	sprintf(path, "%s\\%s", directory, filename);

	fp = fopen(path, "r");

	if(!fp) {
		return 0;
	}
/*
	newCar = new CPlayerVehicle;

	while(fgets(buf, sizeof(buf), fp)) {
		token = strtok(buf, seps);

		if(!strcmp(token, "<bodyMesh>")) {
			token = strtok(NULL, seps);
				newCar->setName(token);
				continue;
		}
		else if(!strcmp(token, "<wheelMesh>")) {
			token = strtok(NULL, seps);
			for(int i=0;i<4;i++) {
				newCar->getTires()[i].setName(token);
			}
			continue;
		}
		else if(!strcmp(token, "<FLWheelTrans>")) {
			for(int i=0;i<3;i++) {
				token = strtok(NULL, seps);
				temp[i] = float(atof(token));
			}
			newCar->getTires()[FLWHEEL].setLocalPos(Vector3f(temp[0], temp[1], temp[2]));
			newCar->getTires()[FRWHEEL].setLocalPos(Vector3f(-temp[0], temp[1], temp[2]));
			continue;
		}
		else if(!strcmp(token, "<FLWheelScale>")) {
			for(int i=0;i<3;i++) {
				token = strtok(NULL, seps);
				temp[i] = float(atof(token));
			}
			newCar->getTires()[FLWHEEL].setScale(Vector3f(temp[0], temp[1], temp[2]));
			newCar->getTires()[FRWHEEL].setScale(Vector3f(temp[0], temp[1], temp[2]));
			continue;
		}
		else if(!strcmp(token, "<BLWheelTrans>")) {
			for(int i=0;i<3;i++) {
				token = strtok(NULL, seps);
				temp[i] = float(atof(token));
			}
			newCar->getTires()[BLWHEEL].setLocalPos(Vector3f(temp[0], temp[1], temp[2]));
			newCar->getTires()[BRWHEEL].setLocalPos(Vector3f(-temp[0], temp[1], temp[2]));
			continue;
		}
		else if(!strcmp(token, "<BLWheelScale>")) {
			for(int i=0;i<3;i++) {
				token = strtok(NULL, seps);
				temp[i] = float(atof(token));
			}
			newCar->getTires()[BLWHEEL].setScale(Vector3f(temp[0], temp[1], temp[2]));
			newCar->getTires()[BRWHEEL].setScale(Vector3f(temp[0], temp[1], temp[2]));
			continue;
		}
		else if(!strcmp(token, "<CarTrans>")) {
			for(int i=0;i<3;i++) {
				token = strtok(NULL, seps);
				temp[i] = float(atof(token));
			}
			newCar->setTranslate(Vector3f(temp[0], temp[1], temp[2]));  //$$$$$$$
		}
	}

	Vector3f test = newCar->getTranslate();
	for(int i=0;i<4;i++) {
		Vector3f test1 = newCar->getTires()[i].getLocalPos();
		if(i ==0 || i == 1) {
			newCar->getTires()[i].setRotate(Vector3f(90.0f, 0.0f, 0.0f));
		}
		newCar->getTires()[i].setTranslate(newCar->getTranslate() + newCar->getTires()[i].getLocalPos());
	}

	// Add the vehicle to the objects list
	addObject((CObject*)newCar);
	newCar->initCarPhysics();
	CPhysics::GetPhysicsPtr()->setPlayerVehicle(newCar);

    // Add the Tires to the objects list
	addObject( ((CObject *)(&newCar->getTire(0))) );
    addObject( ((CObject *)(&newCar->getTire(1))) );
    addObject( ((CObject *)(&newCar->getTire(2))) );
    addObject( ((CObject *)(&newCar->getTire(3))) );

  */


	return 1;
}

int CScene::LoadEntity(string* directory, string* filename)
{
	CEntity* newEntity;
	string path;
	char temp[128];

/*	
    do your own file checking here,  I check for the .x file when I load it
    // Construct the path of the filename
	path = directory->c_str();
	path.append("\\");
	path.append(filename->c_str());
	path.append(".x");

	FILE* fp = fopen(path.c_str(), "r");

	// Check to see if we can open the file for reading
	if(!fp) {
		CLog::GetLog().Write(LOG_MISC, "Error CScene::LoadEntity >> Unable to open file for reading");
		return 0;
	}
*/
	// Allocate memory for the entity
	NEW(newEntity, CEntity, "Error CScene::LoadEntity() >> new operator failed");


	strcpy(temp, filename->c_str());
	newEntity->SetName(temp);
	newEntity->SetId(m_vEntities.size());
	newEntity->SetTranslate(Vector3f(0.0f, 0.0f, 0.0f));
	newEntity->SetScale(Vector3f(1.0f, 1.0f, 1.0f));
	newEntity->SetRotate(Vector3f(0.0f, 0.0f, 0.0f));

	if(!newEntity->LoadMesh()) {
		CLog::GetLog().Write(LOG_MISC, "Error CScene::LoadEntity() >> Error loading mesh");
		FREE(newEntity, "Error CScene::LoadIdentity() >> Error releasing memory");
		return 0;
	}

	// Calculate Bounding Box, and Bounding Sphere

	// Everything went ok, so now add the entity to the scene
	m_vEntities.push_back(newEntity);
	m_vMeshes.push_back(newEntity->GetMesh());
	return 1;
}