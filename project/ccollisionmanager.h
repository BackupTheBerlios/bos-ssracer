#ifndef CCOLLISIONMANAGER_H
#define CCOLLISIONMANAGER_H

#define STL_USING_ALL
#include "stl.h"

#include "entity.h"
#include "task.h"

#include "WmlPlane3.h"
#include "wmlbox3.h"
#include "wmlsphere3.h"
using namespace Wml;

class CCollisionManager : public ITask {
public:
	CCollisionManager();
	~CCollisionManager();

	bool hasCollided(std::vector<CEntity*>::iterator E1, std::vector<CEntity*>::iterator E2);
	bool hasCollided(std::vector<CEntity*>::iterator Entity, Plane3f* Plane);
	int respond(std::vector<CEntity*>::iterator E1, std::vector<CEntity*>::iterator E2);
	int respond(std::vector<CEntity*>::iterator Entity, Plane3f* Plane);

	static CCollisionManager & GetCollisionManager() {return *m_pkCollisionManager;}
    static CCollisionManager * GetCollisionManagerPtr() {return m_pkCollisionManager;}

	bool Start();
	void Update();
	//void OnSuspend();
	//void OnResume();
    //void Stop();

protected:
	void DoMessageHandle( ITaskMessage *cMsg );
	// Can't think of anything it needs right now (maybe a reference to the QuadTree?)

private:
	static CCollisionManager* m_pkCollisionManager;

};

#endif 