#include "copponentai.h"
#include "appstate.h"

COpponentAI* COpponentAI::m_pkOpponentAI = NULL;

COpponentAI::COpponentAI()
{
	m_pCars.reserve(VAI_CARS_SIZE);
	m_pCars.clear();
	m_pWaypoints.reserve(VAI_WP_SIZE);
	m_pWaypoints.clear();

	m_pkOpponentAI = this;
}

COpponentAI::~COpponentAI()
{
	// nothing to do here
}

int COpponentAI::createNCars(int n)
{
	if (n < 0) return NEGATIVE_VALUE;

	for (int i = 0; i < n; i++)
		m_pCars.push_back(new CVehicle());
	// Will be more complex than this eventually.
	// Also, need to load vehicles and add them to scene. 

	return OK;
}


int COpponentAI::addCar(CVehicle* Car)
{
	if (!Car) return NULL_POINTER;

	// see comment in createNCars()
	m_pCars.push_back(Car);
	return OK;
}

int COpponentAI::addCar(std::string dir, std::string file)
{
	// Will implement later
	return OK;
}

int COpponentAI::removeCar(int i)
{
	if (i < 0 || i >= m_pCars.size())
		return INDEX_OUT_OF_RANGE;

	std::vector<CVehicle*>::iterator thisCar = &m_pCars[i];
	m_pCars.erase(thisCar);
	// Must also remove it from scene
}

bool COpponentAI::isAtWaypoint(CVehicle* Car)
{
	// To be implemented:
	// if distance btwn wp center and car pos < wp radius
	// then return true
	// else return false
	// This won't catch cars who are partially within wp,
	// But whose corner pos marks is not.
	return true;
}

int COpponentAI::setDirection(CVehicle* Car)
{
	// To be implemented:
	// Have array of waypoints either in this AI class or in vehicle class.
	// This array is the order of wp's vehicle must follow.
	// Check next wp in array.
	// Orient vehicle to face that waypoint.
	// set lturn or rturn to true
	// This may be complicated: when to set them back to false?
	return OK;
}

bool COpponentAI::Start()
{
	// To be implemented:
	// Must either create vehicles & waypoints here,
	// Or get them from the current scene.
	return true;
}

void COpponentAI::Update()
{
	if (m_pCars.empty()) return;

	int i;
	switch (CAppStateManager::GetAppManPtr()->GetAppState()) {
	case STATE_PRE_GAME: // Is there anything to be done here?
		break;
	case STATE_IN_GAME:
		for (i = 0; i < m_pCars.size(); i++) {
			if (isAtWaypoint(m_pCars[i]))
				setDirection(m_pCars[i]);
			// Later, will implement brake and gas application
			// This requires knowledge of local environment.
			// i.e. About to crash? Spinning out?
			// Also, need to maintain a standard velocity (speedup/slowdown)
			// Particularly upon start of race when they're initially stopped.
		}
		break;
	default:; // Program should never get here
	}

	// Also, need to decide what to do with cars that have finished race
}

int COpponentAI::setCars(std::vector<CVehicle*> Cars)
{
	m_pCars.clear(); // This takes care of memory leaks doesn't it?
	m_pCars = Cars;
	return OK;
}

int COpponentAI::setWaypoints(std::vector<CWaypoint*> Waypoints)
{
	m_pWaypoints.clear();
	m_pWaypoints = Waypoints;
	return OK;
}

void COpponentAI::DoMessageHandle(ITaskMessage* cMsg)
{
	// Not doing anything here
}

