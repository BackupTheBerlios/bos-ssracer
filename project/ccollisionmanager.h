#ifndef CCOLLISIONMANAGER_H
#define CCOLLISIONMANAGER_H

#define STL_USING_ALL
#include "stl.h"

#include "copponentvehicle.h"
#include "task.h"
#include "ccollisionmessage.h"

#include "WmlRectangle3.h"
#include "wmlbox3.h"
#include "wmlsphere3.h"
#include "wmlplane3.h"

using namespace Wml;

typedef struct {
	Vector3f* vertices;
	int col_vertex;
	Plane3f* Plane;
	float dist;
	Vector3f* ColPoint;
	Vector3f* Reverse;
} CollisionInfo;

class CCollisionManager : public ITask {
public:
	CCollisionManager();
	~CCollisionManager();

	bool hasCollided(CVehicle* PV, std::vector<COpponentVehicle*>::iterator OV);
	bool hasCollided(CVehicle* PV, std::vector<Rectangle3f*>::iterator Plane);
	int respond(CVehicle* PV, std::vector<COpponentVehicle*>::iterator OV);
	int respond(CVehicle* PV, std::vector<Rectangle3f*>::iterator Plane);

	int ComputeVertices(Box3f BBox, Vector3f vertices[]);
	int ComputeEdges(Vector3f vertices[], Vector3f edges[][2]);
	Vector3f* ComputeCollisionPoint(Plane3f* Plane, CEntity* Entity);
	static CCollisionManager & GetCollisionManager() {return *m_pkCollisionManager;}
    static CCollisionManager * GetCollisionManagerPtr() {return m_pkCollisionManager;}

	bool Start();
	void Update();
	//void OnSuspend();
	//void OnResume();
    //void Stop();

	int SetPlanes(std::vector<Rectangle3f*>* Planes);
	std::vector<Rectangle3f*>* GetPlanes() {return m_vPlanes;}

protected:
	void DoMessageHandle( ITaskMessage *cMsg );

	// This Planes vector is meant to be set the the general planes vector in Game or Scene.
	// This is so I don't have to change my code around when it actually gets implemented.
	std::vector<Rectangle3f*>* m_vPlanes;
	CollisionInfo m_CI;

private:
	static CCollisionManager* m_pkCollisionManager;

};

#endif 

/*
	bool hasCollided(std::vector<CEntity*>::iterator E1, std::vector<CEntity*>::iterator E2);
	bool hasCollided(std::vector<CEntity*>::iterator Entity, std::vector<Rectangle3f*>::iterator Plane);
	int respond(std::vector<CEntity*>::iterator E1, std::vector<CEntity*>::iterator E2);
	int respond(std::vector<CEntity*>::iterator Entity, std::vector<Rectangle3f*>::iterator Plane);
*/