#include "ccollisionmanager.h"
#include "log.h"
#include "macros.h"
#include "gamestatemanager.h"
#include "WmlIntrPln3Box3.h"
#include "WmlIntrBox3Box3.h"
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
	m_CI.Rect = NULL;
	m_CI.vertices = NULL;
	m_CI.Reverse = NULL;

	m_pkCollisionManager = this;
}

CCollisionManager::~CCollisionManager()
{
//	m_vPlanes->clear();
	SAFE_DELETE(m_vPlanes);
	SAFE_DELETE(m_CI.Plane);
	SAFE_DELETE(m_CI.Rect);
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
	std::vector<COpponentVehicle*>::iterator OV1;
	std::vector<COpponentVehicle*>::iterator OV2;


	CVehicle* PV = CGameStateManager::GetGameStateManagerPtr()->GetPlayerVehicle();

	// First, test collisions with player vehicle
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
		// playervehicle-box collisions
		if (CGameStateManager::GetGameStateManagerPtr()->GetOpponents())
			if (CGameStateManager::GetGameStateManagerPtr()->GetOpponents()->size() > 0) {
				OV1 = CGameStateManager::GetGameStateManagerPtr()->GetOpponents()->begin();
				while (OV1 != CGameStateManager::GetGameStateManagerPtr()->GetOpponents()->end()) {
					if (hasCollided(PV, OV1))
						respond(PV, OV1);
					OV1++;
				}
			}
	}

	
	// Now, test collisions with opponent vehicles
	if (!CGameStateManager::GetGameStateManagerPtr()->GetOpponents()) return;
	if (CGameStateManager::GetGameStateManagerPtr()->GetOpponents()->size() == 0) return;

	OV1 = CGameStateManager::GetGameStateManagerPtr()->GetOpponents()->begin();
	OV2 = OV1 + 1;
	while (OV1 != CGameStateManager::GetGameStateManagerPtr()->GetOpponents()->end()) { 
		// vehicle-plane collisions
		if (m_vPlanes) {
			if (m_vPlanes->size() > 0) {
				thisPlane = m_vPlanes->begin();
				while (thisPlane != m_vPlanes->end()) {
					if (hasCollided((CVehicle*)(*OV1), thisPlane))
						respond((CVehicle*)(*OV1), thisPlane);
					thisPlane++;
				}
			}
		}

		// vehicle-vehicle
		while (OV2 != CGameStateManager::GetGameStateManagerPtr()->GetOpponents()->end()) {
			if (hasCollided((CVehicle*)(*OV1), OV2))
				respond((CVehicle*)(*OV1), OV2);
			OV2++;
		}

		OV1++;
	}


	// Basic needs:
	// Go thru all Entities.
	// For each one, parse the quadtree till quadtree division cut through entity.
	// Check for collisions btwn it and all other entities within that quadrant.
	// If collisions detected, call respond(entity, entity) function
	// If quadrant is bordering world's edge, check for collisions btwn entity and edge plane
	// If collision detected, call respond(entity, plane)
}

// playervehicle, opponentvehicle
bool CCollisionManager::hasCollided(CVehicle* PV, std::vector<COpponentVehicle*>::iterator OV)
{
	Vector3f* ReverseVelocity;
	Vector3f ReverseNormal;
	float theta, h;

	// First, test if they are within colliding distance
	float pv_radius = PV->GetBoundingSphere()->Radius();
	float ov_radius = (*OV)->GetBoundingSphere()->Radius();
	Vector3f DistVec = PV->GetBoundingSphere()->Center() - (*OV)->GetBoundingSphere()->Center();

	if (pv_radius + ov_radius >= DistVec.Length()) {
		if (TestIntersection(*PV->GetBoundingBox(), *(*OV)->GetBoundingBox())) {


			return true;


			/* // ABANDONNING THIS FOR NOW AND GOING WITH A VERY SIMPLE SPHERE-SPHERE COLLISION RESPONSE

			int whichrectangle;
			Vector3f vertices[8];
			Rectangle3f rectangles[4];

			// See if any of PV's vertices are in OV's bounding box.
			// If they are, this determines the type of collision response
			// If they are not, then OV undergoes this type of collision response
			// The other may undergo a different kind of collision response
			// or the same depending on whether they both have vertices with the other's bounding box

			// Compute opponent vehicle's rectangles
			(*OV)->GetBoundingBox()->ComputeVertices(vertices);
			ComputeRectangles(vertices, rectangles);
			// Compute player vehicle's vertices
			PV->GetBoundingBox()->ComputeVertices(vertices);

			if (isInBoundingBox(vertices, rectangles, PV, whichrectangle)) {
				m_CI.collision_type = REFLECTIVE;
			}
			else m_CI.collision_type = PUSHED;

			SAFE_DELETE(m_CI.Rect);
			m_CI.Rect = new Rectangle3f(rectangles[whichrectangle]);

			return true; // temp

			/*
			if (m_CI.collision_type == REFLECTIVE) {

				Plane3f* P = new Plane3f(rectangles[whichrectangle].Edge0().Cross(rectangles[whichrectangle].Edge1()), 
								    	 rectangles[whichrectangle].Origin());
				// Go thru each bounding box vertex and do 2 things:
				// 1) find out if they span the plane
				// 2) find out which is furthest behind plane
				float dist;
				m_CI.dist = 0.0f;
				for (int i = 0; i < 8; i++) {
					dist = P->DistanceTo(vertices[i]);
					if (dist < m_CI.dist) {
						m_CI.dist = dist;
						m_CI.col_vertex = i;
					}
				}

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
			}
		
			if (m_CI.collision_type == PUSHED) {
				// whole different algorithm:
				// Find point of collision
				// This determines angular velocity
				// Find pushing vehicle's velocity
				// This determines push force
			}
			*/
		}
	}
	

	return false;
}

// playervehicle, opponentvehicle
int CCollisionManager::respond(CVehicle* PV, std::vector<COpponentVehicle*>::iterator OV)
{
	/*** Make CRASH sound ***/
	CSoundMessage* SoundMsg = new CSoundMessage();
	SoundMsg->PlaySoundEffectOnce("crash_hard");
	CKernel::GetKernelPtr()->DeliverMessage(SoundMsg, SOUND_TASK);

	/*** Send collision info to physics task ***/
	CCollisionMessage* ColMsg_forPV = new CCollisionMessage();
	CCollisionMessage* ColMsg_forOV = new CCollisionMessage();

	// Send message about player vehicle
	Vector3f CenterToCenter_forPV = PV->GetBoundingSphere()->Center() - (*OV)->GetBoundingSphere()->Center();
	ColMsg_forPV->SetCenterToCenter(new Vector3f(CenterToCenter_forPV));
	ColMsg_forPV->SetCollisionType(SPHERE_TO_SPHERE);
	ColMsg_forPV->SetEntity((CEntity*)PV);
	CKernel::GetKernelPtr()->DeliverMessage(ColMsg_forPV, PHYSICS_TASK);

	// Send message about opponent vehicle
	Vector3f CenterToCenter_forOV = (*OV)->GetBoundingSphere()->Center() - PV->GetBoundingSphere()->Center();
	ColMsg_forOV->SetCenterToCenter(new Vector3f(CenterToCenter_forOV));
	ColMsg_forOV->SetCollisionType(SPHERE_TO_SPHERE);
	ColMsg_forOV->SetEntity((CEntity*)(*OV));
	CKernel::GetKernelPtr()->DeliverMessage(ColMsg_forOV, PHYSICS_TASK);

	/*
	Vector3f* Normal;

	// Set Entity
	ColMsg->SetEntity((CEntity*)PV);
	// Set Normal
	Normal = new Vector3f(m_CI.Plane->GetNormal());
	Normal->Normalize();
	ColMsg->SetNormal(Normal);
	// Set Plane
	ColMsg->SetPlane(m_CI.Rect);
	// Set Collision Point
	ColMsg->SetColPoint(m_CI.ColPoint);

	/* // PUSH collisions don't work properly. Leaving this for now
	if (m_CI.collision_type == REFLECTIVE) {
		// Set Reverse
		ColMsg->SetReverse(m_CI.Reverse);
		// Set Type
		ColMsg->SetCollisionType(REFLECTIVE);
		// Send message
		CKernel::GetKernelPtr()->DeliverMessage(ColMsg, PHYSICS_TASK);
	}
	else { // m_CI.collision_type = PUSHED
		// Set PushForce
		Vector3f* OV_vel = new Vector3f((*OV)->GetVehicleVelocityWC());
		if ((*OV)->GetVehicleVelocityLC().X() < 0.0f)
			*OV_vel *= -1.0f;
		ColMsg->SetPushForce(OV_vel);
		// Set Type
		ColMsg->SetCollisionType(PUSHED);
		// Send message
		CKernel::GetKernelPtr()->DeliverMessage(ColMsg, PHYSICS_TASK);	
	}
	*/
	/*

	// If you get push collisions working properly, remove this
			// Set Reverse
		ColMsg->SetReverse(m_CI.Reverse);
		// Send message
		CKernel::GetKernelPtr()->DeliverMessage(ColMsg, PHYSICS_TASK);
*/


	return OK;
}

// playervehicle, plane
bool CCollisionManager::hasCollided(CVehicle* PV, std::vector<Rectangle3f*>::iterator Plane)
{
	Vector3f vertices[8];  
	bool NEG = false, POS = false;

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
	PV->GetBoundingBox()->ComputeVertices(vertices);

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
	// If that point is within the rectangle boundaries, return true
	Vector3f* ReverseVelocity;
	Vector3f ReverseNormal;
	float theta, h;
	if (POS && NEG) {
		// Find the collision point
		if (PV->isDisturbed()) {
			ReverseVelocity = new Vector3f(PV->GetDirectionWhenDisturbed());
			*ReverseVelocity *= -1.0f;
		}
		else {
			ReverseVelocity = new Vector3f(PV->GetVehicleVelocityWC());
			// If going forward, ReverseVelocity should point in opposite direction
			if (PV->GetVehicleVelocityLC().X() > 0.0f)
				*ReverseVelocity *= -1.0f;
		}

		ReverseNormal = -P->GetNormal();

		if (ReverseVelocity->Length() == 0.0f) {
			h = 1.0f;
		}
		else {
			theta = acos((ReverseVelocity->Dot(ReverseNormal))/(ReverseVelocity->Length()*ReverseNormal.Length()));		
			if (cos(theta) == 0.0f) h = 1.0f;
			else h = m_CI.dist/cos(theta);
		}

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

// NOTE: THIS FUNCTION IS NO LONGER VALID AS IT NOW NEEDS TO ACCOUNT FOR THE AXES ALIGNMENT
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

// NOTE: THIS FUNCTION IS NO LONGER VALID AS IT NOW NEEDS TO ACCOUNT FOR THE AXES ALIGNMENT
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

// THIS FUNCTION IS CURRENTLY NOT BEING USED
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

int CCollisionManager::ComputeRectangles(Vector3f vertices[8], Rectangle3f rectangles[4])
{
	// Calculate the 4 rectangles that make up the sides of the bounding box.
	/* vertices = {near-top-right, far-top-right, far-bottom-right, near-bottom-right,
				   near-top-left, far-top-left, far-bottom-left, near-bottom-left}
				   */

	Rectangle3f RectFRONT;
	RectFRONT.Origin() = Vector3f(vertices[6]);
	RectFRONT.Edge0() = Vector3f(vertices[2]-vertices[6]);
	RectFRONT.Edge1() = Vector3f(vertices[5]-vertices[6]);

	Rectangle3f RectRIGHT;
	RectRIGHT.Origin() = Vector3f(vertices[2]);
	RectRIGHT.Edge0() = Vector3f(vertices[3]-vertices[2]);
	RectRIGHT.Edge1() = Vector3f(vertices[1]-vertices[2]);

	Rectangle3f RectBACK;
	RectBACK.Origin() = Vector3f(vertices[3]);
	RectBACK.Edge0() = Vector3f(vertices[7]-vertices[3]);
	RectBACK.Edge1() = Vector3f(vertices[0]-vertices[3]);

	Rectangle3f RectLEFT;
	RectLEFT.Origin() = Vector3f(vertices[7]);
	RectLEFT.Edge0() = Vector3f(vertices[6]-vertices[7]);
	RectLEFT.Edge1() = Vector3f(vertices[4]-vertices[7]);

	rectangles[0] = Rectangle3f(RectFRONT);
	rectangles[1] = Rectangle3f(RectRIGHT);
	rectangles[2] = Rectangle3f(RectBACK);
	rectangles[3] = Rectangle3f(RectLEFT);

	return OK;
}

bool CCollisionManager::isInBoundingBox(Vector3f vertices[8], Rectangle3f rectangles[4], CVehicle* Car, int &whichrectangle)
{
	// IDEA:
	// Make 4 planes out of rectangles
	// Go thru front 4 vertices: as soon as you discover one that is a negative distance from all planes, stop
	// If no such vertex found, return false
	// We are assuming the vehicle never spans across 2 opposing planes, but can span 2 adjacent planes.
	// Therefore, find at most 2 planes for which some vertices are POS and some are NEG.
	// For one of these planes, find the collision point based on the reverse velocity.
	// If this point is with in the rectangle, select this rectangle for whichrectangle.
	// If not, select the other rectangle for which rectangle.

		/* vertices = {near-top-right, far-top-right, far-bottom-right, near-bottom-right,
					   near-top-left, far-top-left, far-bottom-left, near-bottom-left}
		   rectangles = {FRONT, RIGHT, BACK, LEFT} // CW
				   */

	// Make 4 planes out of rectangles
	Plane3f planes[4];
	Vector3f Normal;
	for (int i = 0; i < 4; i++) {
		Normal = rectangles[i].Edge1().Cross(rectangles[i].Edge0());
		Normal.Normalize();
		planes[i] = Plane3f(Normal, rectangles[i].Origin());
	}

	// Go thru front 4 vertices
	// If one happens to be behind all 4 planes, stop
	// NOTE: if reversing, need to check back 4 points (actually, it appears the bounding box automatically inverts itself when reversing, so probably don't need to)
	// {top-right, bottom-right, top-left, bottom-left}
	int front[4] = {1, 2, 5, 6};  
	//int back[4] = {0, 3, 4, 7};
	float dist[4];
	for (int j = 0; j < 4; j++) {
		for (int k = 0; k < 4; k++) {
			dist[k] = planes[k].DistanceTo(vertices[front[j]]);
			if (dist[k] > 0.0f) break;
		}
		if (k == 4) break;
	}

	// Find out which two (or one) planes are candidates for collision planes.
	// How? Compare DistanceTo(dist[i]) with DistanceTo(dist[i]+velocity)
	// If distance decreases, we are interested in that plane
	int P1, P2;
	float sign;
	P1 = P2 = -1;
	if (Car->GetVehicleVelocityLC().X() < 0.0f) sign = -1.0f;
	else sign = 1.0f;
	for (i = 0; i < 4; i++) {
		if (dist[i] > planes[i].DistanceTo(vertices[front[j]] + Car->GetVehicleVelocityWC()*sign)) {
			if (P1 == -1) P1 = i;
			else P2 = i;
		}
	}

	// Now find collision point.
	// For each plane (P1 and P2), find the vertex with the highest negative value using DistanceTo().
	// Then run the reversing algorithm on that point
	Vector3f FurthestPoint;
	Vector3f ColPoint_P1, ColPoint_P2;
	Vector3f* ReverseVelocity = NULL;
	Vector3f ReverseNormal;
	Vector3f RV_P1, RV_P2;
	float theta, h;
	int left, right;
	i = P1;

	while (i != -1) {
		// Need to check upper 2 front vertices
		// If one of them outside bounding box, we don't even need to check
		switch(i) {
		case 0: left = 1; right = 3; break;
		case 1: left = 2; right = 0; break;
		case 2: left = 3; right = 1; break;
		case 3: left = 4; right = 2; break;
		}
		if (planes[right].DistanceTo(vertices[front[0]]) > 0.0f)
			FurthestPoint = vertices[front[2]];
		else if (planes[left].DistanceTo(vertices[front[2]]) > 0.0f)
			FurthestPoint = vertices[front[0]];
		else if (planes[i].DistanceTo(vertices[front[0]]) < planes[i].DistanceTo(vertices[front[2]]))
			FurthestPoint = vertices[front[0]];
		else FurthestPoint = vertices[front[2]];

		// Find collision point
		SAFE_DELETE(ReverseVelocity);
		ReverseVelocity = new Vector3f(Car->GetVehicleVelocityWC());
		// If going forward, ReverseVelocity should point in opposite direction
		if (Car->GetVehicleVelocityLC().X() > 0.0f)
			*ReverseVelocity *= -1.0f;

		ReverseNormal = -planes[i].GetNormal();
		theta = acos((ReverseVelocity->Dot(ReverseNormal))/(ReverseVelocity->Length()*ReverseNormal.Length()));		
		h = planes[i].DistanceTo(FurthestPoint)/cos(theta);

		ReverseVelocity->Normalize();
		*ReverseVelocity *= Math<float>::FAbs(h);

		if (i == P1) {
			ColPoint_P1 = FurthestPoint + *ReverseVelocity;
			RV_P1 = *ReverseVelocity;
			i = P2;
		}
		else {
			ColPoint_P2 = FurthestPoint + *ReverseVelocity;
			RV_P2 = *ReverseVelocity;
			i = -1;
		}
	}

	// Now figure out which plane actually got hit
	// How? Which ColPoint is actually in the rectangle?
	switch(P1) {
	case 0: left = 1; right = 3; break;
	case 1: left = 2; right = 0; break;
	case 2: left = 3; right = 1; break;
	case 3: left = 4; right = 2; break;
	}
	SAFE_DELETE(m_CI.ColPoint);
	SAFE_DELETE(m_CI.Reverse);
	SAFE_DELETE(m_CI.Plane);
	if (planes[left].DistanceTo(ColPoint_P1) > 0.0f ||
		planes[right].DistanceTo(ColPoint_P1) > 0.0f) {
		m_CI.ColPoint = new Vector3f(ColPoint_P2);
		m_CI.Reverse = new Vector3f(RV_P2);
		m_CI.Plane = new Plane3f(planes[P2]);
		whichrectangle = P2;
	}
	else {
		m_CI.ColPoint = new Vector3f(ColPoint_P1);
		m_CI.Reverse = new Vector3f(RV_P1);
		m_CI.Plane = new Plane3f(planes[P1]);
		whichrectangle = P1;
	}

	// Now return whether there was a vertex discovered in the bounding box or not.
	if (j != 4) {
		CLog::GetLog().Write(LOG_DEBUGOVERLAY, 60, "vertices[%i] = (%f, %f, %f) seems to be in box",
			front[j], vertices[front[j]].X(), vertices[front[j]].Y(), vertices[front[j]].Z());
		return true;
	}
	else {
		CLog::GetLog().Write(LOG_DEBUGOVERLAY, 60, "no vertices seem to be in box.");
		return false;
	}

}

void CCollisionManager::DoMessageHandle( ITaskMessage *cMsg )
{
	// Don't need to do anything here (as far as I can think)
}

/*** SAVING THIS FOR NOW

  // print planes
	CLog::GetLog().Write(LOG_MISC, "\n\n\nSTART PLANES REPORT");

	for (int j = 0; j < 4; j++) {
		CLog::GetLog().Write(LOG_MISC, "planes[%i].GetConstant() = %f", j, planes[j].GetConstant());
		CLog::GetLog().Write(LOG_MISC, "planes[%i].GetNormal() = (%f, %f, %f)", j, 
			planes[j].GetNormal().X(), planes[j].GetNormal().Y(), planes[j].GetNormal().Z());
	}

	CLog::GetLog().Write(LOG_MISC, "END PLANES REPORT\n\n\n");



  // print vertices
  	CLog::GetLog().Write(LOG_MISC, "---------------");
	for (int g = 0; g < 8; g++) {
		CLog::GetLog().Write(LOG_MISC, "vertices[%i] = (%f, %f, %f)",
			g, vertices[g].X(), vertices[g].Y(), vertices[g].Z());
	}
		CLog::GetLog().Write(LOG_MISC, "---------------");


  // print rectangles
  			CLog::GetLog().Write(LOG_MISC, "***");
			for(int gibby = 0; gibby < 4; gibby++) {
				CLog::GetLog().Write(LOG_MISC, "\nrectangle %i", gibby);
				CLog::GetLog().Write(LOG_MISC, "origin = (%f, %f, %f)",
					rectangles[gibby].Origin().X(), rectangles[gibby].Origin().Y(), rectangles[gibby].Origin().Z());
				CLog::GetLog().Write(LOG_MISC, "edge0 = (%f, %f, %f)",
					rectangles[gibby].Edge0().X(), rectangles[gibby].Edge0().Y(), rectangles[gibby].Edge0().Z());
CLog::GetLog().Write(LOG_MISC, "edge1 = (%f, %f, %f)",
					rectangles[gibby].Edge1().X(), rectangles[gibby].Edge1().Y(), rectangles[gibby].Edge1().Z());

			}
CLog::GetLog().Write(LOG_MISC, "---------------");


  // print FurthestPoint
  		CLog::GetLog().Write(LOG_MISC, "\n\n\nFurthestPoint = (%f, %f, %f)",
			FurthestPoint.X(), FurthestPoint.Y(), FurthestPoint.Z());
		CLog::GetLog().Write(LOG_MISC, "i = %i\n\n\n", i);

  // print ReverseVelocity
  		CLog::GetLog().Write(LOG_MISC, "\n\n\nReverseVelocity = (%f, %f, %f)",
			ReverseVelocity->X(), ReverseVelocity->Y(), ReverseVelocity->Z());
		CLog::GetLog().Write(LOG_MISC, "i = %i\n\n\n", i);


// Print ReverseNormal, theta, and h
  		CLog::GetLog().Write(LOG_MISC, "\n\n\nReverseNormal = (%f, %f, %f)",
			ReverseNormal.X(), ReverseNormal.Y(), ReverseNormal.Z());
		CLog::GetLog().Write(LOG_MISC, "theta = %f, h = %f", theta, h);
		CLog::GetLog().Write(LOG_MISC, "i = %i\n\n\n", i);

  ***/