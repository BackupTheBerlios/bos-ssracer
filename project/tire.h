#ifndef _TIRE_H
#define _TIRE_H

#include "entity.h"

class CTire : public CEntity {

public:
	CTire() {};
	~CTire() {};

	Vector3f GetPositionLC();
protected:

private:

	Vector3f positionLC;	// The position of the tire relative to the vehicle
};


#endif