#ifndef _PHYSICS_H
#define _PHYSICS_H

#include <stdio.h>

class CPhysics {

public:
	
	CPhysics(int temp);
	~CPhysics() {};
	// singleton instance get functions
    static CPhysics & GetPhysics() { return *m_physics; };
    static CPhysics * GetPhysicsPtr() { return m_physics; };
	//void setPlayerVehicle(CPlayerVehicle* playerCar);
	//CPlayerVehicle * getPlayerVehicle(){ return m_playerCar; };

	void Update(int, bool);

protected:

	CPhysics() {};
//	CPlayerVehicle* m_playerCar;
	static CPhysics * m_physics;


private:
	
};


#endif