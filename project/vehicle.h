#ifndef _VEHICLE_H
#define _VEHICLE_H

#include "entity.h"
#include "tire.h"
#include "WmlVector3.h"

using namespace Wml;

enum { FLTIRE, FRTIRE, RLTIRE, RRTIRE };

// Maximum angle (in rads) that the front tires can turn
#define MAX_STEER_ANGLE_RADS	0.43f
// Number of seconds for the tires to get from 0 - MAX_STEER_ANGLE_RADS
#define STEER_ANGLE_TIME		1.0f



typedef struct ___X___ {
	bool lturn;
	bool rturn;
	bool gas;
	bool brake;
	bool ebrake;
} tInputState;

class CVehicle : public CEntity {

public:
	CVehicle() { for(int i=0;i<4;i++) { tires[i] = new CTire(); } };
	~CVehicle() {};
	void Init();
	void UpdateVehiclePhysics();

	void SetTire(CTire* tire, int index) { if(index >= 0 && index <=3) { tires[index] = tire; } };
	CTire* GetTire(int index) { if(index >= 0 && index <=3) { return tires[index]; } return NULL; };

	// Set methods for the vehicle's empirical data
	void SetB(float param) { b = param; };
	void SetC(float param) { c = param; };
	void SetHeight(float param) { height = param; };
	void SetRollCenterHeight(float param) { rollCenterHeight = param; };
	void SetTrackWidth(float param) { trackWidth = param; };
	void SetSuspensionStiffness(float param) { suspensionStiffness = param; };
	void SetVehicleMass(float param) { vehicleMass = param; };
	void SetRotatingMass(float param) { rotatingMass = param; };
	void SetTireMass(float param) { tireMass = param; };
	void SetMaximumTorque(float param) { maximumTorque = param; };
	void SetMaximumRPM(float param) { maximumRPM = param; };
	void SetDrivetrainEfficiency(float param) { drivetrainEfficiency = param; };
	void SetRearDiffRatio(float param) { rearDiffRatio = param; };
	void SetGearRatios(float *param) { for(int i=0;i<6;i++) { gearRatios[i] = param[i]; } };
	void SetTireRadius(float param) { tireRadius = param; };
	void SetFrontalArea(float param) { frontalArea = param; };
	void SetCoefficientOfAerodynamicFriction(float param) { coefficientOfAerodynamicFriction = param; };
	void SetCoefficientOfTireFriction(float param) { coefficientOfTireFriction = param; };

	// Set other member variables
	void SetPositionLC(Vector3f param) { positionLC = param; };

	// Set methods for the vehicle's input state
	void SetGas(bool gas) { inputState.gas = gas; };
	void SetBrake(bool brake) { inputState.brake = brake; };
	void SetLTurn(bool lturn) { inputState.lturn = lturn; };
	void SetRTurn(bool rturn) { inputState.rturn = rturn; };
	void SetEBrake(bool ebrake) { inputState.ebrake = ebrake; };

	// Get methods for the vehicle's input state
	bool GetGas() { return inputState.gas; };
	bool GetBrake() { return inputState.brake; };
	bool GetEBrake() { return inputState.ebrake; };
	bool GetLTurn() { return inputState.lturn; };
	bool GetRTurn() { return inputState.rturn; };

protected:
	
private:

	void CalculateBankAndGradient();
	void CalculateWeightDistribution();
	void CalculateDrag();
	void CalculateRollingResistance();
	void CalculateLongitudinalAcceleration();
	void CalculateSlipRatio();
	void CalculateEngineTorque();
	void CalculateRPM();
	void CalculateDriveWheelAngularAcceleration();
	void CalculateVehicleVelocity(float deltaT);
	void CalculateVehiclePosition(float deltaT);
	void CalculateTireAngularVelocity(float deltaT);
	void CalculateTireRotation(float deltaT);
	void CalculateBodyOrientation();


	float CalculateTraction(float engineForce, float rearAxleWeight);
	float CalculateMaxTraction(float rearAxleWeight);

	void InterpolateTireRotation(float deltaT);
	void CalculateAutomaticGearShifting();

	void TransformLocalToWorldSpace();

	// Required from .car file
	// Following data is what gives each car its driving characteristics
	float L;			// L = b + c = wheelbase of the vehicle
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
	float tireMass;		// mass of each of the tires on the vehicle
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
	CTire *tires[4];		// Pointers to the 4 tires.

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
	float driveWheelTorque; // Torque generated at the drive wheel by the engine
	float tractionTorque;	// Torque generated on the drive wheel due to friction. (opposes driveWheelTorque)
	float brakeTorque;		// Torque generated on the drive wheel due to application of the brakes. (opposes driveWheelTorque)
	float slipRatio;	// Slip ratio between the tire and the road

	float driveWheelAngularVelocityRADS; // angular velocity of the drive wheel (RADS/s)
	float driveWheelAngularAccelerationRADS;	// angular acceleration of the drive wheel (RADS/s)

	Vector3f accelerationLC;	// acceleration of the vehicle in local coordinate space
	Vector3f velocityLC;	// velocity of the vehicle in local coordinate space
	Vector3f positionLC;	// position of the vehicle in local coordinate space

	tInputState inputState;
};



#endif
