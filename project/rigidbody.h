#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "Entity.h"
#include "ccollisionmessage.h"
#include "WmlVector3.h"

using namespace Wml;

class CRigidBody : public CEntity {
public:
	CRigidBody();
	~CRigidBody();

	void DeliverCollisionMessage(CCollisionMessage* ColMsg);
	void UpdateCollisionReaction();

protected:
	Vector3f m_vPosition;
	Vector3f m_vOrientation;
	Vector3f m_vReflection;
	Vector3f m_vDirectionWhenDisturbed;
	bool disturbed;

private:

};

#endif