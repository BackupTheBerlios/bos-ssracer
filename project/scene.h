#ifndef _CSCENE_H
#define _CSCENE_H

#define STL_USING_ALL
#include "stl.h"

#include "entity.h"
#include "ccommandlineparser.h"

class CScene {

    friend CCommandLineParser::loadmap(); //needed to access the LoadMap function from console

public:

    CScene();
	~CScene(); 

    bool IsLoaded(){ return bMapIsLoaded;};  // check if a scene is allocated for a map

	int ReleaseScene();		// Delete all entities, and their meshes in the current scene
	//int LoadScene(string* directory, string* filename);		// Load a new scene
	int LoadPlayerVehicle(string* directory, string* filename);		// Load a new player vehicle (.car file)
	int LoadEntity(string* directory, string* filename);	// Load an entity and add it to the current scene

    //$$$TEMP this is just to get access too the entities for now.
    vector<CEntity*> * TEMPGetEntities() { return &m_vEntities; };

    bool IsMeshLoaded( string strMeshName ){ if (!m_kMeshMap[strMeshName]) return false; else return true;};
    CD3DMesh * GetMeshPtrFromMap( string strName ) { return m_kMeshMap[strName]; };

protected:
	
	//static vector<CD3DMesh*> m_vMeshes;	// Vector containing meshes in the scene
    static std::map< std::string, CD3DMesh * > m_kMeshMap;       // meshes in the current scene
	static vector<CEntity*> m_vEntities;	// Vector containing all entities in the scene

	

private:

	int LoadMap(FILE* fp, string* directory, string* filename);		// Load a new map (.map file) and create a scene
	int LoadEntities(string* directory, string* filename);	// Load the objects specified in the map file (.objects file)
    bool bMapIsLoaded;

    int AddMesh( CD3DMesh * pMesh );  // add a mesh to the meshmap

	/*void LoadMap(char * cFilename = "debug", char * cDir = "./maps/debug/");*/
};

#endif