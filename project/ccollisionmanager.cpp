#include "ccollisionmanager.h"
#include "log.h"
#include "macros.h"

CCollisionManager * CCollisionManager::m_pkCollisionManager = NULL; 

CCollisionManager::CCollisionManager()
{
	m_nTaskType = COLLISION_TASK;
	m_pkCollisionManager = this;
}

CCollisionManager::~CCollisionManager()
{
	// Nothing to do here
}

bool CCollisionManager::Start()
{
	// Can't think of anything else
	return true;
}

void CCollisionManager::Update()
{
	// Basic needs:
	// Go thru all Entities.
	// For each one, parse the quadtree till quadtree division cut through entity.
	// Check for collisions btwn it and all other entities within that quadrant.
	// If collisions detected, call respond(entity, entity) function
	// If quadrant is bordering world's edge, check for collisions btwn entity and edge plane
	// If collision detected, call respond(entity, plane)
}

bool CCollisionManager::hasCollided(std::vector<CEntity*>::iterator E1, std::vector<CEntity*>::iterator E2)
{
#ifdef _DEBUG
	CLog::GetLog().Write(LOG_DEBUGOVERLAY, 80, "CCollisionManager::hasCollided(entity, entity) not implemented yet.");
#endif
	return false;
}

bool CCollisionManager::hasCollided(std::vector<CEntity*>::iterator Entity, Plane3f* Plane)
{
#ifdef _DEBUG
	CLog::GetLog().Write(LOG_DEBUGOVERLAY, 80, "CCollisionManager::hasCollided(entity, plane) not implemented yet.");
#endif
	return false;
}

int CCollisionManager::respond(std::vector<CEntity*>::iterator E1, std::vector<CEntity*>::iterator E2)
{
#ifdef _DEBUG
	CLog::GetLog().Write(LOG_DEBUGOVERLAY, 80, "CCollisionManager::respond(entity, entity) not implemented yet.");
#endif
	return OK;
}

int CCollisionManager::respond(std::vector<CEntity*>::iterator Entity, Plane3f* Plane)
{
#ifdef _DEBUG
	CLog::GetLog().Write(LOG_DEBUGOVERLAY, 80, "CCollisionManager::respond(entity, plane) not implemented yet.");
#endif
	return OK;
}

void CCollisionManager::DoMessageHandle( ITaskMessage *cMsg )
{
	// Don't need to do anything here (as far as I can think)
}
