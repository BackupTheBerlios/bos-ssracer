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


/*	if(m_playerCar) {
		switch(iInput)
		{
			
		case GAME_NUMPAD8:
		case GAME_BUTTON0:
			if(test) {
				m_playerCar->setGas(true);
			}
			else {
				m_playerCar->setGas(false);
			}
			break;

		case GAME_NUMPAD5:
		case GAME_BUTTON2:
			if(test) {
				m_playerCar->setBrake(true);
			}
			else {
				m_playerCar->setBrake(false);
			}
			break;

		case GAME_NUMPAD4:
		case GAME_LEFT:
			if(test) {
				m_playerCar->setLTurn(true);
			}
			else {
				m_playerCar->setLTurn(false);
			}
			break;

		case GAME_NUMPAD6:
		case GAME_RIGHT:
			if(test) {
				m_playerCar->setRTurn(true);
			}
			else {
				m_playerCar->setRTurn(false);
			}
			break;
		}

		m_playerCar->autoGearShift();
		m_playerCar->interpolateSteering(CTimer::GetTimer().GetTimeElapsed());
		m_playerCar->updatePhysics(CTimer::GetTimer().GetTimeElapsed());
	}
	*/
}

/*
void CPhysics::setPlayerVehicle(CPlayerVehicle* playerCar)
{
    if (playerCar)
    	m_playerCar = playerCar;

}
*/