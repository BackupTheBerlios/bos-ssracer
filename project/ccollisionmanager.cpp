#include "ccollisionmanager.h"
#include "log.h"
#include "macros.h"
#include "gamestatemanager.h"
#include "WmlIntrPln3Box3.h"
#include "WmlPlane3.h"
#include "soundmessage.h"
using namespace Wml;

CCollisionManager * CCollisionManager::m_pkCollisionManager = NULL; 

CCollisionManager::CCollisionManager()
{
	m_nTaskType = COLLISION_TASK;
	m_vPlanes = NULL;

	m_CI.col_vertex = -1;
	m_CI.dist = 0.0f;
	m_CI.Plane = NULL;
	m_CI.vertices = NULL;
	m_CI.Reverse = NULL;

	m_pkCollisionManager = this;
}

CCollisionManager::~CCollisionManager()
{
//	m_vPlanes->clear();
	SAFE_DELETE(m_vPlanes);
	SAFE_DELETE(m_CI.Plane);
	SAFE_DELETE(m_CI.vertices); // This is an array
	SAFE_DELETE(m_CI.Reverse);
}

bool CCollisionManager::Start()
{
	// Can't think of anything else
	return true;
}

void CCollisionManager::Update()
{
	std::vector<CEntity*>::iterator thisEntity;
	std::vector<Rectangle3f*>::iterator thisPlane;

	// First, test collisions with player vehicle
	CVehicle* PV = CGameStateManager::GetGameStateManagerPtr()->GetPlayerVehicle();
	if (PV) {
		// playervehicle-plane collisions
		if (m_vPlanes) {
			if (m_vPlanes->size() > 0) {
				thisPlane = m_vPlanes->begin();
				while (thisPlane != m_vPlanes->end()) {
					if (hasCollided(PV, thisPlane))
						respond(PV, thisPlane);
					thisPlane++;
				}
			}
		}
		// Implementing playervehicle and opponent vehicle collisions here
	}

	// Now, test collisions with opponent vehicles
	if (!CGameStateManager::GetGameStateManagerPtr()->GetOpponents()) return;
	if (CGameStateManager::GetGameStateManagerPtr()->GetOpponents()->size() == 0) return;

	std::vector<COpponentVehicle*>::iterator OP = CGameStateManager::GetGameStateManagerPtr()->GetOpponents()->begin();
	while (OP != CGameStateManager::GetGameStateManagerPtr()->GetOpponents()->end()) { 
		// vehicle-plane collisions
		if (m_vPlanes) {
			if (m_vPlanes->size() > 0) {
				thisPlane = m_vPlanes->begin();
				while (thisPlane != m_vPlanes->end()) {
					if (hasCollided((CVehicle*)*OP, thisPlane))
						respond((CVehicle*)*OP, thisPlane);
					thisPlane++;
				}
			}
		}
		// Implement opponent vehicle collisions with other opponent vehicles here
		// Remember to skip opponent vehicles colliding with themselves
		OP++;
	}

	// Basic needs:
	// Go thru all Entities.
	// For each one, parse the quadtree till quadtree division cut through entity.
	// Check for collisions btwn it and all other entities within that quadrant.
	// If collisions detected, call respond(entity, entity) function
	// If quadrant is bordering world's edge, check for collisions btwn entity and edge plane
	// If collision detected, call respond(entity, plane)
}

// entity, entity
bool CCollisionManager::hasCollided(std::vector<CEntity*>::iterator E1, std::vector<CEntity*>::iterator E2)
{
#ifdef _DEBUG
	CLog::GetLog().Write(LOG_DEBUGOVERLAY, 80, "CCollisionManager::hasCollided(entity, entity) not implemented yet.");
#endif

	return false;
}

// playervehicle, plane
bool CCollisionManager::hasCollided(CVehicle* PV, std::vector<Rectangle3f*>::iterator Plane)
{
	Vector3f vertices[8];  
	bool NEG = false, POS = false;

	CLog::GetLog().Write(LOG_DEBUGOVERLAY, 26, "translate = (%f, %f, %f)",
		PV->GetTranslate()->X(), PV->GetTranslate()->Y(), PV->GetTranslate()->Z());

	// Create a WmlPlane3 from the WmlRectangle3 in the Plane iterator
	Vector3f normal = (*Plane)->Edge0().Cross((*Plane)->Edge1());
	normal.Normalize();
	Plane3f* P = new Plane3f(normal, (*Plane)->Origin()); 
	// Save in CollisionInfo
	SAFE_DELETE(m_CI.Plane);
	m_CI.Plane = P;

	// And 2 planes that mark the edges of the rectangle.
	// These will be used to test intersection points to see if they are within rectangle boundries
	Plane3f EdgePlanes[2];
	Vector3f EdgePlaneNormals[2];
	Vector3f EdgePlanePoints[2];
	// Create 2 planes out of its edges, and see if point is a positive distance away from all of them.
	EdgePlaneNormals[0] = (*Plane)->Edge1().Cross(P->GetNormal());
	EdgePlaneNormals[1] = P->GetNormal().Cross((*Plane)->Edge1());
	EdgePlaneNormals[0].Normalize();
	EdgePlaneNormals[1].Normalize();
	EdgePlanePoints[0] = (*Plane)->Origin();
	EdgePlanePoints[1] = (*Plane)->Origin() + (*Plane)->Edge0();
	EdgePlanes[0] = Plane3f(EdgePlaneNormals[0], EdgePlanePoints[0]);
	EdgePlanes[1] = Plane3f(EdgePlaneNormals[1], EdgePlanePoints[1]);

	// Compute vertices and edges of Entity's bounding box
	ComputeVertices(*PV->GetBoundingBox(), vertices);

	// Go thru each bounding box vertex and do 2 things:
	// 1) find out if they span the plane
	// 2) find out which is furthest behind plane
	float dist;
	m_CI.dist = 0.0f;
	for (int i = 0; i < 8; i++) {
		dist = P->DistanceTo(vertices[i]);
		if (dist > 0) POS = true;
		if (dist < 0) NEG = true;
		if (dist < m_CI.dist) {
			m_CI.dist = dist;
			m_CI.col_vertex = i;
		}
	}

	// if some vertices are positive and some negative, it spans the plane
	// therefore, find the exact collision point
	// If that point is within the rectangle boundries, return true
	Vector3f* ReverseVelocity;
	Vector3f ReverseNormal;
	float theta, h;
	if (POS && NEG) {
		// Find the collision point
		ReverseVelocity = new Vector3f(PV->GetVehicleVelocityWC());
		// If going forward, ReverseVelocity should point in opposite direction
		if (PV->GetVehicleVelocityLC().X() > 0.0f)
			*ReverseVelocity *= -1.0f;
		ReverseNormal = -P->GetNormal();
		theta = acos((ReverseVelocity->Dot(ReverseNormal))/(ReverseVelocity->Length()*ReverseNormal.Length()));		
		h = m_CI.dist/cos(theta);
		ReverseVelocity->Normalize();
		*ReverseVelocity *= Math<float>::FAbs(h);

		SAFE_DELETE(m_CI.Reverse);
		m_CI.Reverse = ReverseVelocity;
		SAFE_DELETE(m_CI.ColPoint);
		m_CI.ColPoint = new Vector3f(vertices[m_CI.col_vertex] + *ReverseVelocity);	
		
		// If it is within the rectangle boundried, return true
		// Make 2 planes of out rectangle edges
		Plane3f P1 = Plane3f((*Plane)->Edge0(), (*Plane)->Origin());
		Plane3f P2 = Plane3f(-(*Plane)->Edge0(), (*Plane)->Origin()+(*Plane)->Edge0());
		if (P1.DistanceTo(*m_CI.ColPoint) >= 0 &&
			P2.DistanceTo(*m_CI.ColPoint) >= 0)
			return true;
	}

	return false;
	//if (!strcmp(PV->GetName(),"mitsuEclipseBody")) 
}

// entity, entity
int CCollisionManager::respond(std::vector<CEntity*>::iterator E1, std::vector<CEntity*>::iterator E2)
{
#ifdef _DEBUG
	CLog::GetLog().Write(LOG_DEBUGOVERLAY, 80, "CCollisionManager::respond(entity, entity) not implemented yet.");
#endif
	return OK;
}

// playervehicle, plane
int CCollisionManager::respond(CVehicle* PV, std::vector<Rectangle3f*>::iterator Plane)
{
	/*** Make CRASH sound ***/
	CSoundMessage* SoundMsg = new CSoundMessage();
	SoundMsg->PlaySoundEffectOnce("crash_hard");
	CKernel::GetKernelPtr()->DeliverMessage(SoundMsg, SOUND_TASK);

	/*** Send collision info to physics task ***/
	CCollisionMessage* ColMsg = new CCollisionMessage();
	// Set Entity
	ColMsg->SetEntity((CEntity*)PV);
	// Set Normal
	Vector3f* Normal = new Vector3f((*Plane)->Edge0().Cross((*Plane)->Edge1()));
	Normal->Normalize();
	ColMsg->SetNormal(Normal);
	// Set Plane
	ColMsg->SetPlane(*Plane);
	// Set Reverse
	ColMsg->SetReverse(m_CI.Reverse);
	// Set Collision Point
	ColMsg->SetColPoint(m_CI.ColPoint);
	// Send message
	CKernel::GetKernelPtr()->DeliverMessage(ColMsg, PHYSICS_TASK);

	return OK;
}

int CCollisionManager::SetPlanes(std::vector<Rectangle3f*>* Planes)
{
	if (!Planes) return NULL_POINTER;

	// As long as m_vPlanes is not initialized with 'new', this will not cause a memory leak
	m_vPlanes = Planes;
	return OK;
}

// 'cause Box3's ComputeVertices() doesn't work
int CCollisionManager::ComputeVertices(Box3f BBox, Vector3f vertices[])
{
	Vector3f Center = BBox.Center();
	float* Ex = BBox.Extents();

	Vector3f V[] = {Vector3f(Ex[0], Ex[1], Ex[2]), // far-top-left
					Vector3f(Ex[0], Ex[1], -Ex[2]), // far-top-right
					Vector3f(Ex[0], -Ex[1], Ex[2]), // far-bottom-left
					Vector3f(Ex[0], -Ex[1], -Ex[2]), // far-bottom-right
					Vector3f(-Ex[0], Ex[1], Ex[2]), // near-top-left
					Vector3f(-Ex[0], Ex[1], -Ex[2]), // near-top-right
					Vector3f(-Ex[0], -Ex[1], Ex[2]), // near-bottom-left
					Vector3f(-Ex[0], -Ex[1], -Ex[2]) // near-bottom-right
	};

	for (int i = 0; i < 8; i++) {
		vertices[i] = V[i] + Center;
	}

	return OK;
}

int CCollisionManager::ComputeEdges(Vector3f vertices[], Vector3f edges[][2])
{
	edges[0][0] = vertices[0]; edges[0][1] = vertices[1]; // far-top-left to far-top-right
	edges[1][0] = vertices[1]; edges[1][1] = vertices[3]; // far-top-right to far-bottom-right
	edges[2][0] = vertices[3]; edges[2][1] = vertices[2]; // far-bottom-right to far-bottom-left
	edges[3][0] = vertices[2]; edges[3][1] = vertices[0]; // far-bottom-left to far-top-left

	edges[4][0] = vertices[4]; edges[4][1] = vertices[5]; // near-top-left to near-top-right
	edges[5][0] = vertices[5]; edges[5][1] = vertices[7]; // near-top-right to near-bottom-right
	edges[6][0] = vertices[7]; edges[6][1] = vertices[6]; // near-bottom-right to near-bottom-left
	edges[7][0] = vertices[6]; edges[7][1] = vertices[4]; // near-bottom-left to near-top-left

	edges[8][0] = vertices[0]; edges[8][1] = vertices[4]; // far-top-left to near-top-left
	edges[9][0] = vertices[1]; edges[9][1] = vertices[5]; // far-top-right to near-top-right
	edges[10][0] = vertices[3]; edges[10][1] = vertices[7]; // far-bottom-right to near-bottom-right
	edges[11][0] = vertices[2]; edges[11][1] = vertices[6]; // far-bottom-left to near-bottom-left

	return OK;
}

Vector3f* CCollisionManager::ComputeCollisionPoint(Plane3f* Plane, CEntity* Entity)
{
	if (!Plane || !Entity) return NULL;

	float dist;
	Vector3f MinPoint(0.0f, 0.0f, 0.0f);
	Vector3f vertices[8];
	ComputeVertices(*Entity->GetBoundingBox(), vertices);

	// Assumes Entity crashed into Plane on side of normal
	for (int i = 0; i < 8; i++) {
		dist = Plane->DistanceTo(vertices[i]); 
		if (dist < -MinPoint.Length()) {
			MinPoint = vertices[i];
			CLog::GetLog().Write(LOG_DEBUGOVERLAY, 74, "vertices[%i] = (%f, %f, %f)",
				i, vertices[i].X(), vertices[i].Y(), vertices[i].Z());
		}
	}
	dist = Plane->DistanceTo(MinPoint); // restore dist

	// Found furthest vertex, now find where it intersected
	Vector3f ReverseVelocity = ((CVehicle*)Entity)->GetVehicleHeadingWC();
	ReverseVelocity.Normalize();
	ReverseVelocity *= -((CVehicle*)Entity)->GetVehicleVelocityWC().Length();
	Vector3f ReverseNormal = -Plane->GetNormal();
	float theta = acos((ReverseVelocity.Dot(ReverseNormal))/(ReverseVelocity.Length()*ReverseNormal.Length()));
	float h = dist/cos(theta);
	ReverseVelocity.Normalize();
	ReverseVelocity *= h;
	Vector3f* ColPoint = new Vector3f(MinPoint + ReverseVelocity);

	return ColPoint;
}

void CCollisionManager::DoMessageHandle( ITaskMessage *cMsg )
{
	// Don't need to do anything here (as far as I can think)
}




/*
			CLog::GetLog().Write(LOG_DEBUGOVERLAY, 80+(i*2), "plane.normal = (%f, %f, %f)",
				 (*thisPlane)->GetNormal().X(),  (*thisPlane)->GetNormal().Y(),  (*thisPlane)->GetNormal().Z());
			CLog::GetLog().Write(LOG_DEBUGOVERLAY, 81+(i*2), "plane.c = %f", (*thisPlane)->GetConstant());
*/

/*
		CLog::GetLog().Write(LOG_DEBUGOVERLAY, 80, "Ex: (%f, %f, %f)",
			(*Entity)->GetBoundingBox()->Extent(0), (*Entity)->GetBoundingBox()->Extent(1), (*Entity)->GetBoundingBox()->Extent(2));
		for (int i = 0; i < 8; i++) {
			CLog::GetLog().Write(LOG_DEBUGOVERLAY, 81+i, "(%f, %f, %f)",
				vertices[i].X(), vertices[i].Y(), vertices[i].Z());
		}
		*/

//		CLog::GetLog().Write(LOG_DEBUGOVERLAY, 81, "car.translate = (%f, %f, %f)",
//			(*Entity)->GetTranslate()->X(), (*Entity)->GetTranslate()->Y(), (*Entity)->GetTranslate()->Z());
	//	CLog::GetLog().Write(LOG_DEBUGOVERLAY, 82, "plane.c = %f", (*Plane)->GetConstant());
		/*
		CLog::GetLog().Write(LOG_DEBUGOVERLAY, 82, "box.translate = (%f,\n%f,\n%f)",
			(*Entity)->GetBoundingBox()->Center().X(), 
			(*Entity)->GetBoundingBox()->Center().Y(),
			(*Entity)->GetBoundingBox()->Center().Z());
		CLog::GetLog().Write(LOG_DEBUGOVERLAY, 85, "sphere.translate = (%f,\n%f,\n%f)",
			(*Entity)->GetBoundingSphere()->Center().X(), 
			(*Entity)->GetBoundingSphere()->Center().Y(),
			(*Entity)->GetBoundingSphere()->Center().Z());
		*/	
	
/*		CLog::GetLog().Write(LOG_DEBUGOVERLAY, 82, "BB.pos = (%f, %f, %f)",
			(*Entity)->GetBoundingBox()->Center().X(), (*Entity)->GetBoundingBox()->Center().Y(), (*Entity)->GetBoundingBox()->Center().Z());

		CLog::GetLog().Write(LOG_DEBUGOVERLAY, 83, "BB.ext = (%f, %f, %f)",
			(*Entity)->GetBoundingBox()->Extent(0), (*Entity)->GetBoundingBox()->Extent(1), (*Entity)->GetBoundingBox()->Extent(2));

		CLog::GetLog().Write(LOG_DEBUGOVERLAY, 84, "BB.axes = (%f, %f, %f)",
			(*Entity)->GetBoundingBox()->Axis(0), (*Entity)->GetBoundingBox()->Axis(1), (*Entity)->GetBoundingBox()->Axis(2));

	(*Entity)->GetBoundingBox()->ComputeVertices(vertices);
	for (int i = 0; i < 8; i++)
		CLog::GetLog().Write(LOG_DEBUGOVERLAY, 85+i, "vertices[%i] = (%f, %f, %f)",
			i, vertices[i].X(), vertices[i].Y(), vertices[i].Z());
*/

/*
	if (!strcmp((*Entity)->GetName(),"mitsuEclipseBody")) {
		for (int i = 6; i < 12; i++)
		CLog::GetLog().Write(LOG_DEBUGOVERLAY, 68+(i*2), "From (%f, %f, %f)\nTo (%f, %f, %f)",
			edges[i][0].X(), edges[i][0].Y(), edges[i][0].Z(),
			edges[i][1].X(), edges[i][1].Y(), edges[i][1].Z());
	}
	*/

/*
	if (!strcmp((*Entity)->GetName(),"mitsuEclipseBody")) {
		CLog::GetLog().Write(LOG_DEBUGOVERLAY, 74, "P: (%f, %f, %f)",
			P.GetNormal().X(), P.GetNormal().Y(), P.GetNormal().Z());
		CLog::GetLog().Write(LOG_DEBUGOVERLAY, 75, "C: %f", (float)P.GetConstant());

			CLog::GetLog().Write(LOG_DEBUGOVERLAY, 76, "O: (%f, %f, %f)",
				(*Plane)->Origin().X(), (*Plane)->Origin().Y(), (*Plane)->Origin().Z());
			CLog::GetLog().Write(LOG_DEBUGOVERLAY, 77, "E0: (%f, %f, %f)",
				(*Plane)->Edge0().X(), (*Plane)->Edge0().Y(), (*Plane)->Edge0().Z());
			CLog::GetLog().Write(LOG_DEBUGOVERLAY, 78, "E1: (%f, %f, %f)",
				(*Plane)->Edge1().X(), (*Plane)->Edge1().Y(), (*Plane)->Edge1().Z());

	EdgePlaneNormals[0] = (*Plane)->Edge1().Cross(P.GetNormal());
	EdgePlaneNormals[1] = P.GetNormal().Cross((*Plane)->Edge1());
	EdgePlaneNormals[0].Normalize();
	EdgePlaneNormals[1].Normalize();

		CLog::GetLog().Write(LOG_DEBUGOVERLAY, 80, " N0: (%f, %f, %f)",
			EdgePlaneNormals[0].X(), EdgePlaneNormals[0].Y(), EdgePlaneNormals[0].Z());
		CLog::GetLog().Write(LOG_DEBUGOVERLAY, 81, " N1: (%f, %f, %f)",
			EdgePlaneNormals[1].X(), EdgePlaneNormals[1].Y(), EdgePlaneNormals[1].Z());
	
	EdgePlanePoints[0] = (*Plane)->Origin();
	EdgePlanePoints[1] = (*Plane)->Origin() + (*Plane)->Edge0();

		CLog::GetLog().Write(LOG_DEBUGOVERLAY, 82, " P0: (%f, %f, %f)",
			EdgePlanePoints[0].X(), EdgePlanePoints[0].Y(), EdgePlanePoints[0].Z());
		CLog::GetLog().Write(LOG_DEBUGOVERLAY, 83, " P1: (%f, %f, %f)",
			EdgePlanePoints[1].X(), EdgePlanePoints[1].Y(), EdgePlanePoints[1].Z());


	EdgePlanes[0] = Plane3f(EdgePlaneNormals[0], EdgePlanePoints[0]);
	EdgePlanes[1] = Plane3f(EdgePlaneNormals[1], EdgePlanePoints[1]);

		CLog::GetLog().Write(LOG_DEBUGOVERLAY, 84, " Pl0: (%f, %f, %f)",
			EdgePlanes[0].GetNormal().X(), EdgePlanes[0].GetNormal().Y(), EdgePlanes[0].GetNormal().Z());
		CLog::GetLog().Write(LOG_DEBUGOVERLAY, 85, "c: %f", EdgePlanes[0].GetConstant());
		CLog::GetLog().Write(LOG_DEBUGOVERLAY, 86, " Pl1: (%f, %f, %f)",
			EdgePlanes[1].GetNormal().X(), EdgePlanes[1].GetNormal().Y(), EdgePlanes[1].GetNormal().Z());
		CLog::GetLog().Write(LOG_DEBUGOVERLAY, 87, "c: %f", EdgePlanes[1].GetConstant());
		}
*/
	/*
	if (!strcmp((*Entity)->GetName(),"mitsuEclipseBody"))
	for (int g = 0; g < 2; g++)
	CLog::GetLog().Write(LOG_DEBUGOVERLAY, 80+(g*2), " %i: (%f, %f, %f)\nc = %f", g,
		EdgePlanes[g].GetNormal().X(), EdgePlanes[g].GetNormal().Y(), EdgePlanes[g].GetNormal().Z(), EdgePlanes[g].GetConstant());
*/

/*
// entity, plane
bool CCollisionManager::hasCollided(std::vector<CEntity*>::iterator Entity, std::vector<Rectangle3f*>::iterator Plane)
{
	Vector3f vertices[8];  // struct
	bool NEG = false, POS = false;

	CLog::GetLog().Write(LOG_DEBUGOVERLAY, 26, "translate = (%f, %f, %f)",
		(*Entity)->GetTranslate()->X(), (*Entity)->GetTranslate()->Y(), (*Entity)->GetTranslate()->Z());

	// Create a WmlPlane3 from the WmlRectangle3 in the Plane iterator
	Vector3f normal = (*Plane)->Edge0().Cross((*Plane)->Edge1());
	normal.Normalize();
	Plane3f* P = new Plane3f(normal, (*Plane)->Origin()); // struct
	// Save in CollisionInfo
	SAFE_DELETE(m_CI.Plane);
	m_CI.Plane = P;

	// And 2 planes that mark the edges of the rectangle.
	// These will be used to test intersection points to see if they are within rectangle boundries
	Plane3f EdgePlanes[2];
	Vector3f EdgePlaneNormals[2];
	Vector3f EdgePlanePoints[2];
	// Create 2 planes out of its edges, and see if point is a positive distance away from all of them.
	EdgePlaneNormals[0] = (*Plane)->Edge1().Cross(P->GetNormal());
	EdgePlaneNormals[1] = P->GetNormal().Cross((*Plane)->Edge1());
	EdgePlaneNormals[0].Normalize();
	EdgePlaneNormals[1].Normalize();
	EdgePlanePoints[0] = (*Plane)->Origin();
	EdgePlanePoints[1] = (*Plane)->Origin() + (*Plane)->Edge0();
	EdgePlanes[0] = Plane3f(EdgePlaneNormals[0], EdgePlanePoints[0]);
	EdgePlanes[1] = Plane3f(EdgePlaneNormals[1], EdgePlanePoints[1]);

	// Compute vertices and edges of Entity's bounding box
	ComputeVertices(*(*Entity)->GetBoundingBox(), vertices);

	// Go thru each bounding box vertex and do 2 things:
	// 1) find out if they span the plane
	// 2) find out which is furthest behind plane
	float dist;
	m_CI.dist = 0.0f;
	for (int i = 0; i < 8; i++) {
		dist = P->DistanceTo(vertices[i]);
		if (dist > 0) POS = true;
		if (dist < 0) NEG = true;
		if (dist < m_CI.dist) {
			m_CI.dist = dist;
			m_CI.col_vertex = i;
		}
	}

	// if some vertices are positive and some negative, it spans the plane
	// therefore, find the exact collision point
	// If that point is within the rectangle boundries, return true
	Vector3f* ReverseVelocity;
	Vector3f ReverseNormal;
	float theta, h;
	if (POS && NEG) {
		// Find the collision point
		ReverseVelocity = new Vector3f(((CVehicle*)*Entity)->GetVehicleVelocityWC());
		*ReverseVelocity *= -1;
		ReverseNormal = -P->GetNormal();
		theta = acos((ReverseVelocity->Dot(ReverseNormal))/(ReverseVelocity->Length()*ReverseNormal.Length()));		
		h = m_CI.dist/cos(theta);
		ReverseVelocity->Normalize();
		*ReverseVelocity *= Math<float>::FAbs(h);
		SAFE_DELETE(m_CI.Reverse);
		m_CI.Reverse = ReverseVelocity;
		SAFE_DELETE(m_CI.ColPoint);
		m_CI.ColPoint = new Vector3f(vertices[m_CI.col_vertex] + *ReverseVelocity);	
		
		// If it is within the rectangle boundried, return true
		// Make 2 planes of out rectangle edges
		Plane3f P1 = Plane3f((*Plane)->Edge0(), (*Plane)->Origin());
		Plane3f P2 = Plane3f(-(*Plane)->Edge0(), (*Plane)->Origin()+(*Plane)->Edge0());
		if (P1.DistanceTo(*m_CI.ColPoint) >= 0 &&
			P2.DistanceTo(*m_CI.ColPoint) >= 0)
			return true;
	}

	return false;
	//if (!strcmp((*Entity)->GetName(),"mitsuEclipseBody")) 
}

  // entity, plane
int CCollisionManager::respond(std::vector<CEntity*>::iterator Entity, std::vector<Rectangle3f*>::iterator Plane)
{
	// Make CRASH sound
	CSoundMessage* SoundMsg = new CSoundMessage();
	SoundMsg->PlaySoundEffectOnce("crash_hard");
	CKernel::GetKernelPtr()->DeliverMessage(SoundMsg, SOUND_TASK);

	// Send collision info to physics task
	CCollisionMessage* ColMsg = new CCollisionMessage();
	// Set Entity
	ColMsg->SetEntity(*Entity);
	// Set Normal
	Vector3f* Normal = new Vector3f((*Plane)->Edge0().Cross((*Plane)->Edge1()));
	Normal->Normalize();
	ColMsg->SetNormal(Normal);
	// Set Reverse
	ColMsg->SetReverse(m_CI.Reverse);
	// Set Collision Point
	ColMsg->SetColPoint(m_CI.ColPoint);
	// Send message
	CKernel::GetKernelPtr()->DeliverMessage(ColMsg, PHYSICS_TASK);

	return OK;
}
*/