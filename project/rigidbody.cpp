#include "rigidbody.h"
#include "log.h"
#include "vehicle.h"

CRigidBody::CRigidBody()
{
	m_vPosition = Vector3f(0.0f, 0.0f, 0.0f);
	m_vRotation = Vector3f(0.0f, 0.0f, 0.0f);
	m_vOrientation = Vector3f(0.0f, 0.0f, 0.0f); // not being used
	m_vReflection = Vector3f(0.0f, 0.0f, 0.0f);
	m_vDirectionWhenDisturbed = Vector3f(0.0f, 0.0f, 0.0f);
	disturbed = false;
}

CRigidBody::~CRigidBody()
{
	// No pointers, no problem
}

#define RIGIDBODY_REFLECTION_FACTOR 0.009f
#define RIGIDBODY_SPACING_FACTOR 3.0f
#define RIGIDBODY_SPIN_FACTOR 0.02f;
void CRigidBody::DeliverCollisionMessage(CCollisionMessage* ColMsg)
{
	if (!ColMsg) return;

	if (ColMsg->GetCollisionType() == SPHERE_TO_SPHERE) {
		HandleSphereToSphereCollision(ColMsg);
		return;
	}

	/****** Deploy to HandlePushCollision() if this is the case ******/
	// Push collision not working. Commenting this out for now.
	/*	if (ColMsg->GetCollisionType() == PUSHED) {
		HandlePushCollision(ColMsg);
		return;
	}
*/ 

	CVehicle* Car = (CVehicle*)ColMsg->GetEntity();

	/************** set reflection motion ************/

	m_vPosition = m_translate + (*ColMsg->GetReverse())*RIGIDBODY_SPACING_FACTOR;

	Vector3f velocityWC;
	if (disturbed) {
		velocityWC = m_vDirectionWhenDisturbed*80.0f;
	}
	else {
		velocityWC = Car->GetVehicleVelocityWC();
		// if reversing, velocityWC will point in opposite direction as actual velocity
		if (Car->GetVehicleVelocityLC().X() < 0.0f)
			velocityWC *= -1.0f;
	}

	m_vReflection = velocityWC - 2.0f*(velocityWC.Dot(*ColMsg->GetNormal()))*(*ColMsg->GetNormal());
	m_vReflection *= RIGIDBODY_REFLECTION_FACTOR;
	m_vDirectionWhenDisturbed = m_vReflection;

	Car->SetVehicleVelocityLC(0.0f);
	Car->SetVehiclePositionLC(Vector3f(m_vPosition.X(), m_vPosition.Z(), m_vPosition.Y()));

	/*************** set angular velocity ******************/

	// Compute angle between vehicle heading and plane
	Vector3f PlaneEdge = ColMsg->GetPlane()->Edge0();
	Vector3f CarHeading = Car->GetVehicleHeadingWC();
	float angle = acos(CarHeading.Dot(PlaneEdge)/(PlaneEdge.Length()*CarHeading.Length()));

	// spin CW or CCW?
	float spin; // magnitude of spin about the y-axis
	if (angle > Math<float>::PI/2.0f) { // CCW
		spin = Math<float>::PI - angle;
	}
	else { // CW
		spin = -angle;
	}
	spin *= RIGIDBODY_SPIN_FACTOR;
	m_vRotation = Vector3f(0.0f, spin, 0.0f);

	/*************** set vectors that are actually used in renderer ************/
	/*********************** to the values computed above **********************/

	m_translate = m_vPosition;
	m_box.Center() = m_vPosition;
	m_sphere.Center() = m_vPosition;
	Car->GetRotationLC().Z() += spin;

	disturbed = true;

	/*
	CLog::GetLog().Write(LOG_MISC, "\n\n\nreflection = (%f, %f, %f)",
		m_vReflection.X(), m_vReflection.Y(), m_vReflection.Z());
	CLog::GetLog().Write(LOG_MISC, "direction = (%f, %f, %f)\n\n",
		m_vDirectionWhenDisturbed.X(), m_vDirectionWhenDisturbed.Y(), m_vDirectionWhenDisturbed.Z());
*/
}

void CRigidBody::HandlePushCollision(CCollisionMessage* ColMsg)
{
	CVehicle* Car = (CVehicle*)ColMsg->GetEntity();


	CLog::GetLog().Write(LOG_MISC, "In HandlePushCollision()");

	/***************** First, findout how hard Car was hit **************/
	float force = ColMsg->GetPushForce()->Length();

	//CLog::GetLog().Write(LOG_MISC, "force = %f", force);

	Vector3f Direction = (*ColMsg->GetNormal())*force;

	CLog::GetLog().Write(LOG_MISC, "\n\n\nforce = %f", force);
	CLog::GetLog().Write(LOG_MISC, "Direction = (%f, %f, %f)",
		Direction.X(), Direction.Y(), Direction.Z());

	/***************** Next, findout where along body Car was hit *********/
	float where; 
	Rectangle3f Rect = *ColMsg->GetPlane();
	Vector3f ColPoint = *ColMsg->GetColPoint();
	Plane3f P1 = Plane3f(Rect.Edge0(), Rect.Origin());
	where = P1.DistanceTo(ColPoint)/Rect.Edge0().Length();
	// So where = [1,0]. 0 - at origin, 1 - opposite origin

}

void CRigidBody::HandleSphereToSphereCollision(CCollisionMessage* ColMsg)
{
	CVehicle* Car = (CVehicle*)ColMsg->GetEntity();
	Vector3f CenterToCenter = *ColMsg->GetCenterToCenter();

	// set translate
	m_vReflection = CenterToCenter*0.05f;
	m_vPosition = m_translate;
	m_vDirectionWhenDisturbed = m_vReflection;

	// set rotation
	if (CenterToCenter.Length() == 0.0f) CenterToCenter = Vector3f(1.0f, 0.0f, 0.0f);
	float theta1 = (CenterToCenter.Dot(Car->GetVehicleHeadingWC()))/(CenterToCenter.Length()*Car->GetVehicleHeadingWC().Length());
	Vector3f CP = CenterToCenter.Cross(Vector3f(0.0f, 1.0f, 0.0f));
	float theta2 = (CP.Dot(Car->GetVehicleHeadingWC()))/(CP.Length()*Car->GetVehicleHeadingWC().Length());

//	CLog::GetLog().Write(LOG_DEBUGOVERLAY, 120, "theta1 = %f", theta1);
//	CLog::GetLog().Write(LOG_DEBUGOVERLAY, 121, "theta2 = %f", theta2);

	float spin;
	if (0.0f < theta1 && theta1 < 1.0f) {
		// LOWER-LEFT QUADRANT
		if (0.0f < theta2 && theta2 < 1.0f) {
			spin = theta2;
		}
		// LOWER-RIGHT QUADRANT
		else {
			spin = theta2;
		}
	}
	else {
		// UPPER-LEFT QUADRANT
		if (0.0f < theta2 && theta2 < 1.0f) {
			spin = -theta2;
		}
		// UPPER-RIGHT QUADRANT
		else {
			spin = -theta2;
		}
	}

	spin *= RIGIDBODY_SPIN_FACTOR;
	m_vRotation = Vector3f(0.0f, spin, 0.0f);

	// actually set it!
	Car->SetVehicleVelocityLC(0.0f);
	Car->SetVehiclePositionLC(Vector3f(m_vPosition.X(), m_vPosition.Z(), m_vPosition.Y()));

	disturbed = true;
}

#undef RIGIDBODY_REFLECTION_FACTOR
#undef RIGIDBODY_SPACING_FACTOR
#undef RIGIDBODY_SPIN_FACTOR

#define RIGIDBODY_REFLECTION_ENTROPY_FACTOR 0.99f
#define RIGIDBODY_REFLECTION_DEATH_FACTOR 0.01f
#define RIGIDBODY_ROTATION_ENTROPY_FACTOR 0.99f
void CRigidBody::UpdateCollisionReaction()
{
	CVehicle* Car = (CVehicle*)this;

	Vector3f OldPosition = m_vPosition;

	// update reflection motion
	m_vReflection *= RIGIDBODY_REFLECTION_ENTROPY_FACTOR;
	m_vPosition = m_translate + m_vReflection;
	m_vDirectionWhenDisturbed = m_vPosition - OldPosition;
	m_translate = m_vPosition;
	m_box.Center() = m_vPosition;
	m_sphere.Center() = m_vPosition;

	Car->SetVehiclePositionLC(Vector3f(m_vPosition.X(), m_vPosition.Z(), m_vPosition.Y()));

	// update angular velocity
	m_vRotation *= RIGIDBODY_ROTATION_ENTROPY_FACTOR;
	Car->GetRotationLC().Z() += m_vRotation.Y();

	// see if reflection has dissipated enough to stop
	if (m_vReflection.Length() < RIGIDBODY_REFLECTION_DEATH_FACTOR) {
		disturbed = false;
	}

}
#undef RIGIDBODY_REFLECTION_ENTROPY_FACTOR
#undef RIGIDBODY_REFLECTION_DEATH_FACTOR
#undef RIGIDBODY_ROTATION_ENTROPY_FACTOR