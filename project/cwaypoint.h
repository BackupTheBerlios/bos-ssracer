#ifndef CWAYPOINT_H
#define CWAYPOINT_H

#define STL_USING_ALL
#include "stl.h"
#include "entity.h"
#include "vehicle.h"
#include "macros.h"

#define WP_NEIGHBOR_SIZE 10
#define WP_RADIUS 50.0f // idunno

using namespace Wml;

class CWaypoint : public CEntity {
	public:
		CWaypoint();
		~CWaypoint();

		bool isAtWaypoint(CVehicle* Car);
		int addNeighbor(CWaypoint* WP);
		int removeNeighbor(std::vector<CWaypoint*>::iterator thisWP);

		float Radius() {return m_fRadius;}
		std::vector<CWaypoint*>* Neighbors() {return &m_Neighbors;}
		int setRadius(float r);
		int setNeighbors(std::vector<CWaypoint*> Neighbors);
	protected:
		float m_fRadius;
		std::vector<CWaypoint*> m_Neighbors;

	private:
};

#endif