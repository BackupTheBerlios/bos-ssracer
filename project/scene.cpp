#include "scene.h"

#include "log.h"
#include "vehicle.h"
#include "gamestatemanager.h"
#include "macros.h"
#include "settings.h"
#include "copponentvehicle.h"
#include "ccollisionmanager.h" // Gib's add (for LoadPlanes())
#include "copponentai.h"

//static member declarations
std::map< std::string, CD3DMesh * > CScene::m_kMeshMap;
//vector<CD3DMesh*> CScene::m_vMeshes;

vector<CEntity*> CScene::m_vEntities;

//Rams Add
vector<CWaypoint*> CScene::m_vWaypoints;
vector<CWaypoint*> CScene::m_vWPShortCut1;

//Gib's add
vector<Rectangle3f*> CScene::m_vPlanes;

CScene::CScene()  
{
    bMapIsLoaded = false; 
    //m_vMeshes.clear();
    m_kMeshMap.clear();
    m_vEntities.clear();
    m_vWaypoints.clear();
    m_vWPShortCut1.clear();
    m_vPlanes.clear();
    m_kQuadTree = new CQuadTree();
}


CScene::~CScene() 
{
    //m_vMeshes.clear();
    m_kMeshMap.clear();
    m_vEntities.clear();
    m_vWaypoints.clear();
    m_vWPShortCut1.clear();
    m_vPlanes.clear();
    delete m_kQuadTree;
};


int CScene::AddMesh( CD3DMesh * pMesh ) 
{
    // null pointer?
    if (!pMesh) {
        CLog::GetLog().Write(LOG_GAMECONSOLE|LOG_MISC, "ERROR: CScene::AddMesh tried to add a NULL mesh to the mesh map");
        return 0;
    }
    // check if we already have this mesh loaded
    //if ( m_kMeshMap[string(pMesh->m_strName)])  {
    if (IsMeshLoaded( string(pMesh->m_strName)) ) {
        #ifdef _DEBUG
        CLog::GetLog().Write(LOG_MISC, "WARNING CScene::AddMesh: Mesh %s already in the mesh map!", pMesh->m_strName);
        #endif
        return 1;
    }
    else {
        // add it to the meshmap
        m_kMeshMap[string(pMesh->m_strName)] = pMesh;
    }

    return 1;
}


int CScene::ReleaseScene()
{
/*	// Free all the meshes
	for(i=0;i<m_vMeshes.size();i++) {
        m_vMeshes[i]->InvalidateDeviceObjects();
        m_vMeshes[i]->Destroy();
		FREE(m_vMeshes[i], "Error CScene::ReleaseScene >> Attempted to delete a null pointer");
	}

	// Clear the vector of mesh pointers
	m_vMeshes.clear();
*/
    // destroy any loaded meshes
    for (std::map< std::string, CD3DMesh * >::iterator it=m_kMeshMap.begin(); it!=m_kMeshMap.end(); it++)  {
        if (it->second)  {
            HRESULT hr = it->second->InvalidateDeviceObjects();
            if( FAILED( hr ) )
                CLog::GetLog().Write(LOG_USER|LOG_MISC, "could not release mesh %s", it->second->m_strName);
            it->second->Destroy();
            FREE(it->second, "Error CScene::ReleaseScene >> Attempted to delete a null pointer");
        }
    }
    m_kMeshMap.clear();

	// Free all the entities
	for(unsigned int i=0;i<m_vEntities.size();i++) {
		FREE(m_vEntities[i], "Error CScene::ReleaseScene >> Attempted to delete a null pointer");
	}

	// Clear the vector of entity pointers
	m_vEntities.clear();

    //Ramit's add to free all waypoints in scene
    // Free all the Waypoints
	for(unsigned int j=0;j<m_vWaypoints.size();j++) {
		FREE(m_vWaypoints[j], "Error CScene::ReleaseScene >> Attempted to delete a null pointer");
	}

	// Clear the vector of entity pointers
	m_vWaypoints.clear();

    for(j=0;j<m_vWPShortCut1.size();j++) {
		FREE(m_vWPShortCut1[j], "Error CScene::ReleaseScene >> Attempted to delete a null pointer");
	}

	// Clear the vector of entity pointers
	m_vWPShortCut1.clear();

	//Gib's add to free all planes in scene
    // Free all the Planes
	for(unsigned int k=0;k<m_vPlanes.size();k++) {
		FREE(m_vPlanes[k], "Error CScene::ReleaseScene >> Attempted to delete a null pointer");
	}
	m_vPlanes.clear();

	// set player vehicle pointer to NULL
    CGameStateManager::GetGameStateManager().SetPlayerVehicle(NULL);

    // Also, clean up any other pointers that use the scene
	// AI player cars would have to be set to NULL as well.
	// Can't think of anything else right now.

    // empty out the quadtree
    m_kQuadTree->ClearQuadTree(); /////////////////////////////

    bMapIsLoaded = false;

	return 1;
}

/*
// is this old code?
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
*/

int CScene::LoadMap(FILE* fp, string* directory, string* filename)
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
				if(!LoadEntities(directory, filename)) {
					return 0;
				}
            }
            //Rams adds
            if(!strcmp(token, "waypoints")) {
				if(!LoadWaypoints(directory, filename)) {
					return 0;
				}
			}
            if(!strcmp(token, "race")) {
				if(!LoadRace(directory, filename)) {
					return 0;
				}
			}

			// Add more strcmp's here for other file types
			// that the map exporter might export
			// Maybe .aiPaths, .triggers
		}
	}

    bMapIsLoaded = true;  

    // intitalize the quadtree using the new entitity information
    m_kQuadTree->Initialize( &m_vEntities );

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
	//path.append("\\");
	path += *filename;
    ////
    path += ".objects";

	fp = fopen(path.c_str(), "r");

	if(!fp) {
		#ifdef _DEBUG
		CLog::GetLog().Write(LOG_GAMECONSOLE, "Error CScene::LoadEntities() >> Unable to open file %s", path.c_str());
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

        // for now assume these are all static entitites in the map file
        // so I know where to look for the mesh
        // we will need to be able to tell the difference between static and dynamic eventually to preserve the directory struture

        // look in .\media\meshes\static\
        // the mesh filename is the object's name as well: .\media\meshes\static\meshname\meshname.x .
        //if(!(newObject->LoadMesh(CSettingsManager::GetSettingsManager().GetGameSetting(DIRSTATICMESH) + string(newObject->GetName()) +"\\")) ) {
        if(!(newObject->LoadMesh(CSettingsManager::GetSettingsManager().GetGameSetting(DIRSTATICMESH) +"\\")) ) {
            CLog::GetLog().Write(LOG_MISC, "Error CScene::LoadEntities() >> Error loading mesh");
//                        return 0; //if you comment this line out, The entity will still load but will not render
        }

        //=== add it to the mesh map ===//
        AddMesh( newObject->GetMesh() );

        //=== add it to the entity vector ===//
		m_vEntities.push_back(newObject);

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
			newCar->GetTire(FLTIRE)->SetRotationLC(Vector3f(0.0f, 0.0f, -PI_BOS));
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
			newCar->GetTire(RLTIRE)->SetRotationLC(Vector3f(0.0f, 0.0f, -PI_BOS));
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
			/*
            for(int j=0; j<4; j++) {
                newCar->GetTire(j)->SetPositionLC(newCar->GetTire(j)->GetPositionLC() + vOTrans);
			}
			*/
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
		else if(!strcmp(token, "<MaximumEngineTorque>")) {
			token = strtok(NULL, seps);
			newCar->SetMaximumEngineTorque(float(atof(token)));
			continue;
		}
		else if(!strcmp(token, "<MaximumBrakeTorque>")) {
			token = strtok(NULL, seps);
			newCar->SetMaximumBrakeTorque(float(atof(token)));
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

	// Add the mesh, 
	//m_vMeshes.push_back(newCar->GetMesh());
    if(!AddMesh(newCar->GetMesh()))
        return 0;

    // add the vehicle to the scene
	m_vEntities.push_back(newCar);

    // add body to the quadtree
    //m_kQuadTree->Add(newCar);


	// Add 1 tire mesh (assuming they all look the same)
	//m_vMeshes.push_back(newCar->GetTire(0)->GetMesh());
    if (!AddMesh(newCar->GetTire(0)->GetMesh()))
        return 0;

    // Add the tires to the scene
	for(i=0;i<4;i++) {
		m_vEntities.push_back(newCar->GetTire(i));
        // add tire to the quadtree
        //m_kQuadTree->Add(newCar->GetTire(i));
	}

	// Set the playerVehicle pointer for the gamestatemanager,
	CGameStateManager::GetGameStateManagerPtr()->SetPlayerVehicle(newCar);


	return 1;
}

//Ram & Gibs Addition (Exactly Like Load player but uses COpponentVehicle instead
int CScene::LoadOpponentVehicle(string* directory, string* filename)
{
	FILE* fp;
	string path;
	char buf[1024];
	char* token;
	char seps[] = " \t\n";
	COpponentVehicle * newCar;
	float temp[6];

	path.assign(directory->c_str());
	path.append(filename->c_str());

	fp = fopen(path.c_str(), "r");

	if(!fp) {
		return 0;
	}

	newCar = new COpponentVehicle();
    //newCar->SetId(20001);   //temp for myself testing
	while(fgets(buf, sizeof(buf), fp)) {
		token = strtok(buf, seps);

		if(token == NULL) {
			continue;
		}
        //hardcoded id to 20001 for now, since im only dealing with one ai car
        if(!strcmp(token, "<id>")) {
			token = strtok(NULL, seps);
			newCar->SetId(atoi(token));
            //newCar->SetId(20001);
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
			newCar->GetTire(FLTIRE)->SetRotationLC(Vector3f(0.0f, 0.0f, -PI_BOS));
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
			newCar->GetTire(RLTIRE)->SetRotationLC(Vector3f(0.0f, 0.0f, -PI_BOS));
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
			/*
            for(int j=0; j<4; j++) {
                newCar->GetTire(j)->SetPositionLC(newCar->GetTire(j)->GetPositionLC() + vOTrans);
			}
			*/
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
		else if(!strcmp(token, "<MaximumEngineTorque>")) {
			token = strtok(NULL, seps);
			newCar->SetMaximumEngineTorque(float(atof(token)));
			continue;
		}
		else if(!strcmp(token, "<MaximumBrakeTorque>")) {
			token = strtok(NULL, seps);
			newCar->SetMaximumBrakeTorque(float(atof(token)));
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
		CLog::GetLog().Write(LOG_MISC, "Error CScene::LoadOpponentVehicle() >> Error loading vehicle body mesh");
		return 0;
	}
	// Load the mesh for the first tire
	if(!newCar->GetTire(0)->LoadMesh( *directory )) {
		CLog::GetLog().Write(LOG_MISC, "Error CScene::LoadOpponentVehicle() >> Error loading tire mesh");
		return 0;
	}

	// Set the remaining tires to point to the first tire mesh
	for(int i=1;i<4;i++) {
		newCar->GetTire(i)->SetMesh(newCar->GetTire(0)->GetMesh());
	}


	// Initialize the car variables, and convert local variables to world
	// space for the renderer to use.
	newCar->Init();

	// Add the mesh, 
	//m_vMeshes.push_back(newCar->GetMesh());
    if(!AddMesh(newCar->GetMesh()))
        return 0;

    // add the vehicle to the scene
	m_vEntities.push_back(newCar);

    // add body to the quadtree
    //m_kQuadTree->Add(newCar);


	// Add 1 tire mesh (assuming they all look the same)
	//m_vMeshes.push_back(newCar->GetTire(0)->GetMesh());
    if (!AddMesh(newCar->GetTire(0)->GetMesh()))
        return 0;

    // Add the tires to the scene
	for(i=0;i<4;i++) {
		m_vEntities.push_back(newCar->GetTire(i));
        // add tire to the quadtree
        //m_kQuadTree->Add(newCar->GetTire(i));
	}

    // Add opponent to list in Gamestate manager
    CGameStateManager::GetGameStateManagerPtr()->addOpponentVehicle(newCar);
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

    // load up the mesh
	if(!newEntity->LoadMesh( *directory )) {
		CLog::GetLog().Write(LOG_GAMECONSOLE|LOG_MISC, "Error CScene::LoadEntity() >> Error loading mesh %s%s",directory->c_str(), filename->c_str());
		FREE(newEntity, "Error CScene::LoadIdentity() >> Error releasing memory");
		return 0;
	}

	// Everything went ok, so now add the entity to the scene
	m_vEntities.push_back(newEntity);
	
    // add the mesh
    if (!AddMesh(newEntity->GetMesh()))
        return 0;

    // add it to the quadtree
    m_kQuadTree->Add(newEntity);

	return 1;
}

//Ramits Add Until infrastructure up, 
// uses CWaypoint instead of CEntity
//other than that exactly LoadEntitys
int CScene ::LoadWaypoints(string* directory, string* filename)
{
	FILE* fp;
	char buf[512];
	char* token;
	char seps[] = " \n";
	int i;
	string path;

	path = directory->c_str();
	//path.append("\\");
	path += *filename;
    ////
    path += ".waypoints";

	fp = fopen(path.c_str(), "r");

	if(!fp) {
		#ifdef _DEBUG
		CLog::GetLog().Write(LOG_GAMECONSOLE, "Error CScene::LoadEntities() >> Unable to open file %s", path.c_str());
		#endif
		return 0;
	}

	float temp[3];
	Box3f tempBox;
	Sphere3f tempSphere;
	CWaypoint *newObject = NULL;

	while(fgets(buf, sizeof(buf), fp)) {
		token = strtok(buf, seps);
		if(token == NULL) {
			continue;
		}
		if(!strcmp(token, "<newwp>")) {
			//newObject = new CEntity;


			NEW(newObject, CWaypoint, "Error CScene::LoadWaypoints >> new operator failed");
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
                //To determine if waypoint is normal, branch, or conjunct or not
                if(!strcmp(token, "<type>")) {
					token = strtok(NULL, seps);
					newObject->setType(atoi(token));
					continue;
					}
                //To differentiate the different paths and where waypoint is ultimately loaded
                if(!strcmp(token, "<path>")) {
					token = strtok(NULL, seps);
					newObject->setPath(atoi(token));
					continue;
					}
                //Will only have on Waypoints that are of Branch type
                if(!strcmp(token, "<BranchToPath>")) {
					token= strtok(NULL, seps);
					newObject->setGoToPath(atoi(token));
					continue;
					}
                //Will only have on Waypoints that are of Conjunction type
                if(!strcmp(token, "<ConjunctIndex>")) {
					token= strtok(NULL, seps);
					newObject->setCIndex(atoi(token));
					continue;
					}
				if(!strcmp(token, "<scale>")) {
					for(i=0;i<3;i++) {
						token = strtok(NULL, seps);
						temp[i] = float(atof(token));
					}
					newObject->SetScale(Vector3f(temp[0], temp[1], temp[2]));
					break;
				}
               
			}
		}

        //No mesh stuff needed :)
        
        //=== add it to the appropriate Waypoint vector ===//
        if ( newObject->getPath() == 1)
        {
          m_vWPShortCut1.push_back(newObject);
        }
        else
        {
		  m_vWaypoints.push_back(newObject);
        }

	}  //endwhile

    //Set Last Waypoint in Main Path as last Waypoint
   
    std::vector<CWaypoint *>::iterator it = m_vWaypoints.end()-1;
	(*it)->setLastWay(true);
	fclose(fp);

	return 1;

}

int CScene ::LoadRace(string* directory, string* filename)
{
	FILE* fp;
	char buf[512];
	char* token;
	char seps[] = " \n";
	int i;
	string path;

	path = directory->c_str();
	//path.append("\\");
	path += *filename;
    ////
    path += ".race";

	fp = fopen(path.c_str(), "r");

	if(!fp) {
		#ifdef _DEBUG
		CLog::GetLog().Write(LOG_GAMECONSOLE, "Error CScene::LoadEntities() >> Unable to open file %s", path.c_str());
		#endif
		return 0;
	}

	float temp[3];
	Box3f tempBox;
	Sphere3f tempSphere;
    string carDir, carName;
	COpponentVehicle *currentOpponent = NULL;
    std::vector<COpponentVehicle *>::iterator it;

	while(fgets(buf, sizeof(buf), fp)) {
		token = strtok(buf, seps);
		if(token == NULL) {
			continue;
		}
        	if(!strcmp(token, "<racedata>")) {
              CLog::GetLog().Write(LOG_GAMECONSOLE, "In race data");
	
			//newObject = new CEntity;
			//NEW(newObject, CWaypoint, "Error CScene::LoadWaypoints >> new operator failed");
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
				if(!strcmp(token, "<laps>")) {
					token = strtok(NULL, seps);
					int laps = atoi(token);
                    //TODO deal with race conditions
					continue;
				}
				if(!strcmp(token, "<racetype>")) {
					token = strtok(NULL, seps);
					int raceType = atoi(token);
                    //TODO deal with race conditions
                    break;
				}
            }
            }
				
		if(!strcmp(token, "<newopponent>")) {
			//newObject = new CEntity;
			//NEW(newObject, CWaypoint, "Error CScene::LoadWaypoints >> new operator failed");
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
				if(!strcmp(token, "<cardir>")) {
					token = strtok(NULL, seps);
					carDir = CSettingsManager::GetSettingsManager().GetGameSetting(DIRDYNVEHICLES)+token;
					continue;
				}
				if(!strcmp(token, "<carname>")) {
					token = strtok(NULL, seps);
					carName = token;
                    //NOTE Absolutely requires dir before name and dir & name before other attributes in .race file!!
                    if(!(CGameStateManager::GetGameStateManagerPtr()->GetScenePtr()->LoadOpponentVehicle(&carDir, &carName))) 
                    {
	            	CLog::GetLog().Write(LOG_GAMECONSOLE, "The Opponent Vehicle is not loaded correctly!");
	            	return OK;
	                }
                    it = CGameStateManager::GetGameStateManagerPtr()->GetOpponents()->end()-1;
                    currentOpponent = (*it);
                    continue;
				}
				if(!strcmp(token, "<startpos>")) {
					for(i=0;i<3;i++) {
						token = strtok(NULL, seps);
						temp[i] = float(atof(token));
					}
                    //doesnt set starting position properly .... wtf.
					//currentOpponent->SetPositionLC(Vector3f(temp[0], temp[1], temp[2]));
					currentOpponent->SetTranslate(Vector3f(temp[0], temp[1], temp[2]));
                    continue;
				}
				
                //To determine if ailevel is dumb, med or advanced
                if(!strcmp(token, "<ailevel>")) {
					token = strtok(NULL, seps);
					currentOpponent->setAILevel(atoi(token));
					break;
					}
                
				                

			}
		}

       /* //=== add it to the Waypoint vector ===//
        if ( newObject->getPath() == 1)
        {
          m_vWPShortCut1.push_back(newObject);
        }
        else
        {
		  m_vWaypoints.push_back(newObject);
        }
*/
	}  //endwhile

    //Go thru opponents vector and initialize waypoints (Which should be loaded in)
    vector<COpponentVehicle *>::iterator it2;
    for (it2=CGameStateManager::GetGameStateManagerPtr()->GetOpponents()->begin();
         it2<CGameStateManager::GetGameStateManagerPtr()->GetOpponents()->end();  it2++) {
 
        currentOpponent = (*it2);
        currentOpponent->setWPSequence(CGameStateManager::GetGameStateManagerPtr()->GetScenePtr()->GetWaypoints());
        currentOpponent->setWPSequence(CGameStateManager::GetGameStateManagerPtr()->GetScenePtr()->GetShortCut1());
        currentOpponent->initNext();
	    COpponentAI::GetOpponentAIPtr()->addCar(currentOpponent);
     
    }
  
    /*std::vector<CWaypoint *>::iterator it = m_vWaypoints.end()-1;
	(*it)->setLastWay(true);
	fclose(fp);
*///CRenderer::GetRenderer().SetActiveCamera(CAMERA_CHASE);
    //((CCameraChase *)CRenderer::GetRenderer().GetActiveCameraPtr())->SetVehicle((*CGameStateManager::GetGameStateManagerPtr()->GetOpponents()->begin()));
	
	return 1;

}



// Gib's Add: code copied and pasted directly from Ram's LoadWaypoint()
// then modified accordingly.
int CScene::LoadPlanes(string* directory, string* filename)
{
	FILE* fp;
	char buf[512];
	char* token;
	char seps[] = " \n";
	int i;
	string path;

	path = directory->c_str();
	//path.append("\\");
	path += *filename;
    ////
    path += ".planes";

	fp = fopen(path.c_str(), "r");

	if(!fp) {
		#ifdef _DEBUG
		CLog::GetLog().Write(LOG_GAMECONSOLE, "Error CScene::LoadEntities() >> Unable to open file %s", path.c_str());
		#endif
		return 0;
	}

	float temp[2];
	//Box3f tempBox;
	//Sphere3f tempSphere;
	Rectangle3f * newPlane = NULL;

	while(fgets(buf, sizeof(buf), fp)) {
		token = strtok(buf, seps);
		if(token == NULL) {
			continue;
		}
		if(!strcmp(token, "<newPlane>")) {
			newPlane = new Rectangle3f();

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
				if(!strcmp(token, "<origin>")) {
					for(i=0;i<3;i++) {
						token = strtok(NULL, seps);
						temp[i] = float(atof(token));
					}
					newPlane->Origin() = Vector3f(temp[0], temp[1], temp[2]);
					continue;
				}
				if(!strcmp(token, "<edge0>")) {
					for(i=0;i<3;i++) {
						token = strtok(NULL, seps);
						temp[i] = float(atof(token));
					}
					newPlane->Edge0() = Vector3f(temp[0], temp[1], temp[2]);
					continue;
				}
				if(!strcmp(token, "<edge1>")) {
					for(i=0;i<3;i++) {
						token = strtok(NULL, seps);
						temp[i] = float(atof(token));
					}
					newPlane->Edge1() = Vector3f(temp[0], temp[1], temp[2]);
					continue;
				}
			
				if(!strcmp(token, "<endPlane>")) {
					m_vPlanes.push_back(newPlane);
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

		if (!strcmp(token, "<endFile>")) {
			fclose(fp);
			break;
		}
	}

	// Now, add planes to CollisionManager:
	CCollisionManager::GetCollisionManagerPtr()->SetPlanes(&m_vPlanes);


        //No mesh stuff needed :)
        /*
        // for now assume these are all static entitites in the map file
        // so I know where to look for the mesh
        // we will need to be able to tell the difference between static and dynamic eventually to preserve the directory struture

        // look in .\media\meshes\static\
        // the mesh filename is the object's name as well: .\media\meshes\static\meshname\meshname.x .
        if(!(newObject->LoadMesh(CSettingsManager::GetSettingsManager().GetGameSetting(DIRSTATICMESH) + string(newObject->GetName()) +"\\")) ) {
            CLog::GetLog().Write(LOG_MISC, "Error CScene::LoadEntities() >> Error loading mesh");
//                        return 0; //if you comment this line out, The entity will still load but will not render
        }

        //=== add it to the mesh map ===//
        AddMesh( newObject->GetMesh() );
        */
        //=== add it to the Waypoint vector ===//
	//	m_vWaypoints.push_back(newObject);

//	}  //endwhile

    //Set Last Waypoint as last Waypoint
   
		/*
    std::vector<CWaypoint *>::iterator it = m_vWaypoints.end()-1;
	(*it)->setLastWay(true);
	fclose(fp);
*/

	return 1;
}