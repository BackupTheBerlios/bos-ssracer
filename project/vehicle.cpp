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

void CVehicle::Init()
{
	inputState.gas = false;
	inputState.brake = false;
	inputState.ebrake = false;
	inputState.lturn = false;
	inputState.rturn = false;
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

	// Calculate the weight of the vehicle.  W = mass * gravity
	vehicleWeight = vehicleMass * 9.81f;
	rpm = IDLE_RPM;
	driveWheelAngularVelocityRADS = 0.0f;
	driveWheelAngularAccelerationRADS = 0.0f;
	frontWheelAngularVelocityRADS = 0.0f;
	frontWheelAngularAccelerationRADS = 0.0f;

	// Initialize the gear to first gear
	gear = 1;



	// Calculate the wheelbase, using the distance from the center
	// of gravity to the front axle (b), and the distance from
	// the center of gravity to the rear axle (c)
	L = b + c;

	// Calculate the difference between the CG and the roll center
	// height
	deltaHeight = float(fabs(height - rollCenterHeight));

	steerAngleRADS = 0.0f;

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

	/////////////////////////////////////////////////////////
	// FOR NOW WE DON"T NEED TO TAKE INTO ACCOUNT THE BANK
	// AND GRADIENT SINCE THEY ARE EQUAL TO 0
	/////////////////////////////////////////////////////////
	weightDistribution[FRTIRE] = wFront / 2.0f;
	weightDistribution[FLTIRE] = wFront / 2.0f;
	weightDistribution[RRTIRE] = wRear / 2.0f;
	weightDistribution[RLTIRE] = wRear / 2.0f;
	///////////////////////////////////////////////////////////

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

	float engineForce;
	float brakeForce;
	float tractionBrakeForce;
	float tractionDriveForce;

	engineForce = (engineTorque * gearRatios[gear] * rearDiffRatio) / tireRadius;
	driveWheelTorque = engineForce * tireRadius;

	CLog::GetLog().Write(LOG_GAMECONSOLE, "engineForce: %f", engineForce);

	tractionDriveForce = CalculateDriveTraction(engineForce);
	tractionDriveTorque = tractionDriveForce * tireRadius;

	brakeForce = brakeTorque / tireRadius;

	tractionBrakeForce = CalculateBrakeTraction(brakeForce);
	tractionBrakeTorque = tractionBrakeForce * tireRadius;

	float Flongitudinal = tractionDriveForce - tractionBrakeForce - drag.X() - rollingResistance.X();

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
		CLog::GetLog().Write(LOG_GAMECONSOLE, "Gas not pressed.");
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
	CLog::GetLog().Write(LOG_GAMECONSOLE, "totalTorque: %f", totalTorque);
	CLog::GetLog().Write(LOG_GAMECONSOLE, "driveWheelTorque: %f", driveWheelTorque);
	CLog::GetLog().Write(LOG_GAMECONSOLE, "brakeTorque: %f", brakeTorque);

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
	// 0 - 25 DEGS, we want them to get over the course of about
	// 1 or 2 seconds. These values need to be tweaked.

	// Positive rotation, rotates counterclockwise around the Z axis.
	// Negative rotation, rotates clockwise around the Z axis.

	float newSteerAngle;

	// Interpolate the wheels to steer left ( +Z rotation )
	if(inputState.lturn) {
		newSteerAngle = (deltaT / STEER_ANGLE_TIME) * MAX_STEER_ANGLE_RADS + steerAngleRADS;
		if(newSteerAngle > MAX_STEER_ANGLE_RADS) {
			steerAngleRADS = MAX_STEER_ANGLE_RADS;
		}
		else {
			steerAngleRADS = newSteerAngle;
		}
	}
	// Interpolate the wheels to steer right ( -Z rotation )
	else if(inputState.rturn) {
		newSteerAngle = (deltaT / STEER_ANGLE_TIME) * MAX_STEER_ANGLE_RADS * -1.0f + steerAngleRADS;
		if(newSteerAngle < (MAX_STEER_ANGLE_RADS * -1.0f)) {
			steerAngleRADS = MAX_STEER_ANGLE_RADS * (-1.0f);
		}
		else {
			steerAngleRADS = newSteerAngle;
		}
	}
	// Interpolate the wheels back to 0
	else {	// Right Button nor Left Button is pressed
		newSteerAngle = (deltaT / STEER_ANGLE_TIME) * MAX_STEER_ANGLE_RADS;

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

	CLog::GetLog().Write(LOG_GAMECONSOLE, "SteerAngle: %f", steerAngleRADS);
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
	if(rpm > (maximumRPM * 0.90f)  && !(inputState.brake)) {
		if(gear >= 1 && gear < 5) {
			gear++;
		}
	}
	// Shift down
	else if(rpm < (maximumRPM * 0.40f)) {
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
	float velocityMagnitude = float(sqrt(pow(velocityLC.X(), 2) + pow(velocityLC.Y(), 2) + pow(velocityLC.Z(), 2)));
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
		driveWheelAngularVelocityRADS = velocityLC.X() / tireRadius;	
	}
	// *** End Front Wheel Acceleration Calculations ***


	//driveWheelAngularVelocityRADS += driveWheelAngularAccelerationRADS * deltaT;
	//frontWheelAngularVelocityRADS += frontWheelAngularAccelerationRADS * deltaT;
	CLog::GetLog().Write(LOG_GAMECONSOLE, "DriveWheelAngVelocity: %f", driveWheelAngularVelocityRADS);
	CLog::GetLog().Write(LOG_GAMECONSOLE, "FrontWheelAngVelocity: %f", frontWheelAngularVelocityRADS);
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
	velocityLC = velocityLC + (accelerationLC * deltaT);
}

//--------------------------------------------------------------
//
//--------------------------------------------------------------
void CVehicle::CalculateVehiclePosition(float deltaT)
{
	positionLC = positionLC + (velocityLC * deltaT);
}

//--------------------------------------------------------------
//
//--------------------------------------------------------------
void CVehicle::UpdateVehiclePhysics()
{
	float deltaT = CTimer::GetTimer().GetTimeElapsed();
	
	
	CalculateAutomaticGearShifting();
	InterpolateSteeringAngle(deltaT);

	//	$$$PHYSICSLOGS
	CLog::GetLog().Write(LOG_GAMECONSOLE, "Gear: %i", gear);
	CLog::GetLog().Write(LOG_GAMECONSOLE, "RPM: %i", rpm);

	// Begin Variable Precalculation
	CalculateEngineTorque();
	CalculateBrakeTorque();
	CalculateDrag();
	CalculateRollingResistance();
	CalculateWeightDistribution();
	//CalculateSlipRatio();
	// End Variable Precalculation

	CalculateLongitudinalAcceleration();
	CalculateWheelAngularAcceleration();
	CalculateRPM();



	CalculateVehicleVelocity(deltaT);
	CalculateVehiclePosition(deltaT);

	// $$$PHYSICSLOGS
	CLog::GetLog().Write(LOG_GAMECONSOLE, "DeltaT: %f", deltaT);

	CLog::GetLog().Write(LOG_GAMECONSOLE, "Acceleration: %f %f %f", accelerationLC.X(), accelerationLC.Y(), accelerationLC.Z());
	CLog::GetLog().Write(LOG_GAMECONSOLE, "Velocity: %f %f %f", velocityLC.X(), velocityLC.Y(), velocityLC.Z());
	CLog::GetLog().Write(LOG_GAMECONSOLE, "Position: %f %f %f", positionLC.X(), positionLC.Y(), positionLC.Z());

	
	CalculateTireAngularVelocity(deltaT);
	CalculateTireRotation(deltaT);
	
	TransformLocalToWorldSpace();
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
	Vector3f bodyRotWC(rotationLC.X(), rotationLC.Z()*(-1.0f), rotationLC.Y());
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
		tireTransLC += positionLC;
		tires[i]->SetTranslate(Vector3f(tireTransLC.X(), tireTransLC.Z()*(-1.0f), tireTransLC.Y()));
		
		// Something fucked in the renderer.  I think it's gimbal locking my rotations.
		// I need to invert the right side tires, local Y axis rotation to get them to 
		// rotate correctly.
		if(i == FRTIRE || i == RRTIRE) {
			tires[i]->SetRotate(Vector3f( DEGREES(tireRotLC.X()), DEGREES(tireRotLC.Z()*(-1.0f)), DEGREES(tireRotLC.Y())*(-1.0f)));
			//tires[i]->SetRotate(Vector3f(0.0f, 0.0f, DEGREES(tireRotLC.Y()*(-1.0f)) ));
		}
		else {
			tires[i]->SetRotate(Vector3f( DEGREES(tireRotLC.X()), DEGREES(tireRotLC.Z()*(-1.0f)), DEGREES(tireRotLC.Y()) ));
		}
	}
}


