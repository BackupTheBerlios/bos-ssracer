#include "physics.h"
#include "timer.h"
#include "input.h"
#include "gamestatemanager.h"

CPhysics * CPhysics::m_physics = NULL;

CPhysics::CPhysics(int temp)
{ 
	m_physics = this; 
}

void CPhysics::Update()
{

	// Get the player vehicle from the game
	CVehicle* playerVehicle = CGameStateManager::GetGameStateManagerPtr()->GetPlayerVehicle();
 	if(playerVehicle) {
		playerVehicle->UpdateVehiclePhysics();
	}

	// Get any AI vehicles that need to be updated
	// Get all other rigid bodies in simulation, and update their physics.

}
