#include "scene.h"

#include "log.h"
#include "vehicle.h"
#include "gamestatemanager.h"
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
	string path;
	char buf[1024];
	char* token;
	char seps[] = " \t\n";
	CVehicle* newCar;
	float temp[6];

	path.assign(directory->c_str());
	path.append(filename->c_str());

	fp = fopen(path.c_str(), "r");

	if(!fp) {
		return 0;
	}

	newCar = new CVehicle;

	while(fgets(buf, sizeof(buf), fp)) {
		token = strtok(buf, seps);

		if(token == NULL) {
			continue;
		}

		if(!strcmp(token, "<BodyMesh>")) {
			token = strtok(NULL, seps);
			newCar->SetName(token);
			continue;
		}
		else if(!strcmp(token, "<WheelMesh>")) {
			token = strtok(NULL, seps);
			for(int i=0;i<4;i++) {
				newCar->GetTire(i)->SetName(token);
			}
			continue;
		}
		else if(!strcmp(token, "<FRTireTrans>")) {
			for(int i=0;i<3;i++) {
				token = strtok(NULL, seps);
				temp[i] = float(atof(token));
			}
			newCar->GetTire(FRTIRE)->SetPositionLC(Vector3f(temp[0], temp[1], temp[2]));
			newCar->GetTire(FLTIRE)->SetPositionLC(Vector3f(temp[0], -temp[1], temp[2]));
			newCar->GetTire(FLTIRE)->SetRotationLC(Vector3f(0.0f, 180.0f, 0.0f));
			continue;
		}
		/*
		else if(!strcmp(token, "<FRWheelScale>")) {
			for(int i=0;i<3;i++) {
				token = strtok(NULL, seps);
				temp[i] = float(atof(token));
			}
			newCar->getTires()[FLWHEEL].setScale(Vector3f(temp[0], temp[1], temp[2]));
			newCar->getTires()[FRWHEEL].setScale(Vector3f(temp[0], temp[1], temp[2]));
			continue;
		} */
		else if(!strcmp(token, "<RRTireTrans>")) {
			for(int i=0;i<3;i++) {
				token = strtok(NULL, seps);
				temp[i] = float(atof(token));
			}
			newCar->GetTire(RRTIRE)->SetPositionLC(Vector3f(temp[0], temp[1], temp[2]));
			newCar->GetTire(RLTIRE)->SetPositionLC(Vector3f(temp[0], -temp[1], temp[2]));
			newCar->GetTire(RLTIRE)->SetRotationLC(Vector3f(0.0f, 180.0f, 0.0f));
			continue;
		}
		/*
		else if(!strcmp(token, "<RLWheelScale>")) {
			for(int i=0;i<3;i++) {
				token = strtok(NULL, seps);
				temp[i] = float(atof(token));
			}
			newCar->getTires()[BLWHEEL].setScale(Vector3f(temp[0], temp[1], temp[2]));
			newCar->getTires()[BRWHEEL].setScale(Vector3f(temp[0], temp[1], temp[2]));
			continue;
		} */
		else if(!strcmp(token, "<OverallTrans>")) {
			for(int i=0;i<3;i++) {
				token = strtok(NULL, seps);
				temp[i] = float(atof(token));
			}
            Vector3f vOTrans = Vector3f(temp[0], temp[1], temp[2]);
			newCar->SetPositionLC(vOTrans);
            for(int j=0; j<4; j++) {
                newCar->GetTire(j)->SetPositionLC(newCar->GetTire(j)->GetPositionLC() + vOTrans);
			}
			continue;
		}
		else if(!strcmp(token, "<Height>")) {
			token = strtok(NULL, seps);
			newCar->SetHeight(float(atof(token)));
			continue;
		}
		else if(!strcmp(token, "<RollCenterHeight>")) {
			token = strtok(NULL, seps);
			newCar->SetRollCenterHeight(float(atof(token)));
			continue;
		}
		else if(!strcmp(token, "<B>")) {
			token = strtok(NULL, seps);
			newCar->SetB(float(atof(token)));
			continue;
		}
		else if(!strcmp(token, "<C>")) {
			token = strtok(NULL, seps);
			newCar->SetC(float(atof(token)));
			continue;
		}
		else if(!strcmp(token, "<TrackWidth>")) {
			token = strtok(NULL, seps);
			newCar->SetTrackWidth(float(atof(token)));
			continue;
		}
		else if(!strcmp(token, "<VehicleMass>")) {
			token = strtok(NULL, seps);
			newCar->SetVehicleMass(float(atof(token)));
			continue;
		}
		else if(!strcmp(token, "<TireMass>")) {
			token = strtok(NULL, seps);
			newCar->SetTireMass(float(atof(token)));
			continue;
		}
		else if(!strcmp(token, "<MaximumTorque>")) {
			token = strtok(NULL, seps);
			newCar->SetMaximumTorque(float(atof(token)));
			continue;
		}
		else if(!strcmp(token, "<MaximumRPM>")) {
			token = strtok(NULL, seps);
			newCar->SetMaximumRPM(float(atof(token)));
			continue;
		}
		else if(!strcmp(token, "<DrivetrainEfficiency>")) {
			token = strtok(NULL, seps);
			newCar->SetDrivetrainEfficiency(float(atof(token)));
			continue;
		}
		else if(!strcmp(token, "<RearDiffRatio>")) {
			token = strtok(NULL, seps);
			newCar->SetRearDiffRatio(float(atof(token)));
			continue;
		}
		else if(!strcmp(token, "<TireRadius>")) {
			token = strtok(NULL, seps);
			newCar->SetTireRadius(float(atof(token)));
			continue;
		}
		else if(!strcmp(token, "<FrontalArea>")) {
			token = strtok(NULL, seps);
			newCar->SetFrontalArea(float(atof(token)));
			continue;
		}
		else if(!strcmp(token, "<CoefficientOfAerodynamicFriction>")) {
			token = strtok(NULL, seps);
			newCar->SetCoefficientOfAerodynamicFriction(float(atof(token)));
			continue;
		}
		else if(!strcmp(token, "<CoefficientOfTireFriction>")) {
			token = strtok(NULL, seps);
			newCar->SetCoefficientOfTireFriction(float(atof(token)));
			continue;
		}
		else if(!strcmp(token, "<RotatingMass>")) {
			token = strtok(NULL, seps);
			newCar->SetRotatingMass(float(atof(token)));
			continue;
		}
		else if(!strcmp(token, "<GearRatios>")) {
			for(int i=0;i<6;i++) {
				token = strtok(NULL, seps);
				temp[i] = float(atof(token));
			}
			newCar->SetGearRatios(temp);
			continue;
		}
	}
	
	// Load the vehicle mesh
	if(!newCar->LoadMesh( *directory )) {
		CLog::GetLog().Write(LOG_MISC, "Error CScene::LoadPlayerVehicle() >> Error loading vehicle body mesh");
		return 0;
	}
	// Load the mesh for the first tire
	if(!newCar->GetTire(0)->LoadMesh( *directory )) {
		CLog::GetLog().Write(LOG_MISC, "Error CScene::LoadPlayerVehicle() >> Error loading tire mesh");
		return 0;
	}

	// Set the remaining tires to point to the first tire mesh
	for(int i=1;i<4;i++) {
		newCar->GetTire(i)->SetMesh(newCar->GetTire(0)->GetMesh());
	}


	// Initialize the car variables, and convert local variables to world
	// space for the renderer to use.
	newCar->Init();

	// Add the mesh, and the vehicle to the scene
	m_vMeshes.push_back(newCar->GetMesh());
	m_vEntities.push_back(newCar);

	// Add the tires to the scene
	m_vMeshes.push_back(newCar->GetTire(0)->GetMesh());
	for(i=0;i<4;i++) {
		m_vEntities.push_back(newCar->GetTire(i));
	}

	// Set the playerVehicle pointer for the gamestatemanager,
	CGameStateManager::GetGameStateManagerPtr()->SetPlayerVehicle(newCar);

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