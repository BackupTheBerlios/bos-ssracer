#ifndef _CENTITY_H
#define _CENTITY_H


#include "d3dfile.h"
#include "WmlVector3.h"
#include "WmlBox3.h"
#include "WmlSphere3.h"

#define STL_USING_ALL
#include "stl.h"


using namespace Wml;

class CEntity {

public:
	
	CEntity();
	~CEntity() {};

	void SetMesh(CD3DMesh* pMesh) { m_pMesh = pMesh; };
	CD3DMesh* GetMesh() { return m_pMesh; };

	void SetTranslate(Vector3f translate) { m_translate = translate; };
	void SetRotate(Vector3f rotate) { m_rotate = rotate; };
	void SetScale(Vector3f scale) { m_scale = scale; };

	Vector3f* GetTranslate() { return &m_translate; };
	Vector3f* GetRotate() { return &m_rotate; };
	Vector3f* GetScale() { return &m_scale; };

	void SetName(char* name) { strcpy(m_strName, name); };
	void SetId(int id) { m_id = id; };

	char* GetName() { return m_strName; };
	int GetId() { return m_id; };

	void SetBoundingBox(Box3f box) { m_box = box; };
	void SetBoundingSphere(Sphere3f sphere) { m_sphere = sphere; };

	Box3f* GetBoundingBox() { return &m_box; };
	Sphere3f* GetBoundingSphere() { return &m_sphere; };

	int LoadMesh();		// Load the mesh specified by m_strName, append .x to the variable
    int LoadMesh( string strDir );  // load a mesh in a certain directory
    
    // Gib's modification (temporary. Will remove when Chris gets the vehicle vector in the game class implemented)
	std::string* GetEntityType() {return &m_strEntityType;}



protected:
	CD3DMesh* m_pMesh;	// Mesh data structure
	Vector3f m_translate, m_rotate, m_scale;	// World Transformed Values

	char m_strName[128];	// Filename of the mesh (without .x appended)
	int m_id;	// ID used for identification of the mesh

	Box3f m_box;	// Oriented bounding box for the entity
	Sphere3f m_sphere;	// Bounding sphere for the entity

    	// Gib's modification (temporary. Will remove when Chris gets the vehicle vector in the game class implemented)
	std::string m_strEntityType;

private:

};


#endif