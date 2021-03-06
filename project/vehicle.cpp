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

#include "vehicle.h"
#include "timer.h"
#include "macros.h"

// Last minute hacks
static float theta = 0.0f;
static float skidTimeIn = 0.0f;
static float skidTimeOut = 0.0f;
static float skidPercent = 0.0f;

#define SKID_INTERPOLATE_TIME	1.0f
// End last minute hacks

float sgn(float x)
{
	if(x > 0) {
		return 1.0f;
	}
	else if(x < 0) {
		return -1.0f;
	}
	else {
		return 0.0f;
	}
}

static float sgnVel = 0.0f;

void CVehicle::Init()
{
	inputState.gas = false;
	inputState.brake = false;
	inputState.ebrake = false;
	inputState.lturn = false;
	inputState.rturn = false;

	b_playSkidSound = false;

	// Initialize position, acceleration, and velocity to zero
	accelerationLC = Vector3f(0.0f, 0.0f, 0.0f);
	velocityLC = Vector3f(0.0f, 0.0f, 0.0f);

	// Initialize angular values;
	angularAccelerationLC = Vector3f(0.0f, 0.0f, 0.0f);
	angularVelocityLC = Vector3f(0.0f, 0.0f, 0.0f);
	rotationLC = Vector3f(0.0f, 0.0f, 0.0f);
	// Initialize orientation
	headingWC = Vector3f(1.0f, 0.0f, 0.0f);
	velocityWC = Vector3f(1.0f, 0.0f, 0.0f);

	headingTotLC = Vector3f(0.0f, 0.0f, 0.0f);
	velocityTotLC = Vector3f(0.0f, 0.0f, 0.0f);

	// Calculate the weight of the vehicle.  W = mass * gravity
	vehicleWeight = vehicleMass * 9.81f;
	rpm = IDLE_RPM;
	driveWheelAngularVelocityRADS = 0.0f;
	driveWheelAngularAccelerationRADS = 0.0f;
	frontWheelAngularVelocityRADS = 0.0f;
	frontWheelAngularAccelerationRADS = 0.0f;

	steerAngleRADS = 0.0f;
	sideSlipAngleRADS = 0.0f;

	// Initialize the gear to first gear
	gear = 1;



	// Calculate the wheelbase, using the distance from the center
	// of gravity to the front axle (b), and the distance from
	// the center of gravity to the rear axle (c)
	L = b + c;

	// Calculate the difference between the CG and the roll center
	// height
	deltaHeight = float(fabs(height - rollCenterHeight));

	// Figure out what bank and gradient the vehicle sits on
	CalculateBankAndGradient();
	// Use the bank and gradient to figure out the initial weight distribution
	CalculateWeightDistribution();

	// Approximate values for a corvette are as follows:
	//		- coefficientOfAerodynamicFriction = 0.30
	//		- frontalArea = 2.2
	float airDensity = 1.29f;

	coefficientOfDrag = 0.5f * coefficientOfAerodynamicFriction * frontalArea * airDensity ;
	coefficientOfRollingResistance = coefficientOfDrag * 30.0f;

	// Init sound stuff
	CSoundCore::GetSoundCore().GetSoundEffect("car_idle", &engineIdle);
	CSoundCore::GetSoundCore().GetSoundEffect("car_engine", &engineRev);
	CSoundCore::GetSoundCore().GetSoundEffect("car_skid", &tireSkid);
	oldFreq = engineRev->GetFrequency();
	engineIdle->SetFrequency( engineIdle->GetFrequency() * 1.5f );

    //Rams Add
    for(int i=0; i<4;i++){
    checkPointTimes[i]=-1;
    }
	// Gib's additions
	ExtraneousForces = Vector3f(0.0f, 0.0f, 0.0f);
	isPlayer = false;


}


//--------------------------------------------------------------
//
//--------------------------------------------------------------
void CVehicle::CalculateBankAndGradient()
{
	/*
	// Gradient angle of the left side of the vehicle
	float leftGradient = 0.0f;
	// Gradient angle of the right side of the vehicle

	float rightGradient = 0.0f;
	float deltaZ;


	// Calculate the delta Z value between the 2 tires.
	deltaZ = FLTIRE.Z() - RLTIRE.Z();
	// Calculate the gradient angle between the 2 tires
	leftGradient = atan2(deltaZ, L);

	// Calculate the delta Z value between the 2 tires.
	deltaZ = FRTIRE.Z() - RRTIRE.Z();
	// Calculate the gradient angle between the 2 tires
	rightGradient = atan2(deltaZ, L);


	// Average the gradient of the left and right side of the vehicle
	gradientAngleRADS = (leftGradient + rightGradient) / 2.0f;


	// Bank angle for the front of the vehicle
	float frontBank = 0.0f;
	// Bank angle for the rear of the vehicle
	float rearBank = 0.0f;

	// Calculate the delta Z value between the 2 tires
	deltaZ = FLTIRE.Z() - FRTIRE.Z();
	// Calculate the bank angle between the 2 tires
	frontBank = atan2(deltaZ, trackWidth);

	// Calculate the delta Z value between the 2 tires
	deltaZ = RLTIRE.Z() - RRTIRE.Z();
	// Calculate the delta Z value between the 2 tires
	rearBank = atan2(deltaZ, trackWidth);

	// Average the bank angle from the front and rear of the vehicle
	bankAngleRADS = (frontBank + rearBank) / 2.0f;
*/

	///////////////////////////////////////
	// FOR NOW THE BANK AND GRADIENT = 0.0f;
	gradientAngleRADS = 0.0f;
	bankAngleRADS = 0.0f;
	///////////////////////////////////////

}

//--------------------------------------------------------------
//
//--------------------------------------------------------------
void CVehicle::CalculateWeightDistribution()
{
	float wFront, wRear;	// Weight distribution over the front and rear axle

	// Takes into consideration gradient of the vehicle, as well
	// as the acceleration that the vehicle is experiences due to
	// applying the gas or the brake.
	// (Braking is expressed as a negative acceleration)
	
	// Weight on the front axle
	wFront = vehicleWeight * ( (c/L) - ((height/L) * gradientAngleRADS) ) - (height/L) * vehicleMass * accelerationLC.X();
	// Weight on the rear axle
	wRear = vehicleWeight * ( (b/L) + ((height/L) * gradientAngleRADS) ) + (height/L) * vehicleMass * accelerationLC.X();


	// Following takes bank angle of the vehicle into consideration
	// as well as the lateral weight distribution change resulting
	// from cornering forces.

	// ** Lateral Forces due to cornering not implemented yet ** //
	// ** To be done when the cornering physics is finished ** //
	/*
	if(FLTIRE is higher than FRTIRE) {
		// More weight on the lower tire (Front Right Tire)
		weightDistribution[FRTIRE] = wFront * ( 0.5 + ((height/trackWidth) * bankAngleRADS));
		// Less weight on the higher tire (Front Left Tire)
		weightDistribution[FLTIRE] = wFront * ( 0.5 - ((height/trackWidth) * bankAngleRADS));
		
		// More weight on the lower tire (Rear Right Tire)
		weightDistribution[RRTIRE] = wFront * ( 0.5 + ((height/trackWidth) * bankAngleRADS));
		// Less weight on the higher tire (Rear Left Tire)
		weightDistribution[RLTIRE] = wFront * ( 0.5 - ((height/trackWidth) * bankAngleRADS));
	}
	else {
		// More weight on the lower tire (Front Left Tire)
		weightDistribution[FLTIRE] = wFront * ( 0.5 + ((height/trackWidth) * bankAngleRADS));
		// Less weight on the higher tire (Front Right Tire)
		weightDistribution[FRTIRE] = wFront * ( 0.5 - ((height/trackWidth) * bankAngleRADS));
		
		// More weight on the lower tire (Rear Left Tire)
		weightDistribution[RLTIRE] = wFront * ( 0.5 + ((height/trackWidth) * bankAngleRADS));
		// Less weight on the higher tire (Rear Right Tire)
		weightDistribution[RRTIRE] = wFront * ( 0.5 - ((height/trackWidth) * bankAngleRADS));
	}
	*/


	float maximumTractionForce = 7000.0f;

	/////////////////////////////////////////////////////////
	// FOR NOW WE DON"T NEED TO TAKE INTO ACCOUNT THE BANK
	// AND GRADIENT SINCE THEY ARE EQUAL TO 0
	/////////////////////////////////////////////////////////
	//vehicleWeight * ( (c/L) - ((height/L) * gradientAngleRADS) ) - (height/L) * vehicleMass * accelerationLC.X();
	weightDistribution[FRTIRE] = wFront/2.0f - (height/2.0f * wFront * accelerationLC.Y());
	if(weightDistribution[FRTIRE] < 3000) {
		weightDistribution[FRTIRE] = 3000.0f;
	}
	weightDistribution[FLTIRE] = wFront/2.0f + (height/2.0f * wFront * accelerationLC.Y());
	if(weightDistribution[FLTIRE] < 3000) {
		weightDistribution[FLTIRE] = 3000.0f;
	}
	weightDistribution[RRTIRE] = wRear/2.0f - (height/2.0f * wFront * accelerationLC.Y());
	if(weightDistribution[RRTIRE] < 4000) {
		weightDistribution[RRTIRE] = 4000.0f;
	}
	weightDistribution[RLTIRE] = wRear/2.0f + (height/2.0f * wFront * accelerationLC.Y());
	if(weightDistribution[RLTIRE] < 4000) {
		weightDistribution[RLTIRE] = 4000.0f;
	}
	///////////////////////////////////////////////////////////
	bool sgnSetAlready = false;

	if(b_dynamicTraction) {
		sgnSetAlready = true;
	}

	b_dynamicTraction = false;
	
	CLog::GetLog().Write(LOG_DEBUGOVERLAY, 64, "FR: %f", weightDistribution[FRTIRE]);
	CLog::GetLog().Write(LOG_DEBUGOVERLAY, 63, "FL: %f", weightDistribution[FLTIRE]);
	CLog::GetLog().Write(LOG_DEBUGOVERLAY, 62, "RR: %f", weightDistribution[RRTIRE]);
	CLog::GetLog().Write(LOG_DEBUGOVERLAY, 61, "RL: %f", weightDistribution[RLTIRE]);

	if(weightDistribution[FRTIRE] > maximumTractionForce) {
		b_dynamicTraction = true;
	}
	if(weightDistribution[FLTIRE] > maximumTractionForce) {
		b_dynamicTraction = true;
	}

	if(weightDistribution[RRTIRE] > maximumTractionForce) {
		b_dynamicTraction = true;
	}
	if(weightDistribution[RLTIRE] > maximumTractionForce) {
		b_dynamicTraction = true;
	}


	if(!inputState.gas && !inputState.brake) {
		b_dynamicTraction = false;
	}
	if(inputState.brake && (inputState.lturn || inputState.rturn)) {
		b_dynamicTraction = false;
	}
	if(inputState.ebrake) {
		b_dynamicTraction = true;
	}

	if(b_dynamicTraction && !sgnSetAlready) {
		//b_dynamicTraction = false;
		sgnVel = sgn(velocityLC.X());

		//if(skidTimeIn < SKID_INTERPOLATE_TIME) {
		
		//	skidTimeIn += CTimer::GetTimer().GetTimeElapsed();
		//	skidPercent = skidTimeIn / SKID_INTERPOLATE_TIME;
		//}
		//else {
		//
		skidPercent = 1.0f;
			//b_dynamicTraction = true;
		//}

		skidTimeOut = SKID_INTERPOLATE_TIME;
	}
	

	if(sgnSetAlready && !b_dynamicTraction) {
		b_dynamicTraction = true;
		
		if(skidTimeOut > 0.0f) {
			skidTimeOut -= CTimer::GetTimer().GetTimeElapsed();
			skidPercent = skidTimeOut / SKID_INTERPOLATE_TIME;
		}
		else {
			skidPercent = 1.0f;
			b_dynamicTraction = false;
		}

		skidTimeIn = 0.0f;
	}

			
	if(b_dynamicTraction) {
		CLog::GetLog().Write(LOG_DEBUGOVERLAY, 60, "DYNAMIC TRACTION");
	}
	else {
		CLog::GetLog().Write(LOG_DEBUGOVERLAY, 60, "STATIC TRACTION");
	}
}

//--------------------------------------------------------------
//
//--------------------------------------------------------------
void CVehicle::CalculateDrag()
{
	float velocityMagnitude = float(sqrt( pow(velocityLC.X(), 2) + pow(velocityLC.Y(), 2) + pow(velocityLC.Z(), 2)));
	Vector3f normalizedVelocityLC;

	if(velocityMagnitude < 1.0f) {
		drag = Vector3f(0.0f, 0.0f, 0.0f);
		return;
	}
	else {
		normalizedVelocityLC = velocityLC / velocityMagnitude;
	}
	drag = normalizedVelocityLC * coefficientOfDrag * velocityMagnitude * velocityMagnitude;
}

//--------------------------------------------------------------
// Note: As of right now, we calculate a rolling resistance
//       opposite to the velocity vector of the vehicle.  We
//		 might need to change it so that the force acts in the
//       opposite direction to the rolling tires.
//--------------------------------------------------------------
void CVehicle::CalculateRollingResistance()
{
	float velocityMagnitude = float(sqrt( pow(velocityLC.X(), 2) + pow(velocityLC.Y(), 2) + pow(velocityLC.Z(), 2)));
	Vector3f normalizedVelocityLC;

	if(velocityMagnitude < 1.0f) {
		rollingResistance = Vector3f(0.0f, 0.0f, 0.0f);
		return;
	}
	else {
		normalizedVelocityLC = velocityLC / velocityMagnitude;
	}
	rollingResistance = normalizedVelocityLC * coefficientOfRollingResistance * velocityMagnitude * velocityMagnitude;
}

//--------------------------------------------------------------
//
//--------------------------------------------------------------
void CVehicle::CalculateLongitudinalAcceleration()
{
	// Longitudinal acceleration acts along the X-axis of the
	// vehicle's local coordinate system.

	// Flongitudinal = Ftraction - Fbraking - Fdrag - Frollingresistance

	// Fdrag and Frollingresistance are known so all we need to
	// calculate now is Ftraction. (Traction force that the vehicle
	// is generating due to braking or accelerating.)

	// Since the only way for the vehicle to translate engine power into
	// motion is through the rear wheels, we need to know how much of
	// the vehicle's weight is distributed over the rear axle because this
	// affects how much traction we will get from the tires.

	float engineForce = 0.0f;
	float brakeForce = 0.0f;
	float tractionBrakeForce = 0.0f;
	float tractionDriveForce = 0.0f;
	float Flongitudinal = 0.0f;

	// TEMPORARY FORCE THAT SIMULATES THE RESISTANCE CREATED
	// BETWEEN ALL THE GEARS AND FRICTION INSIDE THE ENGINE.
	// SUPPOSED TO SLOW THE VEHICLE DOWN NICELY WHEN THE USER
	// LIFTS OFF THE GAS PEDAL.
	float engineBraking = (4000.0f) * sgn(velocityLC.X());
	float engineHelping = (4000.0f) * sgn(velocityLC.X());

	engineForce = (engineTorque * gearRatios[gear] * rearDiffRatio) / tireRadius;
	driveWheelTorque = engineForce * tireRadius;

	//CLog::GetLog().Write(LOG_GAMECONSOLE, "engineForce: %f", engineForce);

	tractionDriveForce = CalculateDriveTraction(engineForce);
	tractionDriveTorque = tractionDriveForce * tireRadius;

	brakeForce = brakeTorque / tireRadius;

	tractionBrakeForce = CalculateBrakeTraction(brakeForce);
	tractionBrakeTorque = tractionBrakeForce * tireRadius;

	if(sgn(velocityLC.X()) >= 0.0f) {
		if(inputState.gas  && !inputState.brake) {
			Flongitudinal = tractionDriveForce + engineHelping - drag.X() - rollingResistance.X();
		}
		else if(!inputState.gas && inputState.brake) {
			Flongitudinal = -tractionBrakeForce - drag.X() - rollingResistance.X() - engineBraking - engineHelping;
		}
		else if(inputState.gas && inputState.brake) {
			Flongitudinal = drag.X() - rollingResistance.X() - engineBraking / 4.0f;
		}
		else {
			Flongitudinal = drag.X() - rollingResistance.X() - engineBraking;
		}
	}
	else {
		if(inputState.gas && !inputState.brake) {
			Flongitudinal = tractionDriveForce - engineHelping - drag.X() - rollingResistance.X();
		}
		else if(!inputState.gas && inputState.brake) {
			Flongitudinal = engineHelping - tractionBrakeForce - drag.X() - rollingResistance.X();
		}
		else if(inputState.gas && inputState.brake) {
			Flongitudinal = drag.X() - rollingResistance.X() - engineBraking / 4.0f;
		}
		else {
			Flongitudinal = drag.X() - rollingResistance.X() - engineBraking;
		}
	}

	if(rpm == maximumRPM) {
		Flongitudinal = 1000.0f * -sgn(velocityLC.X());
	}

	accelerationLC.X() = Flongitudinal / (vehicleMass + rotatingMass);
}

//--------------------------------------------------------------
//
//--------------------------------------------------------------
float CVehicle::CalculateDriveTraction(float force)
{
	// First we need to calculate the maximum amount of 
	// force that the tires can put to the ground.  This
	// value is affected by the amount of weight on the rear
	// axle, which transfers into the weight on the rear tires.
	
	float rearAxleWeight = weightDistribution[RRTIRE] + weightDistribution[RLTIRE];

	// ***************** TWEAKABLE VALUE ******************* //
	float maximumTractionForce = 8000.0f;

	maximumTractionForce = (rearAxleWeight / maximumTractionForce) * maximumTractionForce;

	// Modulate the maximum amount of tractive force that the tires
	// are able to generate based on the type of tire.  Average street
	// tires can have a coefficient of about 1, and race cars have tires
	// that are usually in the range of 1.5 - 2.0

	if(!dynamicFriction) {
		maximumTractionForce *= coefficientOfTireFriction;
	}
	else {
		// ************** TWEAKABLE VALUE ******************* //
		// 0.8f ...
		maximumTractionForce *= (coefficientOfTireFriction * 0.8f);
	}

	if(force <= maximumTractionForce) {
		dynamicFriction = false;
		return force;
	}
	else {
		// Play the tire spinning sound here
		// Power exceeds tire traction capabilities
		dynamicFriction = true;
		return maximumTractionForce;
	}
}

//--------------------------------------------------------------
//
//--------------------------------------------------------------
float CVehicle::CalculateBrakeTraction(float force)
{
	//float rearAxleWeight = weightDistribution[RRTIRE] + weightDistribution[RLTIRE];
	float frontAxleWeight = weightDistribution[FRTIRE] + weightDistribution[FLTIRE];
	
	float maximumTractionForce = 8000.0f;

	maximumTractionForce = (force / maximumTractionForce) * frontAxleWeight;

	if(force > maximumTractionForce) {
		return maximumTractionForce;
	}
	else {
		return force;
	}

	return 0.0f;
	
	
}

//--------------------------------------------------------------
//
//--------------------------------------------------------------
float CVehicle::CalculateMaxTraction(float rearAxleWeight)
{
	// The slip ratio - traction curve is normalized to
	// a 5000 N weight acting on the tires in question.
	// In order to get the actual traction force we need
	// to multiply the tractive force generated by the curve
	// against the ratio rearAxleWeight / 6000.  This will
	// give us the actual maximum tractive force that the
	// tires can generate.

	// Graph details: The graph is linear, meaning that it
	// increases from 0 - 6% slip ratio where it hits the 
	// maximum tractive force of 6000 N.  After that the
	// graph decreases from 7 - 100%, where it finally comes 
	// to a value of 0 N.

	float normalizedTraction;

	if( float(fabs(slipRatio)) >= 0.0f && float(fabs(slipRatio)) <= 0.06f) {
		normalizedTraction = (slipRatio / 0.06f) * 6000.0f * sgn(slipRatio);
		return ((rearAxleWeight / 6000.0f) * normalizedTraction);
	}
	else {
		normalizedTraction = (slipRatio / 0.94f) * 6000.0f * sgn(slipRatio);
		return ((rearAxleWeight / 6000.0f) * normalizedTraction);
	}

}
//--------------------------------------------------------------
//
//--------------------------------------------------------------
void CVehicle::CalculateSlipRatio()
{
	// Determines the amount of slipping the is occuring
	// between the tire and the road.  This is what determines
	// the amount of engineForce that is actually able to be
	// put to the ground.

	if(velocityLC.X() == 0.0f) {
		slipRatio = 0.06f;
	}
	else {
		if(inputState.gas || inputState.brake) {
			slipRatio = (driveWheelAngularVelocityRADS * tireRadius - velocityLC.X()) / (float(fabs(velocityLC.X())) );
		}
		else {
			slipRatio = 0.0f;
		}
	}

	// $$$PHYSICSLOGS CLog::GetLog().Write(LOG_GAMECONSOLE, "SlipRatio: %f", slipRatio);
}

//--------------------------------------------------------------
//
//--------------------------------------------------------------
void CVehicle::CalculateEngineTorque()
{
	// Operating rpms for our vehicles will range from
	// 1000 <= x <= maximumRPM
	// For our purposes, the torque for our vehicles will be linear.
	// Thus, from 1000 rpm up until 90% of the maximumRPM, the torque
	// will increase.  After 90% of the maximumRPM, the torque will
	// decrease until the rpms hit the maximumRPM.

	if(!(inputState.gas)) {
		engineTorque = 0.0f;
		//CLog::GetLog().Write(LOG_GAMECONSOLE, "Gas not pressed.");
	}
	else if( float(rpm) <= (maximumRPM * 0.90f)) {
		// torque varies by 50%
		// At 1000 rpm we are at 50% torque output
		// At 90% of maxRPM we are at 100% torque output
		engineTorque = float(maximumEngineTorque * 0.50f + ( (rpm - 1000) / (((maximumRPM * 0.90f) - 1000) * 2.0f)));
	}
	else {
		
		// If the rpms are red lined, then we don't want to giving the player
		// any more power, because the vehicle will accelerate until drag
		// can overcome the torque.
		if(rpm == maximumRPM) {
			engineTorque = 0.0f;
			return;
		}
		// torque varies by 10%
		// At 90% of maxRPM we are at 100% torque output
		// At 100% maxRPM we are at 90% torque output
		engineTorque = float(maximumEngineTorque * ( 0.90f + (1 - (rpm / maximumRPM)) ) );

		if(engineTorque > maximumEngineTorque) {
			engineTorque = maximumEngineTorque;
		}
	}
}

//--------------------------------------------------------------
//
//--------------------------------------------------------------
void CVehicle::CalculateBrakeTorque()
{
	// Temporary
	if(inputState.brake && rpm < maximumRPM) {
		brakeTorque = maximumBrakeTorque;
	}
	else {
		brakeTorque = 0.0f;
	}
}
//--------------------------------------------------------------
//
//--------------------------------------------------------------
void CVehicle::CalculateRPM()
{
	// The drivetrain is connected from the engine to the drive wheel 
	// when the engine is declutched. This means that we can calculate
	// the rpm of the engine using the angular velocity of the drive 
	// wheel, the current gear ratio, and the rear differential ratio.

	if(float(fabs(driveWheelAngularVelocityRADS)) == 0.0f) {
		rpm = IDLE_RPM;
	}
	else {
		rpm = int(float(fabs(driveWheelAngularVelocityRADS)) * gearRatios[gear] * rearDiffRatio * 60.0f / (2.0f * PI_BOS)) + IDLE_RPM;

		if(rpm > maximumRPM) {
			rpm = int(maximumRPM);
		}
	}
}

//--------------------------------------------------------------
//  Note: The values calculated by this function require that
//		  the acceleration of the vehicle be calculated first.
//--------------------------------------------------------------
void CVehicle::CalculateWheelAngularAcceleration()
{
	float totalTorque;
	float rearAxleInertia;
	float wheelInertia;

	// *** Begin Rear Wheel (Drive Wheel) Acceleration Calculations ***
	driveWheelAngularAccelerationRADS = 0.0f;

	if(inputState.gas && !inputState.brake) {
		if(sgn(velocityLC.X()) > 0.0f) {
			totalTorque = driveWheelTorque - tractionDriveTorque;
		}
		else {
			totalTorque = 0.0f;
		}
	}
	else if(!inputState.gas && inputState.brake) {
		if(sgn(velocityLC.X()) < 0.0f) {
			totalTorque = brakeTorque - tractionBrakeTorque;
		}
		else {
			totalTorque = 0.0f;
		}
	}
	else if(!inputState.gas && !inputState.brake) {
		totalTorque = 0.0f;
	}
	else if(inputState.gas && inputState.brake) {
		// Have to implement this later.
		totalTorque = 0.0f;
	}

// $$$PHYSICSLOGS
	//CLog::GetLog().Write(LOG_GAMECONSOLE, "totalTorque: %f", totalTorque);
	//CLog::GetLog().Write(LOG_GAMECONSOLE, "driveWheelTorque: %f", driveWheelTorque);
	//CLog::GetLog().Write(LOG_GAMECONSOLE, "brakeTorque: %f", brakeTorque);

	wheelInertia = (tireMass * (tireRadius * tireRadius)) / 2.0f;

	// Multiply by 2 since there are 2 drive wheels
	// Could also add a little bit to take into account
	// the inertia of the axle itself.  I don't do this though.
	rearAxleInertia = wheelInertia * 2;

	// acceleration due to the acceleration of the vehicle along
	// the X axis
	//driveWheelAngularAccelerationRADS = accelerationLC.X() / tireRadius;
	
	// Is the player pressing the gas?
	if( (inputState.gas || inputState.brake) && (!(inputState.gas && inputState.brake))) {
		// extra acceleration due to the wheels slipping because the player
		// is pressing the gas pedal.
		driveWheelAngularAccelerationRADS += (totalTorque / rearAxleInertia);
	}

	// *** End Rear Wheel Acceleration Calculations ***
}

//--------------------------------------------------------------
//
//--------------------------------------------------------------
void CVehicle::InterpolateSteeringAngle(float deltaT)
{
	// Based on the player input, we will interpolate
	// the front tires' rotation about the local Z axis.
	// We don't want the wheels to turn instantaneously from
	// 0 - 40 DEGS, we want them to get over the course of about
	// 1 or 2 seconds. These values need to be tweaked.

	// Positive rotation, rotates counterclockwise around the Z axis.
	// Negative rotation, rotates clockwise around the Z axis.

	float newSteerAngle;

	float vehicleMaxSpeed = 60.0f;

	float speedScalar = 1 - velocityLC.X() / 60.0f;
	float maxTurnAngle = (MAX_STEER_ANGLE_RADS - MIN_STEER_ANGLE_RADS) * speedScalar + MIN_STEER_ANGLE_RADS; 
	

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
	}

	//CLog::GetLog().Write(LOG_GAMECONSOLE, "SteerAngle: %f", steerAngleRADS);
}

//--------------------------------------------------------------
//
//--------------------------------------------------------------
void CVehicle::CalculateLateralAcceleration()
{
	/*
	// Step 1: calculate slip angles for the front
	// and the rear axles.
	float slipAngleFront = 0.0f;
	float slipAngleRear = 0.0f;
	float FlateralRear = 0.0f;
	float FlateralFront = 0.0f;
	float corneringTorque = 0.0f;

	if(float(fabs(velocityLC.X())) > 0.1 ) {
		float rearAxleWeight = weightDistribution[RRTIRE] + weightDistribution[RLTIRE];
		float frontAxleWeight = weightDistribution[FRTIRE] + weightDistribution[FLTIRE];

		//sideSlipAngleRADS = float(atan2(velocityLC.Y(), velocityLC.X()));
		//sideSlipAngleRADS = float(atan2(velocityLC.Y(), velocityLC.X()));

		float mag = float(sqrt(float(pow(velocityLC.X(), 2)) + float(pow(velocityLC.Y(), 2))));
		
		//velocityLC.X() = mag * sgn(velocityLC.X());
		//velocityLC.Y() = 0.0f;
		//velocityLC.Z() = 0.0f;

		sideSlipAngleRADS = 0.0f;
		angularVelocityLC.Z() = 0.0f;

		slipAngleFront = sideSlipAngleRADS + ((angularVelocityLC.Z() * b) / L) - steerAngleRADS;
		slipAngleRear = sideSlipAngleRADS + ((angularVelocityLC.Z() * c) / L);

		//if(float(fabs(slipAngleFront)) > 0.0001f) {
			FlateralFront = CalculateLateralForce(slipAngleFront, frontAxleWeight);
		//}
		//if(float(fabs(slipAngleRear)) > 0.00001f) {
			FlateralRear = CalculateLateralForce(slipAngleRear, rearAxleWeight);
		//}

		accelerationLC.Y() = ((float(cos(steerAngleRADS)) * FlateralFront) + FlateralRear) / vehicleMass;

		
		corneringTorque = (FlateralFront*b) - (FlateralRear*c);

		// ******** should have inertia of the vehicle rather than
		//          vehicleMass.  Use it as a quick test for now ********* //
		angularAccelerationLC.Z() = corneringTorque / 500.0f;


	CLog::GetLog().Write(LOG_DEBUGOVERLAY, 41, "sideSlipAngleRADS: %f", sideSlipAngleRADS);
	CLog::GetLog().Write(LOG_DEBUGOVERLAY, 42, "slipAngleFront: %f", DEGREES(slipAngleFront));
	CLog::GetLog().Write(LOG_DEBUGOVERLAY, 43, "slipAngleRear: %f", DEGREES(slipAngleRear));
	CLog::GetLog().Write(LOG_DEBUGOVERLAY, 44, "FlateralFront: %f", FlateralFront);
	CLog::GetLog().Write(LOG_DEBUGOVERLAY, 45, "FlateralRear: %f", FlateralRear);
	CLog::GetLog().Write(LOG_DEBUGOVERLAY, 46, "accelerationLC.Y(): %f", accelerationLC.Y());
	CLog::GetLog().Write(LOG_DEBUGOVERLAY, 47, "corneringTorque: %f", corneringTorque);
	CLog::GetLog().Write(LOG_DEBUGOVERLAY, 48, "angularAccelerationLC.Z(): %f", angularAccelerationLC.Z());
	CLog::GetLog().Write(LOG_DEBUGOVERLAY, 49, "angularVELOCITY.Z(): %f", DEGREES(angularVelocityLC.Z()));
	CLog::GetLog().Write(LOG_DEBUGOVERLAY, 50, "steerAngleDEGS: %f", DEGREES(steerAngleRADS));
	CLog::GetLog().Write(LOG_DEBUGOVERLAY, 52, "velocityLC: %f %f %f", velocityLC.X(), velocityLC.Y(), velocityLC.Z());


	}
	*/
}

//--------------------------------------------------------------
//
//--------------------------------------------------------------
float CVehicle::CalculateLateralForce(float slipAngleRADS, float axleWeight)
{
	// Lateral force is a byproduct of slip angle ( difference between
	// the heading of the wheels, and the velocity vector of the vehicle ).

	// Starts at zero, increases to 5500 N at 3 degrees, then decreases to
	// 2250 N at 90 degrees linearly.
	float normalizedForce;
	float slipAngleDEGS = DEGREES(slipAngleRADS);

	if( float(fabs(slipAngleDEGS)) <= 3.0f) {
		normalizedForce =  (slipAngleDEGS/3.0f) * (10000.0f);
		return ( (axleWeight / 5000.0f) * normalizedForce * sgn(slipAngleDEGS));
	}
	else if(float(fabs(slipAngleDEGS)) <= 90.0f) {
		normalizedForce = ((90.0f - float(fabs(slipAngleDEGS)))/87.0f) * (10000.0f);
		return ( ( axleWeight / 5000.0f) * normalizedForce * sgn(slipAngleDEGS));
	}
	else {
		return 0.0f;
	}
}
//--------------------------------------------------------------
//
//--------------------------------------------------------------
void CVehicle::CalculateAutomaticGearShifting()
{
	// Vehicle will shift once it gets to 90% of the
	// maximum rpm for the engine.
	// Vehicle will shift down once it gets to 50% of
	// the maximum rpm for the vehicle

	// Shift up
	// We don't want to shift up if the user is pressing the brake
	// this is because the brake doubles as a reverse gear.
	if(rpm > (maximumRPM * 0.90f)  && !(inputState.brake) && velocityLC.X() > -0.1f) {
		if(gear >= 1 && gear < 5) {
			gear++;
		}
	}
	// Shift down
	else if(rpm < (maximumRPM * 0.60f)) {
		if(gear > 1 && gear <= 5) {
			gear--;
		}
	}
}

//--------------------------------------------------------------
//
//--------------------------------------------------------------
void CVehicle::CalculateTireAngularVelocity(float deltaT)
{
	// *** Begin Front Wheel Velocity Calculations ***
	float velocityMagnitude = float(sqrt(pow(velocityTotLC.X(), 2) + pow(velocityTotLC.Y(), 2) + pow(velocityTotLC.Z(), 2)));
	float angularVelocityMagnitude = velocityMagnitude / tireRadius;

	// Calculate the angle between the heading of the vehicle
	// and the acceleration vector.  To do this we will compute
	// the inverseCos(dotProduct(accel * heading) / (magnitude ( accel ) * magnitude ( heading)))
	// this gives us the angle in RADIANS.

	if(velocityMagnitude != 0.0f) {
		// HeadingLC = (1.0f, 0.0f, 0.0f), so when we dot product with it
		// we are left with u.x * headingLC.x = u.x * 1.0f = u.x
		float velocityDotHeading = velocityLC.X();
		
		// Don't need heading magnitude because it will always be 1.
		// This is because we are working along the local coordinate system,
		// and so the heading of the vehicle is always pointing directly
		// up the X-axis, with unit length.  Thus magnitude(heading) = 1.
		float cosTheta = velocityDotHeading / velocityMagnitude;
		float angleBetweenVelocityAndHeadingRADS = float(acos(cosTheta));

		// Check to see if the acceleration is occuring in the opposite direction of the tire
		// spin.  If it is then we need to negate the angularAccelMagnitude.
		if(float(fabs(angleBetweenVelocityAndHeadingRADS - steerAngleRADS)) > (PI_BOS / 2.0f)) {
			angularVelocityMagnitude *= -1.0f;
		}
		
		frontWheelAngularVelocityRADS = float(cos(DEGREES(steerAngleRADS + sideSlipAngleRADS))) * angularVelocityMagnitude;
	}
	else {
		frontWheelAngularVelocityRADS = 0.0f;
	}

	if(driveWheelAngularAccelerationRADS != 0.0f) {
		driveWheelAngularVelocityRADS += driveWheelAngularAccelerationRADS * deltaT;
	}
	else {
		if(velocityLC.X() > -0.1f)
			driveWheelAngularVelocityRADS = velocityMagnitude / tireRadius;
		else
			driveWheelAngularVelocityRADS = velocityLC.X() / tireRadius;
	}
	// *** End Front Wheel Acceleration Calculations ***


	//driveWheelAngularVelocityRADS += driveWheelAngularAccelerationRADS * deltaT;
	//frontWheelAngularVelocityRADS += frontWheelAngularAccelerationRADS * deltaT;
	//CLog::GetLog().Write(LOG_GAMECONSOLE, "DriveWheelAngVelocity: %f", driveWheelAngularVelocityRADS);
	//CLog::GetLog().Write(LOG_GAMECONSOLE, "FrontWheelAngVelocity: %f", frontWheelAngularVelocityRADS);
	// $$$PHYSICSLOGS CLog::GetLog().Write(LOG_GAMECONSOLE, "WheelAngVelocity: %f", driveWheelAngularVelocityRADS);

}

//--------------------------------------------------------------
//  Calculates the rotation of the wheels about the local Y axis.
//--------------------------------------------------------------
void CVehicle::CalculateTireRotation(float deltaT)
{
	for(int i=0;i<4;i++) {
			// Update the tire rotation about the local Y axis
			Vector3f currentRotation = tires[i]->GetRotationLC();
			Vector3f newRotation;

			if(i == FLTIRE || i == FRTIRE) {
				newRotation = Vector3f(currentRotation.X(), currentRotation.Y() + (frontWheelAngularVelocityRADS * deltaT), currentRotation.Z());
			}
			else {
				newRotation = Vector3f(currentRotation.X(), currentRotation.Y() + (driveWheelAngularVelocityRADS * deltaT), currentRotation.Z());
			}
			tires[i]->SetRotationLC(newRotation);
	}
}

//--------------------------------------------------------------
//
//--------------------------------------------------------------
void CVehicle::CalculateVehicleVelocity(float deltaT)
{
	velocityLC.X() = velocityLC.X() + (accelerationLC.X() * deltaT);
	velocityLC.Y() = 0.0f;
	velocityLC.Z() = 0.0f;

}

//--------------------------------------------------------------
//
//--------------------------------------------------------------
void CVehicle::CalculateVehiclePosition(float deltaT)
{
	// Is the car trying to turn?
//	if(float(fabs(steerAngleRADS)) > 0.0f  && float(fabs(velocityLC.X())) > 0.5f) {
		// Yes, so calculate the effects of the steering angle

	b_playSkidSound = false;

	if(!b_dynamicTraction) {
		theta = 0.0f;
		Vector3f rotPos(0.0f, 0.0f, 0.0f);
		float R = L / float(sin(steerAngleRADS));
		float M = float(tan(steerAngleRADS)) * L;
		float velocityMagnitude = float(sqrt(pow(velocityLC.X(), 2) + pow(velocityLC.Y(), 2) + pow(velocityLC.Z(), 2)));
		velocityMagnitude *= float(sin(steerAngleRADS));
		float D = velocityMagnitude * deltaT;
		float X = D / R;

		Vector3f A = tires[FRTIRE]->GetPositionLC();
		A.Z() = 0.0f;
		Vector3f B = tires[RRTIRE]->GetPositionLC();
		B.Y() = A.Y();
		B.Z() = 0.0f;
		Vector3f K = Vector3f(B.X(), B.Y() + M, B.Z());

		Vector3f AK = A - K;
		Vector3f BK = B - K;

		Vector3f AKprime;
		AKprime.X() = AK.X() * float(cos(X)) + AK.Y() * float(sin(X));
		AKprime.Y() = -AK.X() * float(sin(X)) + AK.Y() * float(cos(X));
		AKprime.Z() = AK.Z();

		Vector3f Aprime = AKprime + K;


		Vector3f BKprime;
		BKprime.X() = BK.X() * float(cos(X)) + BK.Y() * float(sin(X));
		BKprime.Y() = -BK.X() * float(sin(X)) + BK.Y() * float(cos(X));
		BKprime.Z() = BK.Z();
	
		Vector3f Bprime = BKprime + K;

		Vector3f G = A - B;
		G = G * ( c / (c + b) );

		Vector3f Gprime = Aprime - Bprime;
		Gprime = Gprime * ( c / (c + b) );

		Vector3f trans = Gprime - G;		
		
		Vector3f temp = velocityLC;
		
		temp.X() = temp.X() * float(cos(steerAngleRADS));
		temp.Y() = 0.0f;
		temp.Z() = 0.0f;

		temp += trans / deltaT;
		//if(sgn(steerAngleRADS != 0.0f))
		//	temp *= sgn(steerAngleRADS);

		Vector3f tempTrans = temp * deltaT;

		rotPos.X() = tempTrans.X() * cos(-rotationLC.Z()) + tempTrans.Y() * sin(-tempTrans.Z());
		rotPos.Y() = tempTrans.X() * -sin(-rotationLC.Z()) + tempTrans.Y() * cos(-tempTrans.Z());
		//rotPos.X() = tempTrans.X() * cos(-rotationLC.Z()) + tempTrans.Y() * sin(-rotationLC.Z());
		//rotPos.Y() = tempTrans.X() * -sin(-rotationLC.Z()) + tempTrans.Y() * cos(-rotationLC.Z());
		rotPos.Z() = tempTrans.Z();

		//if(skidPercent == 0.0f) {
			positionLC += rotPos;
		//}
		//else {
			// rotation rotPos by half angle,
			// then add it to positionLC
			// positionLC += rotPosRotHalf;
		//}

		Vector3f AB = A - B;
		Vector3f AprimeBprime = Aprime - Bprime;

		headingTotLC = Vector3f(1.0f, 0.0f, 0.0f);
		RotateVectorAboutLocalZ(&headingTotLC, rotationLC.Z());

		velocityTotLC = rotPos / deltaT;


		if(velocityLC.X() < -0.3f) {
			velocityTotLC *= -1.0f;
			headingTotLC *= -1.0f;
		}

		float ABdotAprimeBprime = AB.X() * AprimeBprime.X() + AB.Y() * AprimeBprime.Y() + AB.Z() * AprimeBprime.Z();
		float magAB = pow(AB.X(), 2) + pow(AB.Y(), 2) + pow(AB.Z(), 2);

		float rotRADS = float(acos(ABdotAprimeBprime / magAB));
		
		if(velocityLC.X() > -0.1f) {
			rotationLC.Z() += rotRADS * sgn(steerAngleRADS);
		}
		else {
			rotationLC.Z() -= rotRADS * sgn(steerAngleRADS);
		}

		CLog::GetLog().Write(LOG_DEBUGOVERLAY, 41, "tempTrans: %f %f %f", tempTrans.X(), tempTrans.Y()*sgn(steerAngleRADS), tempTrans.Z());
		CLog::GetLog().Write(LOG_DEBUGOVERLAY, 42, "B: %f %f %f", B.X(), B.Y(), B.Z());
		CLog::GetLog().Write(LOG_DEBUGOVERLAY, 43, "HeadingTotLC: %f %f %f", headingTotLC.X(), headingTotLC.Y(), headingTotLC.Z());
		CLog::GetLog().Write(LOG_DEBUGOVERLAY, 44, "VelocityTotLC: %f %f %f", velocityTotLC.X(), velocityTotLC.Y(), velocityTotLC.Z());
		CLog::GetLog().Write(LOG_DEBUGOVERLAY, 50, "steerAngleDEGS: %f", DEGREES(steerAngleRADS));
		
		//Vector3f test = velocityTotLC;
		//Vector3f test = (velocityTotLC - velTotOldLC) * deltaT;

		//Vector3f test = (0.0f, trans.Y(), 0.0f);
		//RotateVectorAboutLocalZ(&test, -rotationLC.Z());

		if(velocityLC.X() > 10.0f) {
			accelerationLC.Y() = (tempTrans.Y() / deltaT) * sgn(steerAngleRADS) * fabs(velocityLC.X() / 40.0f);
		}
		else {
			accelerationLC.Y() = 0.05f;
		}
		
		CLog::GetLog().Write(LOG_DEBUGOVERLAY, 37, "rotPos: %f %f %f", rotPos.X(), rotPos.Y(), rotPos.Z());
//		CLog::GetLog().Write(LOG_DEBUGOVERLAY, 38, "test.Y(): %f", test.Y());
//		CLog::GetLog().Write(LOG_DEBUGOVERLAY, 39, "accelerationLC.Y(): %f", accelerationLC.Y());

		}
		else {
			Vector3f rotPos(0.0f, 0.0f, 0.0f);
			float R = L / float(sin(steerAngleRADS));
			float M = float(tan(steerAngleRADS)) * L;
			float velocityMagnitude = float(sqrt(pow(velocityLC.X(), 2) + pow(velocityLC.Y(), 2) + pow(velocityLC.Z(), 2)));
			velocityMagnitude *= float(sin(steerAngleRADS));
			float D = velocityMagnitude * deltaT;
			float X = D / R;

			Vector3f A = tires[FRTIRE]->GetPositionLC();
			A.Z() = 0.0f;
			Vector3f B = tires[RRTIRE]->GetPositionLC();
			B.Y() = A.Y();
			B.Z() = 0.0f;
			Vector3f K = Vector3f(B.X(), B.Y() + M, B.Z());

			Vector3f AK = A - K;
			Vector3f BK = B - K;

			Vector3f AKprime;
			AKprime.X() = AK.X() * float(cos(X)) + AK.Y() * float(sin(X));
			AKprime.Y() = -AK.X() * float(sin(X)) + AK.Y() * float(cos(X));
			AKprime.Z() = AK.Z();

			Vector3f Aprime = AKprime + K;


			Vector3f BKprime;
			BKprime.X() = BK.X() * float(cos(X)) + BK.Y() * float(sin(X));
			BKprime.Y() = -BK.X() * float(sin(X)) + BK.Y() * float(cos(X));
			BKprime.Z() = BK.Z();
		
			Vector3f Bprime = BKprime + K;

			Vector3f G = A - B;
			G = G * ( c / (c + b) );

			Vector3f Gprime = Aprime - Bprime;
			Gprime = Gprime * ( c / (c + b) );

			Vector3f trans = Gprime - G;		
			
			Vector3f temp = velocityLC;
			
			temp.X() = temp.X() * float(cos(steerAngleRADS));
			temp.Y() = 0.0f;
			temp.Z() = 0.0f;

			temp += trans / deltaT;

			Vector3f tempTrans = temp * deltaT;

			rotPos.X() = tempTrans.X() * cos(-rotationLC.Z()) + tempTrans.Y() * sin(-tempTrans.Z());
			rotPos.Y() = tempTrans.X() * -sin(-rotationLC.Z()) + tempTrans.Y() * cos(-tempTrans.Z());
			//rotPos.X() = tempTrans.X() * cos(-rotationLC.Z()) + tempTrans.Y() * sin(-rotationLC.Z());
			//rotPos.Y() = tempTrans.X() * -sin(-rotationLC.Z()) + tempTrans.Y() * cos(-rotationLC.Z());
			rotPos.Z() = tempTrans.Z();

		//	if(velocityLC.X() < -0.3f) {
		//		velocityTotLC *= -1.0f;
		//		headingTotLC *= -1.0f;
		//	}

			CLog::GetLog().Write(LOG_DEBUGOVERLAY, 41, "tempTrans: %f %f %f", tempTrans.X(), tempTrans.Y()*sgn(steerAngleRADS), tempTrans.Z());
			CLog::GetLog().Write(LOG_DEBUGOVERLAY, 42, "B: %f %f %f", B.X(), B.Y(), B.Z());
			CLog::GetLog().Write(LOG_DEBUGOVERLAY, 43, "HeadingTotLC: %f %f %f", headingTotLC.X(), headingTotLC.Y(), headingTotLC.Z());
			CLog::GetLog().Write(LOG_DEBUGOVERLAY, 44, "VelocityTotLC: %f %f %f", velocityTotLC.X(), velocityTotLC.Y(), velocityTotLC.Z());
			CLog::GetLog().Write(LOG_DEBUGOVERLAY, 50, "steerAngleDEGS: %f", DEGREES(steerAngleRADS));
			
			//Vector3f test = velocityTotLC;
			//Vector3f test = (velocityTotLC - velTotOldLC) * deltaT;

			//Vector3f test = (0.0f, trans.Y(), 0.0f);
			//RotateVectorAboutLocalZ(&test, -rotationLC.Z());

			accelerationLC.Y() = (tempTrans.Y() / deltaT) * sgn(steerAngleRADS);
			
			CLog::GetLog().Write(LOG_DEBUGOVERLAY, 37, "rotPos: %f %f %f", rotPos.X(), rotPos.Y(), rotPos.Z());
	//		CLog::GetLog().Write(LOG_DEBUGOVERLAY, 38, "test.Y(): %f", test.Y());
	//		CLog::GetLog().Write(LOG_DEBUGOVERLAY, 39, "accelerationLC.Y(): %f", accelerationLC.Y());
			// We are in dynamic friction mode (ie, skidding, ebraking)
			float magVel = sqrt(pow(velocityTotLC.X(), 2) + pow(velocityTotLC.Y(), 2) + pow(velocityTotLC.Z(), 2));
			
			if(inputState.ebrake) {
				if(velocityLC.X() > -0.1f) {
					rotationLC.Z() += RADIANS(magVel * 6) * deltaT * sgn(steerAngleRADS);
					theta += RADIANS(magVel * 6) * deltaT * sgn(steerAngleRADS);
				}
				else {
					rotationLC.Z() += RADIANS(magVel * 6) * deltaT * sgn(steerAngleRADS);
					theta += RADIANS(magVel * 6) * deltaT * sgn(steerAngleRADS);
				}
			}
			else {
				if(velocityLC.X() > -0.1f) {
					rotationLC.Z() += RADIANS(magVel*2) * deltaT * sgn(steerAngleRADS);
					theta += RADIANS(magVel*2) * deltaT * sgn(steerAngleRADS);
				}
				else {
					rotationLC.Z() += RADIANS(magVel*2) * deltaT * sgn(steerAngleRADS);
					theta += RADIANS(magVel*2) * deltaT * sgn(steerAngleRADS);
				}
			}

			if(magVel > 1.0f) {
				b_playSkidSound = true;
			}
			else {
				b_playSkidSound = false;
			}

			velocityTotLC *= 0.995f;

			if(skidPercent == 1.0f) {
				positionLC += velocityTotLC * deltaT;
			}
			else {
				
				Vector3f a = velocityTotLC * skidPercent * deltaT;
				Vector3f b = rotPos * (1 - skidPercent);

				Vector3f temp12 = a + b;
				/*
				float velTotLCDotrotPos = (velocityTotLC.X()*deltaT) * rotPos.X() + (velocityTotLC.Y()*deltaT) * rotPos.Y() + (velocityTotLC.Z()*deltaT) * rotPos.Z();
				float magVel2 = sqrt(pow(velocityTotLC.X() * deltaT, 2) + pow(velocityTotLC.Y() * deltaT, 2) + pow(velocityTotLC.Z() * deltaT, 2));
				float magRotPos2 = sqrt(pow(rotPos.X(), 2) + pow(rotPos.Y(), 2) + pow(rotPos.Z(), 2));
				float magAB = magVel2 * magRotPos2;

				float rotRADS = float(acos(velTotLCDotrotPos / magAB));

				Vector3f temp12 = velocityTotLC * deltaT;
				CLog::GetLog().Write(LOG_MISC, "temp12: %f %f %f", temp12.X(), temp12.Y(), temp12.Z());
				CLog::GetLog().Write(LOG_MISC, "rotPos: %f %f %f", rotPos.X(), rotPos.Y(), rotPos.Z());
				CLog::GetLog().Write(LOG_MISC, "ROTRADS: %f", rotRADS);
				CLog::GetLog().Write(LOG_MISC, "magVel2: %f", magVel2);
				CLog::GetLog().Write(LOG_MISC, "magRotPos2: %f", magRotPos2);
				CLog::GetLog().Write(LOG_MISC, "magAB: %f", magAB);
				CLog::GetLog().Write(LOG_MISC, "velTotLCDotrotPos: %f", velTotLCDotrotPos);
				if(rotRADS > RADIANS(1.0f))
					RotateVectorAboutLocalZ(&temp12, rotRADS * (1-skidPercent));
				
				float magTemp12 = sqrt( temp12.X() * temp12.X() + temp12.Y() * temp12.Y() + temp12.Z() * temp12.Z());
				temp12 /= magTemp12;


				float test12 = fabs(magVel2 - magRotPos2);
				float abc = magVel2 + (test12 * (1 - skidPercent));

				test12 *= abc;
				positionLC += temp12;
				
				*/

				positionLC += temp12;
			}

			Vector3f test1 = velocityTotLC;

			RotateVectorAboutLocalZ(&test1, -rotationLC.Z());
			float magVel1 = sqrt(pow(test1.X(), 2) + pow(test1.Y(), 2) + pow(test1.Z(), 2));
			velocityLC = Vector3f(magVel1 * cos(theta), 0.0f, 0.0f);

			headingTotLC = Vector3f(1.0f, 0.0f, 0.0f);
			RotateVectorAboutLocalZ(&headingTotLC, rotationLC.Z());
			
			if(sgn(velocityLC.X()) != sgnVel) {
				velocityLC.X() *= -1.0f;
				headingTotLC *= -1.0f;
			}
	}
}

//--------------------------------------------------------------
//
//--------------------------------------------------------------
void CVehicle::CalculateVehicleAngularVelocity(float deltaT)
{
	angularVelocityLC = angularVelocityLC + (angularAccelerationLC * deltaT);
}

//--------------------------------------------------------------
//
//--------------------------------------------------------------
void CVehicle::CalculatePitchAndRoll(float deltaT)
{
	
	
	// Body rolls 2 degrees per G of acceleration
	// for right now.
	if(float(fabs(accelerationLC.X())) > 0.1f) {
		rotationLC.Y() += RADIANS(10.0f*deltaT) * sgn(accelerationLC.X());
		if(sgn(accelerationLC.X()) == sgn(rotationLC.Y())) {
			if(fabs(rotationLC.Y()) > RADIANS(0.5f)) {
				rotationLC.Y() = RADIANS(0.5f * sgn(accelerationLC.X()));
			}
		}
	}

	if(float(fabs(accelerationLC.Y())) > 0.1f) {
		rotationLC.X() += RADIANS(3.0f*deltaT) * sgn(accelerationLC.Y());
		if(sgn(accelerationLC.Y()) == sgn(rotationLC.X())) {
			if( fabs(rotationLC.X()) > RADIANS(3.0f)) {
				rotationLC.X() = RADIANS(3.0f) * sgn(accelerationLC.Y());
			}
		}
	}
	else if(!inputState.lturn && !inputState.rturn && float(fabs(rotationLC.X())) > RADIANS(1.0f)){
		rotationLC.X() -= RADIANS(15.0f*deltaT) * sgn(rotationLC.X());
		CLog::GetLog().Write(LOG_DEBUGOVERLAY, 46, "Rotation: %f %f %f", rotationLC.X(), rotationLC.Y(), rotationLC.Z());
	}



	
}

//--------------------------------------------------------------
//
//--------------------------------------------------------------
void CVehicle::UpdateVehiclePhysics()
{
	float deltaT = CTimer::GetTimer().GetTimeElapsed();

	CLog::GetLog().Write(LOG_DEBUGOVERLAY, 80, "velocityLC = (%f, %f, %f)",
		velocityLC.X(), velocityLC.Y(), velocityLC.Z());
	CLog::GetLog().Write(LOG_DEBUGOVERLAY, 81, "velocityWC = (%f, %f, %f)",
		velocityWC.X(), velocityWC.Y(), velocityWC.Z());
	
	CalculateAutomaticGearShifting();
	InterpolateSteeringAngle(deltaT);

	//	$$$PHYSICSLOGS
	//CLog::GetLog().Write(LOG_GAMECONSOLE, "Gear: %i", gear);
	//CLog::GetLog().Write(LOG_GAMECONSOLE, "RPM: %i", rpm);

	// Begin Variable Precalculation
	CalculateEngineTorque();
	CalculateBrakeTorque();
	CalculateDrag();
	CalculateRollingResistance();
	CalculateWeightDistribution();
	//CalculateSlipRatio();
	// End Variable Precalculation

	CalculateLongitudinalAcceleration();
	//CalculateLateralAcceleration();
	CalculateWheelAngularAcceleration();
	CalculateRPM();


	CalculateVehicleVelocity(deltaT);
	CalculateVehiclePosition(deltaT);
	CalculatePitchAndRoll(deltaT);
	//CalculateVehicleAngularVelocity(deltaT);
	//CalculateVehicleRotation(deltaT);


	// $$$PHYSICSLOGS
	//CLog::GetLog().Write(LOG_GAMECONSOLE, "DeltaT: %f", deltaT);

	//CLog::GetLog().Write(LOG_GAMECONSOLE, "Acceleration: %f %f %f", accelerationLC.X(), accelerationLC.Y(), accelerationLC.Z());
	//CLog::GetLog().Write(LOG_GAMECONSOLE, "Velocity: %f %f %f", velocityLC.X(), velocityLC.Y(), velocityLC.Z());
	//CLog::GetLog().Write(LOG_GAMECONSOLE, "Position: %f %f %f", positionLC.X(), positionLC.Y(), positionLC.Z());

	CLog::GetLog().Write(LOG_DEBUGOVERLAY, 101, "RPM: %d", rpm);
	CLog::GetLog().Write(LOG_DEBUGOVERLAY, 102, "GEAR: %d", gear);
	CLog::GetLog().Write(LOG_DEBUGOVERLAY, 103, "SPEED.X: %f (m/s)", velocityLC.X());
	CLog::GetLog().Write(LOG_DEBUGOVERLAY, 106, "CarPosition: %f %f %f", m_translate.X(), m_translate.Y(), m_translate.Z());
	CLog::GetLog().Write(LOG_DEBUGOVERLAY, 107, "CarRotation: %f %f %f", m_rotate.X(), m_rotate.Y(), m_rotate.Z());
	
	
	
	CalculateTireAngularVelocity(deltaT);
	CalculateTireRotation(deltaT);
	
	TransformLocalToWorldSpace();

/*
	// Sound adjustment
	if ( rpm < 1100 ) {
		engineRev->Stop();

		// Engine Idle
		if(engineIdle->IsPlaying() == false) {
			engineIdle->SetVolume( 0.8f );
			engineIdle->Play( TRUE, FALSE );
		}

	}
	else {
		engineIdle->Stop();
*/

		// Accelleration
		if(engineRev->IsPlaying() == false) {
			engineRev->SetVolume( 0.8f );
			engineRev->Play( TRUE, FALSE );
		}

		if(b_playSkidSound) {
			if(tireSkid->IsPlaying() == false) {
				tireSkid->SetVolume( 0.8f );
				tireSkid->Play( TRUE, FALSE );
			}
		}
		else {
			if(tireSkid->IsPlaying() == true) {
				tireSkid->Stop();
			}
		}

		// Modulate engine sound based on RPM
		long newFreq = 0;

		newFreq = ( ( (float) rpm / (float) (maximumRPM - IDLE_RPM) ) * oldFreq ) + (oldFreq / 3);
		engineRev->SetFrequency( newFreq );
//	}

		// Gib's additions
		if (disturbed) UpdateCollisionReaction();
}

//--------------------------------------------------------------
//
//--------------------------------------------------------------
void CVehicle::TransformLocalToWorldSpace()
{
	// Apply the transformation WC(X,Y,Z) = LC(X,-Z,Y) to the position of the vehicle
	Vector3f bodyTransWC(positionLC.X(), positionLC.Z()*(-1.0f), positionLC.Y());
	m_translate = bodyTransWC;

	// Update the car body rotation value for the renderer.
	Vector3f bodyRotWC(DEGREES(rotationLC.X()), DEGREES(rotationLC.Z()*(-1.0f)), DEGREES(rotationLC.Y()));
	m_rotate = bodyRotWC;
	
	// Then transform all 4 tires
	Vector3f tireTransformedLC;
	Vector3f tireTransLC;
	for(int i=0;i<4;i++) {
		Vector3f tireRotLC = tires[i]->GetRotationLC();
		if(i == FLTIRE || i == FRTIRE) {
			// We are dealing with front tires, so we need to factor in steer angle
			tireRotLC.Z() += steerAngleRADS;
		}

		tireTransLC = tires[i]->GetPositionLC();

		RotateVectorAboutLocalZ(&tireTransLC, rotationLC.Z());

		tireTransLC += positionLC;

		
		tires[i]->SetTranslate(Vector3f(tireTransLC.X(), tireTransLC.Z()*(-1.0f), tireTransLC.Y()));
		
		// Something fucked in the renderer.  I think it's gimbal locking my rotations.
		// I need to invert the right side tires' local Y axis rotation to get them to 
		// rotate correctly.
		if(i == FRTIRE || i == RRTIRE) {
			tires[i]->SetRotate(Vector3f( DEGREES(tireRotLC.X()), DEGREES(tireRotLC.Z()*(-1.0f)) + DEGREES(rotationLC.Z()*(-1.0f)), DEGREES(tireRotLC.Y())*(-1.0f)));
		}
		else {
			tires[i]->SetRotate(Vector3f( DEGREES(tireRotLC.X()), DEGREES(tireRotLC.Z()*(-1.0f)) + DEGREES(rotationLC.Z()*(-1.0f)), DEGREES(tireRotLC.Y()) ));
		}
	}

	headingWC = Vector3f( headingTotLC.X(), -headingTotLC.Z(), headingTotLC.Y());
	velocityWC = Vector3f( velocityTotLC.X(), -velocityTotLC.Z(), velocityTotLC.Y());

	
	// Gib's additions

	updateBoundingBoxes(bodyRotWC); // gib's addition

	/*
	if (ExtraneousForces.Length() > 0.1f) {
		m_translate += ExtraneousForces;
		m_box.Center() += ExtraneousForces;
		ExtraneousForces *= 0.5f;
		velocityLC = Vector3f(0.0f, 0.0f, 0.0f);
	}
	else ExtraneousForces = Vector3f(0.0f, 0.0f, 0.0f);
    */

}

void CVehicle::RotateVectorAboutLocalZ(Vector3f* param, float rotZRADS)
{
	float cosTheta = float(cos(rotZRADS));
	float sinTheta = float(sin(rotZRADS));

	Vector3f temp;

	temp.X() = (param->X() * cosTheta) - (param->Y() * sinTheta);
	temp.Y() = (param->X() * sinTheta) + (param->Y() * cosTheta);
	temp.Z() = param->Z();

	param->X() = temp.X();
	param->Y() = temp.Y();
	param->Z() = temp.Z();

}

// Gib's addition

void CVehicle::updateBoundingBoxes(Vector3f bodyRotWC)
{

	// update position
	m_box.Center() = m_translate;
	m_sphere.Center() = m_translate;

//	if (bodyRotWC.Y() == 0.0f) return;

	m_box.Axis(0) = headingWC;
	m_box.Axis(0).Normalize();

	m_box.Axis(2) = headingWC.Cross(m_box.Axis(1));
	m_box.Axis(2).Normalize();

	// Do the tires' axes
	for (int i = 0; i < 4; i++) {
		tires[i]->GetBoundingBox()->Axis(0) = headingWC;
		tires[i]->GetBoundingBox()->Axis(0).Normalize();
		tires[i]->GetBoundingBox()->Axis(2) = headingWC.Cross(m_box.Axis(1));
		tires[i]->GetBoundingBox()->Axis(2).Normalize();
	}

	// tire positions
	Vector3f TirePosCopy = Vector3f(FLTirePosition);
	Vector3f Axis0Copy = Vector3f(m_box.Axis(0));
	Vector3f Axis2Copy = Vector3f(m_box.Axis(2));
	Vector3f TirePosYValue = Vector3f(0.0f, TirePosCopy.Y(), 0.0f);

	Axis0Copy.Normalize(); Axis2Copy.Normalize();
	Axis0Copy *= TirePosCopy.X(); Axis2Copy *= TirePosCopy.Z();

	// These are equivalent to FLTirePosition except rotated properly
	Vector3f FLRotatedTirePos = Axis0Copy + Axis2Copy + TirePosYValue; 
	Vector3f FRRotatedTirePos = Axis0Copy + Axis2Copy*(-1.0f) + TirePosYValue;
	Vector3f RLRotatedTirePos = Axis0Copy*(-1.0f) + Axis2Copy + TirePosYValue;
	Vector3f RRRotatedTirePos = Axis0Copy*(-1.0f) + Axis2Copy*(-1.0f) + TirePosYValue;

	// Now, set their positions
	tires[FLTIRE]->GetBoundingBox()->Center() = m_box.Center() + FLRotatedTirePos; // FL
	tires[FRTIRE]->GetBoundingBox()->Center() = m_box.Center() + FRRotatedTirePos; // FR
	tires[RLTIRE]->GetBoundingBox()->Center() = m_box.Center() + RLRotatedTirePos; // RR
	tires[RRTIRE]->GetBoundingBox()->Center() = m_box.Center() + RRRotatedTirePos; // RL

	/*
	if (!isPlayer) {
		CLog::GetLog().Write(LOG_DEBUGOVERLAY, 50, "name = %s", GetName());
		CLog::GetLog().Write(LOG_DEBUGOVERLAY, 51, "sphere center = (%f, %f, %f)",
			m_sphere.Center().X(), m_sphere.Center().Y(), m_sphere.Center().Z());
		CLog::GetLog().Write(LOG_DEBUGOVERLAY, 52, "sphere radius = %f", m_sphere.Radius());
	}
	*/

}


// end Gib's addition

