#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "Entity.h"
#include "ccollisionmessage.h"
#include "WmlVector3.h"
#include "WmlPlane3.h"

using namespace Wml;

class CRigidBody : public CEntity {
public:
	CRigidBody();
	~CRigidBody();

	void DeliverCollisionMessage(CCollisionMessage* ColMsg);
	void UpdateCollisionReaction();
	void HandlePushCollision(CCollisionMessage* ColMsg);
	void HandleSphereToSphereCollision(CCollisionMessage* ColMsg);
	Vector3f GetDirectionWhenDisturbed() {return m_vDirectionWhenDisturbed;}
	bool& isDisturbed() {return disturbed;}

protected:
	Vector3f m_vPosition;
	Vector3f m_vRotation;
	Vector3f m_vOrientation; // not being used... yet
	Vector3f m_vReflection;
	Vector3f m_vDirectionWhenDisturbed;
	bool disturbed;

private:

};

#endif