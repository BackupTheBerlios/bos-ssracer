#ifndef COPPONENTAI_H
#define COPPONENTAI_H

#define STL_USING_ALL
#include "stl.h"
#include "task.h"
#include "copponentvehicle.h"
#include "cwaypoint.h"
#include "macros.h"

#define VAI_CARS_SIZE 20
#define VAI_WP_SIZE 100
#define VAI_CARS_VEL 25.0f // don't know if this is to scale
#define VAI_CARS_ACCEL 10.0f // ""

#define DUMB_AI 1
#define MEDIOCRE_AI 2
#define ADVANCED_AI 3

class COpponentAI : public ITask {
public:
	COpponentAI();
	~COpponentAI();

	static COpponentAI & GetOpponentAI() {return *m_pkOpponentAI;}
	static COpponentAI * GetOpponentAIPtr() {return m_pkOpponentAI;}

	int createNCars(int n);
	int addCar(COpponentVehicle* Car);
	int addCar(std::string dir, std::string file);
	int removeCar(int i);
	bool isAtWaypoint(COpponentVehicle* Car);
	int setDirection(COpponentVehicle* Car);

	// inherited virtual functions
	bool Start();
	void Update();
	//void OnSuspend();
	//void OnResume();
	//void Stop();

	std::vector<COpponentVehicle*>* Cars() {return &m_pCars;}
	std::vector<CWaypoint*>* Waypoints() {return &m_pWaypoints;}
	int setCars(std::vector<COpponentVehicle*> Cars);
	int setWaypoints(std::vector<CWaypoint*> Waypoints);

protected:
	// inherited virtual function
	void DoMessageHandle(ITaskMessage* cMsg);

	std::vector<COpponentVehicle*> m_pCars;
	std::vector<CWaypoint*> m_pWaypoints;
	
private:
	static COpponentAI* m_pkOpponentAI; 
};

#endif