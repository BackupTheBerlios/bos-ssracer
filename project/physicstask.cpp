#include "physicstask.h"
#include "physics.h"
#include "ccollisionmessage.h"
#include "gamestatemanager.h"

CPhysicsTask::CPhysicsTask()
{ 
  m_nTaskType = PHYSICS_TASK;
}

bool CPhysicsTask::Start()
{
  new CPhysics(0);
  CLog::GetLog().Write(LOG_MISC, "Starting Physics Task...");

  return true;
}

void CPhysicsTask::Update()
{
  HandleMessages();
  CPhysics::GetPhysicsPtr()->Update();
}

void CPhysicsTask::OnSuspend()
{
  //do something when suspended

}

void CPhysicsTask::OnResume()
{
  //do something when not suspended
}

void CPhysicsTask::Stop()
{
	// release any memory that was dynamically allocated
	// release devices

	delete CPhysics::GetPhysicsPtr();
}

void CPhysicsTask::DoMessageHandle( ITaskMessage *cMsg ) {

	if (!cMsg) return;

	CCollisionMessage* ColMsg;

	if (cMsg->GetType() == COLLISION_MESSAGE) {
		ColMsg = (CCollisionMessage*)cMsg;

		((CVehicle*)ColMsg->GetEntity())->DeliverCollisionMessage(ColMsg);
	}
}
