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
#define RIGIDBODY_SPACING_FACTOR 1.1f
#define RIGIDBODY_SPIN_FACTOR 0.05f;
void CRigidBody::DeliverCollisionMessage(CCollisionMessage* ColMsg)
{
	if (!ColMsg) return;

	CVehicle* Car = (CVehicle*)ColMsg->GetEntity();

	/************** set reflection motion ************/

	m_vPosition = m_translate + (*ColMsg->GetReverse())*RIGIDBODY_SPACING_FACTOR;

	CLog::GetLog().Write(LOG_MISC, "reverse = (%f, %f, %f)",
		ColMsg->GetReverse()->X(), ColMsg->GetReverse()->Y(), ColMsg->GetReverse()->Z());
	CLog::GetLog().Write(LOG_MISC, "translate = (%f, %f, %f)",
		m_translate.X(), m_translate.Y(), m_translate.Z());
	CLog::GetLog().Write(LOG_MISC, "position = (%f, %f, %f)",
		m_vPosition.X(), m_vPosition.Y(), m_vPosition.Z());

	m_vDirectionWhenDisturbed = m_translate - m_vPosition;

	Vector3f velocityWC = Car->GetVehicleVelocityWC();

	// if reversing, velocityWC will point in opposite direction as actual velocity
	if (Car->GetVehicleVelocityLC().X() < 0.0f)
		velocityWC *= -1.0f;

	m_vReflection = velocityWC - 2.0f*(velocityWC.Dot(*ColMsg->GetNormal()))*(*ColMsg->GetNormal());
	
	/*	if (!disturbed)
		m_vReflection = velocityWC - 2.0f*(velocityWC.Dot(*ColMsg->GetNormal()))*(*ColMsg->GetNormal());
	else {
		m_vReflection = m_vDirectionWhenDisturbed - 2.0f*(m_vDirectionWhenDisturbed.Dot(*ColMsg->GetNormal()))*(*ColMsg->GetNormal());
		CLog::GetLog().Write(LOG_DEBUGOVERLAY, 60, "DWD = (%f, %f, %f)",
			m_vDirectionWhenDisturbed.X(), m_vDirectionWhenDisturbed.Y(), m_vDirectionWhenDisturbed.Z());
		CLog::GetLog().Write(LOG_DEBUGOVERLAY, 61, "Reflection = (%f, %f, %f)",
			m_vReflection.X(), m_vReflection.Y(), m_vReflection.Z());
	}*/
	m_vReflection *= RIGIDBODY_REFLECTION_FACTOR;

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
	Car->GetRotationLC().Z() += spin;

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

	// update reflection motion
	m_vReflection *= RIGIDBODY_REFLECTION_ENTROPY_FACTOR;
	m_vPosition = m_translate + m_vReflection;
	m_vDirectionWhenDisturbed = m_vPosition - m_translate;
	m_translate = m_vPosition;
	m_box.Center() = m_vPosition;

	Car->SetVehiclePositionLC(Vector3f(m_vPosition.X(), m_vPosition.Z(), m_vPosition.Y()));

	// update angular velocity
	m_vRotation *= RIGIDBODY_ROTATION_ENTROPY_FACTOR;
	Car->GetRotationLC().Z() += m_vRotation.Y();

	// see if reflection has dissipated enough to stop
	if (m_vReflection.Length() < RIGIDBODY_REFLECTION_DEATH_FACTOR) {
		disturbed = false;
	}

	/*
	if (disturbed) {
		CLog::GetLog().Write(LOG_MISC, "\n\n\nreflection = (%f, %f, %f)",
			m_vReflection.X(), m_vReflection.Y(), m_vReflection.Z());
		CLog::GetLog().Write(LOG_MISC, "m_vPosition = (%f, %f, %f)",
			m_vPosition.X(), m_vPosition.Y(), m_vPosition.Z());
		CLog::GetLog().Write(LOG_MISC, "translate = (%f, %f, %f)",
			m_translate.X(), m_translate.Y(), m_translate.Z());
		CLog::GetLog().Write(LOG_MISC, "m_box = (%f, %f, %f)\n\n\n",
			m_box.Center().X(), m_box.Center().Y(), m_box.Center().Z());
	}
	else {
		CLog::GetLog().Write(LOG_MISC, "\n\n\ndisturbed = false\n\n\n");
	}
	*/

}
#undef RIGIDBODY_REFLECTION_ENTROPY_FACTOR
#undef RIGIDBODY_REFLECTION_DEATH_FACTOR
#undef RIGIDBODY_ROTATION_ENTROPY_FACTOR