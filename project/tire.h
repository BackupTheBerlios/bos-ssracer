#ifndef _TIRE_H
#define _TIRE_H

#include "entity.h"

class CTire : public CEntity {

public:
	CTire() {};
	~CTire() {};

	Vector3f GetPositionLC() { return positionLC; };
	Vector3f GetRotationLC() { return rotationLC; };

	void SetPositionLC(Vector3f param) { positionLC = param; };
	void SetRotationLC(Vector3f param) { rotationLC = param; };

protected:

private:

	Vector3f positionLC;	// The position of the tire relative to the vehicle
	Vector3f rotationLC;	// The rotation of the tire relative to itself (in vehicle coordinate space)
};


#endif