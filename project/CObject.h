#ifndef _COBJECT_H
#define _COBJECT_H

#include "bos.h"
#include "d3dfile.h"

#define STL_USING_VECTOR
#include "stl.h"

#include "WmlSphere3.h"
#include "WmlVector3.h"
#include "WmlBox3.h"
using namespace Wml;


class CObject {

public:
	CObject() {};
	~CObject() {};
	void setName(char* newName);
	void setType(int objectType);
	void setTranslate(Vector3f translate);
	void setRotate(Vector3f rotate);
	void setScale(Vector3f scale);
	void setId(int id);

	void setBoundingBox(Box3f &rect);
	void setBoundingSphere(Sphere3f &sphere);

	inline void setMesh( CD3DMesh * pkMesh ) { m_pkMesh = pkMesh; };
	inline CD3DMesh * getMesh() { return m_pkMesh; };

	char* getName();
	int getType();
	int getId();
	Vector3f getTranslate();
	Vector3f getRotate();
	Vector3f getScale();
	Sphere3f getBoundingSphere();
	Box3f getBoundingBox();

private:
	char m_name[128];
	int m_id;
	int m_type;
	Box3f m_box;
	Sphere3f m_sphere;
	Vector3f m_translate, m_rotate, m_scale;
	CD3DMesh * m_pkMesh;

};

#endif