#include "copponentvehicle.h"
#include "copponentai.h"
#include "macros.h"

COpponentVehicle::COpponentVehicle()
{
	m_vWPSequence[0].clear();
    m_vWPSequence[1].clear();
    m_vWPSequence[2].clear();
    m_vWPSequence[3].clear();
	m_vHeadingTargetWC = Vector3f(0.0f, 0.0f, 0.0f);
	m_vVelocityTargetWC = Vector3f(0.0f, 0.0f, 0.0f);
	m_Next = m_vWPSequence[0].begin();

	Init();

	m_strEntityType = "COpponentVehicle";
    lastWPReached = false;
    raceOver = false;
    //default dumb
    m_aiLevel = DUMB_AI;
}

COpponentVehicle::~COpponentVehicle()
{
	m_vWPSequence[0].clear();
    m_vWPSequence[1].clear();
    m_vWPSequence[2].clear();
    m_vWPSequence[3].clear();

}

int COpponentVehicle::incNext()
{
	if (m_Next == m_vWPSequence[0].end()-1)
		return GENERAL_ERROR;
    if ((*m_Next)->getType()==1) //If Branch Waypoint
    {
      if(getAILevel() == ADVANCED_AI)
      {
      m_Next = m_vWPSequence[(*m_Next)->getGoToPath()].begin(); 
      }
      else m_Next++;
    }
    else if((*m_Next)->getType()==2) //If Conjunction
    {
      m_Next = &m_vWPSequence[(*m_Next)->getCPath()][(*m_Next)->getCIndex()]; //Can only get here if in branch
    }
    else
	m_Next++;
	return OK;
}

int COpponentVehicle::decNext()
{
	if (m_Next == m_vWPSequence[0].begin())
		return GENERAL_ERROR;

	m_Next--;
	return OK;
}

int COpponentVehicle::setVelocityTarget(Vector3f* VT)
{
	if (!VT) return NULL_POINTER;

	m_vVelocityTargetWC = *VT;
	return OK;
}

int COpponentVehicle::setHeadingTarget(Vector3f* HT)
{
	if (!HT) return NULL_POINTER;

	m_vHeadingTargetWC = *HT;
	return OK;
}

int COpponentVehicle::setNext(std::vector<CWaypoint*>::iterator next)
{
	// Should check to see that next actually does point to an WP in the WPSequence vector
	m_Next = next;
	return OK;
}

int COpponentVehicle::setWPSequence(std::vector<CWaypoint*>* WPSeq)
{
	if (!WPSeq) return NULL_POINTER;
    CWaypoint * temp;
    temp = *WPSeq->begin();
    int path = temp->getPath();
    CLog::GetLog().Write(LOG_MISC, "Setting Path Sequence : %i", path);
	m_vWPSequence[path].clear();
	m_vWPSequence[path] = *WPSeq;
	return OK;
}

bool COpponentVehicle::reachedHeadingTarget()
{
	if (GetLTurn() && GetRTurn()) return true;

	// Procedure for finding angle from heading:
	//		Normalize HeadingWC
	//		Take the z value of normalized HeadingWC.
	//		Take the inverse sine of z
	//		That's your WC angle.

	// For HeadingWC
	Vector3f NormalizedHeadingWC = GetVehicleHeadingWC();
	NormalizedHeadingWC.Normalize();
	double heading_angle = asin(NormalizedHeadingWC.Z());

	// For HeadingTargetWC
	Vector3f NormalizedHeadingTargetWC = *HeadingTarget();

	NormalizedHeadingTargetWC.Normalize();
	double heading_target_angle = asin(NormalizedHeadingTargetWC.Z());

	// read: if turning left then
	//			if current heading WC angle will be greater than target untill target reached.
	//		 if turning right then
	//		    if current heading WC angle will be less than target untill target reached.
	if ((GetLTurn() && heading_angle < heading_target_angle) ||
		(GetRTurn() && heading_angle > heading_target_angle))
		return false;
	//else return true;
    else if (heading_angle==heading_target_angle)
      return true;
    else return false;
	// Note: assuming that if neither lturn or rturn = true, 
	// target heading already reached.
}

//Rams attempt at affecting steering directly
void COpponentVehicle::InterpolateSteeringAngle(float deltaT)
{
	// Based on the ai input, we will interpolate
	// the front tires' rotation about the local Z axis.
	// We don't want the wheels to turn instantaneously from
	// 0 - 40 DEGS, we want them to get over the course of about
	// 1 or 2 seconds. These values need to be tweaked.

	// Positive rotation, rotates counterclockwise around the Z axis.
	// Negative rotation, rotates clockwise around the Z axis.
float angle = getHeadingAngle();
    CLog::GetLog().Write(LOG_DEBUGOVERLAY, 115, "HEAD ANGLE: %f",angle);

    float pi = 3.14159;
    //float newSteerAngle;
    float speedScalar = 1 - velocityLC.X() / 60.0f;
float maxTurnAngle = (MAX_STEER_ANGLE_RADS - MIN_STEER_ANGLE_RADS) * speedScalar + MIN_STEER_ANGLE_RADS; 
	//float vehicleMaxSpeed = 60.0f;

	
if(inputState.lturn)
{
if(angle > maxTurnAngle) {
			steerAngleRADS = maxTurnAngle;
             CLog::GetLog().Write(LOG_DEBUGOVERLAY, 118, "MAX LEFT HIT!");
            //SetBrake(true);
		}
		else {
          CLog::GetLog().Write(LOG_DEBUGOVERLAY, 118, "NO MAX");
			steerAngleRADS = angle;
		}
}
else if(inputState.rturn)
{
  if(angle < (maxTurnAngle * -1.0f)) {
			steerAngleRADS = maxTurnAngle * (-1.0f);
		}
		else {
			steerAngleRADS = angle *-1;
		}
} //((2*pi)-angle)*-1;
    
	/*

	// Interpolate the wheels to steer left ( +Z rotation )
	if(inputState.lturn) {
		newSteerAngle = (deltaT / STEER_ANGLE_TIME) * maxTurnAngle + steerAngleRADS;
		if(newSteerAngle > maxTurnAngle) {
			steerAngleRADS = maxTurnAngle;
		}
		else {
			steerAngleRADS = newSteerAngle;
		}
	}
	// Interpolate the wheels to steer right ( -Z rotation )
	else if(inputState.rturn) {
		newSteerAngle = (deltaT / STEER_ANGLE_TIME) * maxTurnAngle * -1.0f + steerAngleRADS;
		if(newSteerAngle < (maxTurnAngle * -1.0f)) {
			steerAngleRADS = maxTurnAngle * (-1.0f);
		}
		else {
			steerAngleRADS = newSteerAngle;
		}
	}
	// Interpolate the wheels back to 0
	else {	// Right Button nor Left Button is pressed
		newSteerAngle = (deltaT / STEER_ANGLE_TIME) * maxTurnAngle;

		if(steerAngleRADS >= 0.0f) {
			if((steerAngleRADS - newSteerAngle) >= 0.0f) {
				steerAngleRADS -= newSteerAngle;
			}
			else {
				steerAngleRADS = 0.0f;
			}
		}
		else if(steerAngleRADS < 0.0f) {
			if((steerAngleRADS + newSteerAngle) < 0.0f) {
				steerAngleRADS += newSteerAngle;
			}
			else {
				steerAngleRADS = 0.0f;
			}
		}
	}*/

	//CLog::GetLog().Write(LOG_GAMECONSOLE, "SteerAngle: %f", steerAngleRADS);
}
