#include "copponentai.h"
#include "appstate.h"
#include "gamestatemanager.h"
#include "wmlvector.h"

// Copied comment from vehicle.cpp:
//---------------------------------------------------------------------------
//
//	Note** All calculations are carried out in vehicle local coordinates (ie.
//		   +Z is towards the bottom of the vehicle, +Y is out the side of the
//		   vehicle, and +X points out the front of the vehicle.
//
//		   All angular calculations are carried out in RADIANS.
//
//		   All calculations are assumed to be operating on a rear wheel drive
//		   vehicle.
//---------------------------------------------------------------------------

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

// Probably not going to use this function in the end, but good for debugging purposes
int COpponentAI::createNCars(int n)
{
	if (n < 0) return NEGATIVE_VALUE;

	for (int i = 0; i < n; i++) 
		m_pCars.push_back(new COpponentVehicle());
	// Will be more complex than this eventually.
	// Also, need to load vehicles and add them to scene. 

	return OK;
}

int COpponentAI::addCar(COpponentVehicle* Car)
{
	if (!Car) return NULL_POINTER;

	// see comment in createNCars()
	m_pCars.push_back(Car);
	return OK;
}

int COpponentAI::addCar(std::string dir, std::string file)
{
	int success = CGameStateManager::GetGameStateManagerPtr()->
		GetScenePtr()->LoadEntity(&dir, &file);
	if (!success) return GENERAL_ERROR;

	// New Car should be at the end of the Entities vector in Scene
	std::vector<CEntity*>::iterator it = CGameStateManager::GetGameStateManagerPtr()->
		GetScenePtr()->TEMPGetEntities()->end()-1;
	m_pCars.push_back((COpponentVehicle*)(*it));

	/* // Commented out. Iterators are more reliable for retreiving things from vectors
	COpponentVehicle* Car = 
		(COpponentVehicle*)CGameStateManager::GetGameStateManagerPtr()->
		GetScenePtr()->TEMPGetEntities()->end()-1;
	m_pCars.push_back(Car);
	*/

	return OK;
}

int COpponentAI::removeCar(int i)
{
	if (i < 0 || i >= signed(m_pCars.size()))
		return INDEX_OUT_OF_RANGE;

	// from local vectore
	std::vector<COpponentVehicle*>::iterator thisCar = &m_pCars[i];
	m_pCars.erase(thisCar);

	/* // Commented out for now. Removing it from OpponentAI
	   // doesn't necessarily mean removing it from scene altogether.
	   // It could just mean the car will just sit there.
	   // (besides, the code below crashes)

	// and from Scene's entity vector
	CGameStateManager::GetGameStateManagerPtr()->
		GetScenePtr()->TEMPGetEntities()->erase
		((std::vector<CEntity*>::iterator)thisCar);
*/

	return OK;
}

bool COpponentAI::isAtWaypoint(COpponentVehicle* Car)
{
	if (!Car) return bool(NULL_POINTER);

	// if distance btwn wp center and car pos < wp radius
	// then it's at the waypoint
	// NOTE: This doesn't catch cars who are partially within wp,
	// But whose corner pos marks is not.
	float dist = (*Car->Next()->GetTranslate() - *Car->GetTranslate()).Length();
	if (dist < Car->Next()->Radius()) 
    {
     // CLog::GetLog().Write(LOG_DEBUGOVERLAY, 28, "WP Name: %s ", string(*Car->Next()->GetName()));
      return true;
    }

	else return false;

	//return true;
}

int COpponentAI::setDirection(COpponentVehicle* Car)
{
	if (!Car) return NULL_POINTER;

	// IDEA: To set HeadingTarget and lturn or rturn:
	// Find the WC angle of the current Heading:
	//		Normalize HeadingWC
	//		Take the z value of normalized HeadingWC.
	//		Take the inverse sine of z
	//		That's your WC angle.
	// Find the vector from the car's position to the next waypoint:
	//		WP.pos - Car.pos
	// Set HeadingTarget to this vector
	// Find HeadingTarget's WC angle:
	//		Same as above
	// Compare WC angles. This will determine whether to set lturn or rturn to true:
	//		if (Heading angle > HeadingTarget angle) lturn = true;
	//		if (Heading angle < HeadingTarget angle) rturn = true;
	//		else (already facing WP) do nothing


	// angle for HeadingWC
	Vector3f NormalizedHeadingWC = Car->GetVehicleHeadingWC();
	NormalizedHeadingWC.Normalize();
    //CLog::GetLog().Write(LOG_DEBUGOVERLAY,60, "Vehicle HEading: %f %f %f", NormalizedHeadingWC.X(), NormalizedHeadingWC.Y(),NormalizedHeadingWC.Z());
	double heading_angle = asin(NormalizedHeadingWC.Z());

	// Set heading target to the vector from car to waypoint
	CWaypoint* WP = Car->Next();
	Vector3f direction = *WP->GetTranslate() - *Car->GetTranslate();
   	Car->setHeadingTarget(&direction);

	// angle for HeadingTargetWC
	Vector3f NormalizedHeadingTargetWC = *Car->HeadingTarget();
	NormalizedHeadingTargetWC.Normalize();
   // CLog::GetLog().Write(LOG_DEBUGOVERLAY,64, "Normalized Heading: %f %f %f", NormalizedHeadingTargetWC.X(), NormalizedHeadingTargetWC.Y(),NormalizedHeadingTargetWC.Z());
	double heading_target_angle = asin(NormalizedHeadingTargetWC.Z());
    double resultAngle = acos(NormalizedHeadingWC.X()*NormalizedHeadingTargetWC.X()+NormalizedHeadingWC.Y()*NormalizedHeadingTargetWC.Y()+NormalizedHeadingWC.Z()*NormalizedHeadingTargetWC.Z());
	// compare angles to see if lturn or rturn should be set
    CLog::GetLog().Write(LOG_DEBUGOVERLAY,65, "Vehicle Angle: %f Target Angle: %f", heading_angle, heading_target_angle);
	if (heading_angle < heading_target_angle) {
     //   CLog::GetLog().Write(LOG_MISC, "Attempting to turn Left");
		Car->SetRTurn(false);
		Car->SetLTurn(true);
    //  Car->SetHeadingTotLC(Vector3f(direction.X(),direction.Z(), -direction.Y()));
	Car->setHeadingAngle(resultAngle);
    }
	if (heading_angle > heading_target_angle) {
       // CLog::GetLog().Write(LOG_MISC, "Attempting to turn Right");
		Car->SetLTurn(false);
		Car->SetRTurn(true);
      // Car->SetHeadingTotLC(Vector3f(direction.X(),direction.Z(), -direction.Y()));
	Car->setHeadingAngle(resultAngle);
    }
	// if angles are =, no need to turn
    if (heading_angle == heading_target_angle) {
       // CLog::GetLog().Write(LOG_MISC, "Attempting to turn Right");
	//	Car->SetLTurn(false);
	//	Car->SetRTurn(false);
      // Car->SetHeadingTotLC(Vector3f(direction.X(),direction.Z(), -direction.Y()));
	//Car->setHeadingAngle(resultAngle);
    }
	return OK;
}

bool COpponentAI::Start()
{
	/*
	if (!CGameStateManager::GetGameStateManagerPtr()) return false;
	if (!CGameStateManager::GetGameStateManagerPtr()->
		GetScenePtr()) return false;
	std::vector<CEntity*>* Entities = CGameStateManager::GetGameStateManagerPtr()->
		GetScenePtr()->TEMPGetEntities();
	if (!Entities->size()) return false;
*/
	std::vector<CEntity*>* Entities = CGameStateManager::GetGameStateManagerPtr()->
		GetScenePtr()->TEMPGetEntities();

	// Find the COpponentVehicles from the scene and insert them into the Cars vector
	std::vector<CEntity*>::iterator thisEntity = Entities->begin();
	while (thisEntity != Entities->end()) {
		if ((*(*thisEntity)->GetEntityType()) == "COpponentVehicle")
			m_pCars.push_back((COpponentVehicle*)(*thisEntity));
		thisEntity++;
	}

	return true;
}

void COpponentAI::Update()
{CLog::GetLog().Write(LOG_MISC, "In AI update");
	if (m_pCars.empty()) return;

	std::vector<COpponentVehicle*>::iterator thisCar;
	switch (CAppStateManager::GetAppManPtr()->GetAppState()) {
	case STATE_PRE_GAME: // Is there anything to be done here?
		break;
	case STATE_IN_GAME:
		for (thisCar = m_pCars.begin(); thisCar != m_pCars.end(); thisCar++) {
		/*	// turning:
            CLog::GetLog().Write(LOG_MISC, "In AI update");
			if ((*thisCar)->reachedHeadingTarget()) {
				(*thisCar)->SetLTurn(false);
				(*thisCar)->SetRTurn(false);
			}
            
            if((*thisCar)->GetLTurn() || (*thisCar)->GetRTurn()) {
				setDirection(*thisCar);
			}

            if (isAtWaypoint(*thisCar)) 
              {
                (*thisCar)->incNext(); // new next target waypoint
				setDirection(*thisCar);	
			}

			// accelerate/decelerate:
			if ((*thisCar)->GetVehicleVelocityWC().Length() < VAI_CARS_VEL) {
				(*thisCar)->SetGas(true); (*thisCar)->SetBrake(false);
			}
			if ((*thisCar)->GetVehicleVelocityWC().Length() > VAI_CARS_VEL) {
				(*thisCar)->SetBrake(true); (*thisCar)->SetGas(false);
			}
            // NOTE: vehicle current velocity will rarely ever be EXACTLY VAI_CARS_VEL
			// Therefore, gas and brake are probably going to alternate.
			// This can be fixed if necessary bay testing to see if current velocity falls
			// within a range rather than an exact value.
			// ALSO: we can give each Opponent vehicle its own standard velocity if desired.
            //Rams add to brake at last waypoint (after reaching it)
            if (isAtWaypoint((*thisCar)) && (*thisCar)->Next()->getLastWay()) {
                (*thisCar)->lastWPReached = true;
            }
            //Kind of shitty way to do this, but hey it works-> will fix later
            CLog::GetLog().Write(LOG_DEBUGOVERLAY,112, "Vehicle Velocity: %f", (*thisCar)->GetVehicleVelocityWC().Length());
            
            if ((*thisCar)->lastWPReached){ 
            (*thisCar)->SetBrake(true); (*thisCar)->SetGas(false);
            
             if ((*thisCar)->GetVehicleVelocityWC().Length()<=0.2)
               (*thisCar)->raceOver = true; 
            }
            if((*thisCar)->raceOver){
              (*thisCar)->SetBrake(false); (*thisCar)->SetGas(false);}
			
		}*/
          if (isAtWaypoint(*thisCar)) 
              {
                (*thisCar)->incNext(); // new next target waypoint
				setDirection(*thisCar);
                CLog::GetLog().Write(LOG_DEBUGOVERLAY, 111, "At WP");
			}
          
            if ((*thisCar)->reachedHeadingTarget()) {
				//(*thisCar)->SetLTurn(false);
				//(*thisCar)->SetRTurn(false);
                //(*thisCar)->SetGas(true);
                CLog::GetLog().Write(LOG_DEBUGOVERLAY, 111, "Reached Heading Target");
			}
            else
            {
             setDirection(*thisCar);
             CLog::GetLog().Write(LOG_DEBUGOVERLAY, 111, "Not at HT Yet");
            }
			// accelerate/decelerate:
			if ((*thisCar)->GetVehicleVelocityWC().Length() < VAI_CARS_VEL) {
				(*thisCar)->SetGas(true); (*thisCar)->SetBrake(false);
			}
			if ((*thisCar)->GetVehicleVelocityWC().Length() > VAI_CARS_VEL) {
				(*thisCar)->SetBrake(true); (*thisCar)->SetGas(false);
			}
            // NOTE: vehicle current velocity will rarely ever be EXACTLY VAI_CARS_VEL
			// Therefore, gas and brake are probably going to alternate.
			// This can be fixed if necessary bay testing to see if current velocity falls
			// within a range rather than an exact value.
			// ALSO: we can give each Opponent vehicle its own standard velocity if desired.
            //Rams add to brake at last waypoint (after reaching it)
            if (isAtWaypoint((*thisCar)) && (*thisCar)->Next()->getLastWay()) {
                (*thisCar)->lastWPReached = true;
                
            }
            //Kind of shitty way to do this, but hey it works-> will fix later
            CLog::GetLog().Write(LOG_DEBUGOVERLAY,112, "Vehicle Velocity: %f", (*thisCar)->GetVehicleVelocityWC().Length());
            if ((*thisCar)->lastWPReached){ 
                  (*thisCar)->SetBrake(true); (*thisCar)->SetGas(false);
            
                if ((*thisCar)->GetVehicleVelocityWC().Length()<=0.2)
                {(*thisCar)->raceOver = true;(*thisCar)->SetLTurn(false);
                (*thisCar)->SetRTurn(false);} 
            }
              if((*thisCar)->raceOver){
                (*thisCar)->SetBrake(false); (*thisCar)->SetGas(false);
              }
        }
		break;
	default:; // Program should never get here
	}
}
	

// Careful, the following 2 functions don't add Entities to scene
int COpponentAI::setCars(std::vector<COpponentVehicle*> Cars)
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

