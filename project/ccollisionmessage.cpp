#include "ccollisionmessage.h"
#include "macros.h"
#include "DXUtil.h"

CCollisionMessage::CCollisionMessage()
{
	m_E = NULL;
	m_vColPoint = NULL;
	m_vNormal = NULL;
	m_vReverse = NULL;
	m_Plane = NULL;
	m_nMessageType = COLLISION_MESSAGE;
}

CCollisionMessage::~CCollisionMessage()
{
	SAFE_DELETE(m_E);
	SAFE_DELETE(m_vColPoint);
	SAFE_DELETE(m_vNormal);
	SAFE_DELETE(m_vReverse);
	SAFE_DELETE(m_Plane);
}

int CCollisionMessage::SetEntity(CEntity* E)
{
	if (!E) return NULL_POINTER;
	m_E = E;
	return OK;
}

int CCollisionMessage::SetColPoint(Vector3f* ColPoint)
{
	if (!ColPoint) return NULL_POINTER;
	m_vColPoint = ColPoint;
	return OK;
}

int CCollisionMessage::SetNormal(Vector3f* Normal)
{
	if (!Normal) return NULL_POINTER;
	m_vNormal = Normal;
	return OK;
}

int CCollisionMessage::SetReverse(Vector3f* Reverse)
{
	if (!Reverse) return NULL_POINTER;
	m_vReverse = Reverse;
	return OK;
}

int CCollisionMessage::SetPlane(Rectangle3f* Plane)
{
	if (!Plane) return NULL_POINTER;
	m_Plane = Plane;
	return OK;
}