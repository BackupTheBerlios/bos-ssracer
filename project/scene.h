#ifndef _CSCENE_H
#define _CSCENE_H

#define STL_USING_ALL
#include "stl.h"

#include "d3dfile.h"
#include "entity.h"

class CScene {

public:

	CScene() {};
	~CScene() {};

	int ReleaseScene();		// Delete all entities, and their meshes in the current scene
	int LoadScene(char* directory, char* filename);		// Load a new scene

protected:
	
	vector<CD3DMesh*> m_vMeshes;	// Vector containing meshes in the scene
	vector<CEntity*> m_vEntities;	// Vector containing all entities in the scene

private:

	int LoadMap(FILE* fp, char* directory, char* filename);		// Load a new map (.map file)
	int LoadObjects(char* directory, char* filename);	// Load the objects specified in the map file (.objects file)
	int LoadPlayerVehicle(char* directory, char* filename);		// Load a new player vehicle (.car file)
	int LoadMeshes();	// Load all the meshes in the scene
};

#endif