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
    //Ramits add to update AI vehicle(s) 
    //TODO Convert to vector and parse through each one....
	// Get any AI vehicles that need to be updated
    /*CVehicle* opponentVehicle = CGameStateManager::GetGameStateManagerPtr()->GetOpponentVehicle();
 	if(opponentVehicle) {
		opponentVehicle->UpdateVehiclePhysics();
	}*/

    vector<COpponentVehicle *>::iterator it;
    for (it=CGameStateManager::GetGameStateManagerPtr()->GetOpponents()->begin();
         it<CGameStateManager::GetGameStateManagerPtr()->GetOpponents()->end();  it++) {
           (*it)->UpdateVehiclePhysics();
    }
	// Get all other rigid bodies in simulation, and update their physics.

}
