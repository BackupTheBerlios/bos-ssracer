#ifndef CCOLLISIONMESSAGE_H
#define CCOLLISIONMESSAGE_H

#include "task.h"
#include "entity.h"
#include "WmlVector3.h"
#include "WmlRectangle3.h"
using namespace Wml;

class CCollisionMessage : public ITaskMessage {
public:
	CCollisionMessage();
	~CCollisionMessage();

	// Get/Set functions for the structures below:
	int SetEntity(CEntity* E);
	int SetColPoint(Vector3f* ColPoint);
	int SetNormal(Vector3f* Normal);
	int SetReverse(Vector3f* Reverse);
	int SetPlane(Rectangle3f* Plane);
	CEntity* GetEntity() {return m_E;}
	Vector3f* GetColPoint() {return m_vColPoint;}
	Vector3f* GetNormal() {return m_vNormal;}
	Vector3f* GetReverse() {return m_vReverse;}
	Rectangle3f* GetPlane() {return m_Plane;}

protected:	
	CEntity* m_E;			// *Entity collided with
	Vector3f* m_vColPoint;	// *point of collision
	Vector3f* m_vNormal;	// *normal of surface collided with (box or plane)
	Vector3f* m_vReverse;	// *direction and magnitude to back up to arrive at the point of collision
	Rectangle3f* m_Plane;	// *The plane collided with (still valid for box-box collisions)

private:

};

#endif

