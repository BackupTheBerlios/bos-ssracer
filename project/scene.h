#ifndef _CSCENE_H
#define _CSCENE_H

#define STL_USING_ALL
#include "stl.h"

#include "entity.h"

class CScene {

public:

	CScene() {};
	~CScene() {};

	int ReleaseScene();		// Delete all entities, and their meshes in the current scene
	int LoadScene(string* directory, string* filename);		// Load a new scene
	int LoadPlayerVehicle(string* directory, string* filename);		// Load a new player vehicle (.car file)
	int LoadEntity(string* directory, string* filename);	// Load an entity and add it to the current scene

    //$$$TEMP this is just to get access too the entities for now.
    vector<CEntity*> * TEMPGetEntities() { return &m_vEntities; };

protected:
	
	static vector<CD3DMesh*> m_vMeshes;	// Vector containing meshes in the scene
	static vector<CEntity*> m_vEntities;	// Vector containing all entities in the scene

	

private:

	int LoadMap(FILE* fp, string* directory, string* filename);		// Load a new map (.map file)
	int LoadEntities(string* directory, string* filename);	// Load the objects specified in the map file (.objects file)

	/*void LoadMap(char * cFilename = "debug", char * cDir = "./maps/debug/");*/
};

#endif