#ifndef CWAYPOINT_H
#define CWAYPOINT_H

#define STL_USING_ALL
#include "stl.h"
#include "entity.h"
#include "vehicle.h"
#include "macros.h"

#define WP_NEIGHBOR_SIZE 10
#define WP_RADIUS 5.0f // idunno

// Different Waypoint Types
#define NORMALWP 0
#define BRANCHWP 1
#define CONJUNCTWP 2


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
        //Rams's Add
        int setLastWay(bool b) {m_isLastWay=b; return OK;};
        bool getLastWay(){return m_isLastWay;};
        int setType(int t) {m_Type=t; return OK;};
        int getType(){return m_Type;};
        int setPath(int p) {m_Path=p; return OK;};
        int getPath(){return m_Path;};
        int setCIndex(int c) {m_conjunctIndex=c; return OK;};
        int getCIndex(){return m_conjunctIndex;};
        int setCPath(int c) {m_conjunctPath=c; return OK;};
        int getCPath(){return m_conjunctPath;};
        int setGoToPath(int p) {m_gotoPath=p; return OK;};
        int getGoToPath(){return m_gotoPath;};

	protected:
        bool m_isLastWay;
		float m_fRadius;
        int m_Type;                    //look at top for different types
        int m_Path;                     //Which path it is on 0 for main all else for Shortcuts
		//Kinda Ugly for now, Perhaps make subclass later
        int m_gotoPath;                 //if branch taken gotopath
        int m_conjunctIndex;             //when conjoining index on main path to goto
        int m_conjunctPath;
        std::vector<CWaypoint*> m_Neighbors;

	private:
};

#endif