#include "rigidbody.h"
#include "log.h"
#include "vehicle.h"

CRigidBody::CRigidBody()
{
	m_vPosition = Vector3f(0.0f, 0.0f, 0.0f);
	m_vOrientation = Vector3f(0.0f, 0.0f, 0.0f);
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
void CRigidBody::DeliverCollisionMessage(CCollisionMessage* ColMsg)
{
	if (!ColMsg) return;

	CVehicle* Car = (CVehicle*)ColMsg->GetEntity();

	m_vPosition = m_translate + (*ColMsg->GetReverse())*RIGIDBODY_SPACING_FACTOR;

	m_vDirectionWhenDisturbed = m_translate - m_vPosition;

	Vector3f velocityWC = Car->GetVehicleVelocityWC();
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

	if (Car->GetVehicleVelocityLC().X() < 0.0f)
		Car->SetVehicleVelocityLC(0.0f);
	else Car->SetVehicleVelocityLC(0.0f);
	Car->SetVehiclePositionLC(Vector3f(m_vPosition.X(), m_vPosition.Z(), m_vPosition.Y()));

	m_translate = m_vPosition;
	m_box.Center() = m_vPosition;

	disturbed = true;
}
#undef RIGIDBODY_REFLECTION_FACTOR
#undef RIGIDBODY_SPACING_FACTOR

#define RIGIDBODY_REFLECTION_ENTROPY_FACTOR 0.99f
#define RIGIDBODY_REFLECTION_DEATH_FACTOR 0.01f
void CRigidBody::UpdateCollisionReaction()
{
	CVehicle* Car = (CVehicle*)this;

	m_vReflection *= RIGIDBODY_REFLECTION_ENTROPY_FACTOR;
	m_vPosition = m_translate + m_vReflection;
	m_vDirectionWhenDisturbed = m_vPosition - m_translate;
	m_translate = m_vPosition;
	m_box.Center() = m_vPosition;

	Car->SetVehiclePositionLC(Vector3f(m_vPosition.X(), m_vPosition.Z(), m_vPosition.Y()));

	if (m_vReflection.Length() < RIGIDBODY_REFLECTION_DEATH_FACTOR)
		disturbed = false;

	
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
	

}
#undef RIGIDBODY_REFLECTION_ENTROPY_FACTOR
#undef RIGIDBODY_REFLECTION_DEATH_FACTOR