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

void CVehicle::Init()
{
	// Initialize position, acceleration, and velocity to zero
	accelerationLC = Vector3f(0.0f, 0.0f, 0.0f);
	velocityLC = Vector3f(0.0f, 0.0f, 0.0f);
	positionLC = Vector3f(0.0f, 0.0f, 0.0f);

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
	//		- coefficientOfFriction = 0.30
	//		- frontalArea = 2.2
	float airDensity = 1.29f;

	coefficientOfDrag = coefficientOfAerodynamicFriction * frontalArea * airDensity ;
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

	drag = coefficientOfDrag * velocityMagnitude * velocityLC;
}

//--------------------------------------------------------------
//
//--------------------------------------------------------------
void CVehicle::CalculateRollingResistance()
{
	rollingResistance = coefficientOfRollingResistance * velocityLC;
}

//--------------------------------------------------------------
//
//--------------------------------------------------------------
void CVehicle::CalculateLongitudinalAcceleration()
{
	// Longitudinal acceleration acts along the X-axis of the
	// vehicle's local coordinate system.

	// Flongitudinal = Ftraction + Fdrag + Frollingresistance

	// Fdrag and Frollingresistance are known so all we need to
	// calculate now is Ftraction. (Traction force that the vehicle
	// is generating due to braking or accelerating.)

	// Since the only way for the vehicle to translate engine power into
	// motion is through the rear wheels, we need to know how much of
	// the vehicle's weight is distributed over the rear axle because this
	// affects how much traction we will get from the tires.

	float rearAxleWeight = weightDistribution[RRTIRE] + weightDistribution[RLTIRE];

	float engineForce = (engineTorque * gearRatios[gear] * rearDiffRatio) / tireRadius;
	driveWheelTorque = engineForce * tireRadius;

	float tractionForce = CalculateTraction(engineForce, rearAxleWeight);
	tractionTorque = tractionForce * tireRadius;

	float Flongitudinal = tractionForce - drag.X() - rollingResistance.X();

	accelerationLC.X() = Flongitudinal / (vehicleMass + rotatingMass);
}

//--------------------------------------------------------------
//
//--------------------------------------------------------------
float CVehicle::CalculateTraction(float engineForce, float rearAxleWeight)
{
	// First we need to calculate the maximum amount of 
	// force that the tires can put to the ground.  This
	// value is affected by the amount of weight on the rear
	// axle, which transfers into the weight on the rear tires.
	float maximumTractionForce = CalculateMaxTraction(rearAxleWeight);

	// Modulate the maximum amount of tractive force that the tires
	// are able to generate based on the type of tire.  Average street
	// tires can have a coefficient of about 1, and race cars have tires
	// that are usually in the range of 1.5 - 2.0
	maximumTractionForce *= coefficientOfTireFriction;

	if(engineForce <= maximumTractionForce) {
		return engineForce;
	}
	else {
		// Play the tire spinning sound here
		// Power exceeds tire traction capabilities
		return maximumTractionForce;
	}
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
	// against the ratio rearAxleWeight / 5000.  This will
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
	slipRatio = (driveWheelAngularVelocityRADS * tireRadius - velocityLC.X()) / (float(fabs(velocityLC.X())) );
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

	if(rpm <= 1000) {
		// No torque at or below 1000 rpm.
		rpm = 1000;
		engineTorque = 0.0f;
	}
	else if( float(rpm) <= (maximumRPM * 0.90f) ) {
		// torque varies by 50%
		// At 1000 rpm we are at 50% torque output
		// At 90% of maxRPM we are at 100% torque output
		engineTorque = float(maximumTorque * 0.50f + ( (rpm - 1000) / (((maximumRPM * 0.90f) - 1000) * 2.0f)));
	}
	else {
		// torque varies by 10%
		// At 90% of maxRPM we are at 100% torque output
		// At 100% maxRPM we are at 90% torque output
		engineTorque = float(maximumTorque * ( 0.90f + (1 - (rpm / maximumRPM)) ) );
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
	rpm = int(driveWheelAngularVelocityRADS * gearRatios[gear] * rearDiffRatio * 60.0f / (2.0f * PI_BOS));
}

//--------------------------------------------------------------
//
//--------------------------------------------------------------
void CVehicle::CalculateDriveWheelAngularAcceleration()
{
	float totalTorque;
	float rearAxleInertia;
	float wheelInertia;

	// NOT IMPLEMENTED YET.  ON THE TO DO LIST
	float brakeTorque = 0.0f;

	totalTorque = driveWheelTorque - tractionTorque - brakeTorque;

	wheelInertia = (tireMass * (tireRadius * tireRadius)) / 2.0f;

	// Multiply by 2 since there are 2 drive wheels
	// Could also add a little bit to take into account
	// the inertia of the axle itself.  I don't do this though.
	rearAxleInertia = wheelInertia * 2;

	driveWheelAngularAccelerationRADS = totalTorque / rearAxleInertia;
}

//--------------------------------------------------------------
//
//--------------------------------------------------------------
void CVehicle::InterpolateTireRotation(float deltaT)
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
	if(rpm > (maximumRPM * 0.90f)) {
		if(gear >= 1 && gear < 5) {
			gear++;
		}
	}
	// Shift down
	else if(rpm < (maximumRPM * 0.50f)) {
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

}

//--------------------------------------------------------------
//
//--------------------------------------------------------------
void CVehicle::CalculateTireRotation(float deltaT)
{

}

//--------------------------------------------------------------
//
//--------------------------------------------------------------
void CVehicle::CalculateVehicleVelocity(float deltaT)
{

}

//--------------------------------------------------------------
//
//--------------------------------------------------------------
void CVehicle::CalculateVehiclePosition(float deltaT)
{

}

//--------------------------------------------------------------
//
//--------------------------------------------------------------
void CVehicle::UpdateVehiclePhysics()
{
	

	// Begin Variable Precalculation
	CalculateEngineTorque();
	CalculateDrag();
	CalculateRollingResistance();
	CalculateSlipRatio();
	// End Variable Precalculation

	CalculateLongitudinalAcceleration();
	CalculateDriveWheelAngularAcceleration();
	CalculateRPM();

	float deltaT = CTimer::GetTimer().GetTimeElapsed();

	CalculateVehicleVelocity(deltaT);
	CalculateVehiclePosition(deltaT);
	
	CalculateTireAngularVelocity(deltaT);
	CalculateTireRotation(deltaT);
	
	TransformLocalToWorldSpace();
}

//--------------------------------------------------------------
//
//--------------------------------------------------------------
void CVehicle::TransformLocalToWorldSpace()
{
	// First transform the vehicle
	// Apply transformation matrix to the


	// Then transform all 4 tires
}


