#ifndef _VEHICLE_H
#define _VEHICLE_H

#include "WmlVector3.h"


using namespace Wml;

enum { FLTIRE, FRTIRE, RLTIRE, RRTIRE };

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

class CVehicle {

public:
	CVehicle() {};
	~CVehicle() {};
	void Init();
	void UpdateVehiclePhysics();

protected:
	
private:

	void CalculateBankAndGradient();
	void CalculateWeightDistribution();
	void CalculateDrag();
	void CalculateRollingResistance();
	void CalculateLongitudinalAcceleration();
	void CalculateSlipRatio();
	void CalculateEngineTorque();
	float CalculateTraction(float engineForce, float rearAxleWeight);
	float CalculateMaxTraction(float rearAxleWeight);

	// Required from .car file
	// Following data is what gives each car its driving characteristics
	float wheelbase;	// wheelbase = b+c, also known as L
	float L;			// L = wheelbase
	float b;			// b = distance from center of gravity to from axle
	float c;			// c = distance from center of gravity to rear axle
	float height;		// height is how high above the ground the CG lies
	float rollCenterHeight; // height of the roll center
	float deltaHeight;		// fabs(height - rollCenterHeight);
	float trackWidth;	// width of the vehicle, from left tire center -> right tire center
	float suspensionStiffness;	// Amount the suspension resists body roll
	float vehicleMass;	// mass of the vehicle
	float vehicleWeight; // weight of the vehicle W = mass * gravity
	float rotatingMass; // mass of the rotating parts of the vehicle
	float maximumTorque; // maximum amount of torque the vehicle can generate
	float maximumRPM;	// maximum rpm of the vehicle
	float drivetrainEfficiency;  // efficiency of the drivetrain to get power to the wheels (usually 70%)
	float rearDiffRatio;	// rear differential ratio
	float gearRatios[6];	// gear ratios 0[Reverse], 1[1st gear], 2[2nd gear] ....
	float tireRadius;		// radius of the tires
	float frontalArea;		// Frontal area of the vehicle (used for drag calculation)
	float coefficientOfAerodynamicFriction; // The shape of the vehicle affects this attribute, (more aerodynamic cars have lower coefficients)
	float coefficientOfRollingResistance;	// Approx. 30 times greater than the drag of a vehicle travelling at 1 m/s.
	float coefficientOfDrag;		// Approx. 1/30 of the coefficient of rolling resistance.
	float coefficientOfTireFriction; // Scalar value that determines how good the tires are.  Average Tires = 1, Racing Tires <= 2

	// Required from ingame queries
	// Following data is what state the car is currently in
	float bankAngleRADS;	// degree to which the car tipped up on its side
	float gradientAngleRADS;  // degree to which the car is tipped up on its nose
	
	float steerAngleRADS;	// angle between the direction of the vehicle, and the direction of the front wheel;
	float sideSlipAngleRADS;  // angle between the direction of the vehicle, and the direction of the velocity vector;

	float weightDistribution[4];  // distrubution of the vehicle's weight over the 4 tires.

	Vector3f drag;					// Drag force that acts in the opposite direction of the vehicle's motion
	Vector3f rollingResistance;		// Rolling resistance force due to the contact of the tires and the road surface

	int rpm;	// Vehicle's current rpm
	int gear;	// Vehicle's current gear;
	float engineTorque; // Engine's current torque output;

	float slipRatio;	// Slip ratio between the tire and the road

	float driveWheelAngularVelocityRADS; // angular velocity of the drive wheel (RADS/s)

	Vector3f accelerationLC;	// acceleration of the vehicle in local coordinate space
	Vector3f velocityLC;	// velocity of the vehicle in local coordinate space
	Vector3f positionLC;	// position of the vehicle in local coordinate space
};



#endif
