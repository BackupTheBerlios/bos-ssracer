#ifndef COPPONENTVEHICLE_H
#define COPPONENTVEHICLE_H

#define STL_USING_ALL
#include "stl.h"
#include "WmlVector3.h"
#include "cwaypoint.h"
#include "vehicle.h"

/* IDEAS:
	WPSequence (or Waypoint Sequence) is the ordered set of
	waypoints the OpponentVehicle must follow. The next iterator
	points to the next waypoint the vehicle has to reach.
	HeadingTarget and VelocityTarget are set to whatever heading 
	and/or velocity the vehicle must reach before it stops turning or 
	accelerating/decelarating. If any of the InputState bools
	(gas, brake, etc) are true, attention is focused on these.
	Otherwise, they are ignored.
  */

class COpponentVehicle : public CVehicle {
public:
	COpponentVehicle();
	~COpponentVehicle();

	int incNext();
	int decNext();
	int initNext() {m_Next = m_vWPSequence.begin(); return OK;}
	bool reachedHeadingTarget();

	std::vector<CWaypoint*>* WPSequence() {return &m_vWPSequence;}
	CWaypoint* Next() {return *m_Next;}
	Vector3f* HeadingTarget() {return &m_vHeadingTargetWC;}
	Vector3f* VelocityTarget() {return &m_vVelocityTargetWC;}
	int setWPSequence(std::vector<CWaypoint*>* WPSeq);
	int setNext(std::vector<CWaypoint*>::iterator next);
	int setHeadingTarget(Vector3f* HT);
	int setVelocityTarget(Vector3f* VT);
    //Ram's Add 
    bool lastWPReached;
    bool raceOver;
protected:
	std::vector<CWaypoint*> m_vWPSequence;
	std::vector<CWaypoint*>::iterator m_Next;
	Vector3f m_vHeadingTargetWC;
	Vector3f m_vVelocityTargetWC;


private:

};

#endif
