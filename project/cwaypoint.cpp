#include "cwaypoint.h"

CWaypoint::CWaypoint()
{
	m_fRadius = WP_RADIUS;
	m_Neighbors.reserve(WP_NEIGHBOR_SIZE);
	m_Neighbors.clear();
    m_isLastWay = false;
}

CWaypoint::~CWaypoint()
{
	// Nothing to do here
}

bool CWaypoint::isAtWaypoint(CVehicle* Car)
{
	if (!Car) return false;

	// distance = Car.position - this.position
	// if distance < radius, return true
	// else return false
	// This won't catch the condition where cars are partially within
	// WP volume but the corner that their position vector marks is not
	return true;
}

int CWaypoint::addNeighbor(CWaypoint* WP)
{
	if (!WP) return NULL_POINTER;

	// Should we check for duplicates?
	m_Neighbors.push_back(WP);
	return OK;
}

int CWaypoint::removeNeighbor(std::vector<CWaypoint*>::iterator thisWP)
{
	m_Neighbors.erase(thisWP);
	// Should check for success. thisWP may not have been a member of the Neighbors vector
	return OK;
}

int CWaypoint::setNeighbors(std::vector<CWaypoint*> Neighbors)
{
	m_Neighbors.clear();
	m_Neighbors = Neighbors;
	return OK;
}

int CWaypoint::setRadius(float r)
{
	if (r < 0.0f) return NEGATIVE_VALUE;
	m_fRadius = r;
	return OK;
}


