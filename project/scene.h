#ifndef _CSCENE_H
#define _CSCENE_H

#define STL_USING_ALL
#include "stl.h"

#include "entity.h"
#include "cwaypoint.h"
#include "ccommandlineparser.h"
#include "quadtree.h"
#include "renderer.h"
#include "WmlRectangle3.h" // Gib's add (for planes vector)

class CAITask;  //forward declaration

class CScene {

    friend int CCommandLineParser::loadmap();      //needed to access the LoadMap function from console
    friend int CCommandLineParser::ShowEntities(); //needed to access the entities from console
    friend int CCommandLineParser::LoadVehicleAI(); // Ram's Addition needed to axs entities from console
    friend int CCommandLineParser::loadrace();      //needed to access the LoadRace function from console
    friend void CRenderer::RenderScene();  // need to access static & dynamic entities for rendering
    friend CAITask; // to print debugging info only

public:

    CScene();
	~CScene(); 

    bool IsLoaded(){ return bMapIsLoaded;};  // check if a scene is allocated for a map

	int ReleaseScene();		// Delete all entities, and their meshes in the current scene
	//int LoadScene(string* directory, string* filename);		// Load a new scene
	int LoadPlayerVehicle(string* directory, string* filename);		// Load a new player vehicle (.car file)
	int LoadEntity(string* directory, string* filename);	// Load an entity and add it to the current scene
    //Ram's Additions
	int LoadOpponentVehicle(string* directory, string* filename);
    int LoadWaypoints(string* directory, string* filename);
    int LoadRaceSettings(string* directory, string* filename);
    int LoadWaypoint(CWaypoint* waypoint){m_vWaypoints.push_back(waypoint); return 1;}; //Temp just for my own testing
    //$$$TEMP this is just to get access too the entities for now.
    vector<CEntity*> * TEMPGetEntities() { return &m_vEntities; };  //$$$TEMP this function will not exist soon....
   
    //Gib's Additions
    int LoadPlanes(string* directory, string* filename);
 
    //Ramits Add
    vector<CWaypoint*> * GetWaypoints() { return &m_vWaypoints; };
    vector<CWaypoint*> * GetShortCut1() { return &m_vWPShortCut1; };


    //Gib's Add
    vector<Rectangle3f*> * GetPlanes() {return &m_vPlanes;}

    // misc get functions
    int GetNumEntities() { return m_vEntities.size(); };

    bool IsMeshLoaded( string strMeshName ){ if (!m_kMeshMap[strMeshName]) return false; else return true;};
    CD3DMesh * GetMeshPtrFromMap( string strName ) { return m_kMeshMap[strName]; };

    CQuadTree * GetQuadTree(){ return m_kQuadTree; };

protected:
	
	//static vector<CD3DMesh*> m_vMeshes;	// Vector containing meshes in the scene
    static std::map< std::string, CD3DMesh * >   m_kMeshMap;    // meshes in the current scene
	static vector<CEntity*>                      m_vEntities;	// Vector containing all entities in the scene
    CQuadTree *                                  m_kQuadTree;	// quadtree for visibility culling
    //Ram's Add to hold me Waypoints
    static vector<CWaypoint*>                    m_vWaypoints;	// Vector containing all waypoints in the scene
    static vector<CWaypoint*>                    m_vWPShortCut1;	// Short Cut Vector 1 MAke more as needed

    // Gib's Add
    static vector<Rectangle3f*>			 m_vPlanes;

private:
    int LoadRace(FILE* fp, string* directory, string* filename);		// Rams: Load a new Race, which leads to map WPS etc
	int LoadMap(FILE* fp, string* directory, string* filename);		// Load a new map (.map file) and create a scene
	int LoadEntities(string* directory, string* filename);	        // Load the objects specified in the map file (.objects file)
    bool bMapIsLoaded;

    int AddMesh( CD3DMesh * pMesh );  // add a mesh to the meshmap

	/*void LoadMap(char * cFilename = "debug", char * cDir = "./maps/debug/");*/
};

#endif