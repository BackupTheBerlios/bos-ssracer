#include "physicstask.h"
#include "physics.h"

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
  //CPhysics::GetPhysicsPtr()->Update(-1, false);
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

	//delete CPhysics::GetPhysicsPtr();
}

void CPhysicsTask::DoMessageHandle( ITaskMessage *cMsg ) {

}
