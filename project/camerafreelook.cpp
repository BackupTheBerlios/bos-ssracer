#include "camerafreelook.h"
//#include "gameactions.h"
#include "log.h"
#include "timer.h"
#include "input.h"

CCameraFreeLook::CCameraFreeLook() : CD3DCamera()
{
}

//-----------------------------------------------------------------------------
// Name: MapKey
// Desc: Maps a key to an enum
//-----------------------------------------------------------------------------
D3DUtil_CameraKeys CCameraFreeLook::MapKey( UINT nKey )
{
    switch( nKey )
    {
        case 'A':  
		case 'a':
			return CAM_STRAFE_LEFT;

		case 'D':
        case 'd': 
			return CAM_STRAFE_RIGHT;

        case 'W':    
		case 'w':
			return CAM_MOVE_FORWARD;

        case 'S':
		case 's':
			return CAM_MOVE_BACKWARD;

        case 'c':
		case 'C':
			return CAM_MOVE_DOWN;

        case ' ': //spacebar
			return CAM_MOVE_UP;

		case GAME_LEFT:
			return CAM_ROTATE_X_POS;
		case GAME_RIGHT:
			return CAM_ROTATE_X_NEG;

		case GAME_DOWN:
			return CAM_ROTATE_Y_POS;
		case GAME_UP:
			return CAM_ROTATE_Y_NEG;

		//case GAME_DELETE:

		//case GAME_END:
		//	return CAM_ROTATE_Z;

        case GAME_HOME:   
			return CAM_RESET;
    }

    return CAM_UNKNOWN;
}


void CCameraFreeLook::Update( int iInput, bool bState )
{
	HandleInputMessages( new CInputTaskMessage(iInput, bState));
	FrameMove( CTimer::GetTimer().GetTimeElapsed() );
	return;

}

#define ROTSPEED 0.4f;
//-----------------------------------------------------------------------------
// Name: FrameMove
// Desc: Update the view matrix based on user input & elapsed time
//-----------------------------------------------------------------------------
VOID CCameraFreeLook::FrameMove( FLOAT fElapsedTime )
{
    if( IsKeyDown(m_aKeys[CAM_RESET]) )
        Reset();

	/*
    // Get the mouse movement (if any) if the mouse button are down
    if( m_bMouseLButtonDown || m_bMouseMButtonDown || m_bMouseRButtonDown ) 
        UpdateMouseDelta( fElapsedTime );
	*/

	//m_vRotVelocity = m_vMouseDelta * m_fRotationScaler;

	if ( IsKeyDown(m_aKeys[CAM_ROTATE_X_POS]) ) {
		//m_bInvertPitch = FALSE;
		m_vRotVelocity.x += ROTSPEED;     //rot around X
	}
	if ( IsKeyDown(m_aKeys[CAM_ROTATE_X_NEG]) ) {
		//m_bInvertPitch = TRUE;
		m_vRotVelocity.x -= ROTSPEED;     //rot around X
	}

	if ( IsKeyDown(m_aKeys[CAM_ROTATE_Y_POS]) ) {
		//m_bInvertYaw = FALSE;
		m_vRotVelocity.y += ROTSPEED;  	//rot around Y
	}
	if ( IsKeyDown(m_aKeys[CAM_ROTATE_Y_NEG]) ) {
		//m_bInvertYaw = TRUE;
		m_vRotVelocity.y -= ROTSPEED;  	//rot around Y
	}


	m_vRotVelocity *= m_fRotationScaler;

	
    
	// Get amount of velocity based on the keyboard input and drag (if any)
    UpdateVelocity( fElapsedTime );

    // Simple euler method to calculate position delta
    D3DXVECTOR3 vPosDelta = m_vVelocity * fElapsedTime;


    // If rotating the camera 
    //if( m_bMouseLButtonDown ||  m_bMouseMButtonDown || m_bMouseRButtonDown )
	
	if ( IsKeyDown(m_aKeys[CAM_ROTATE_X_POS]) || IsKeyDown(m_aKeys[CAM_ROTATE_X_NEG]) ||
		 IsKeyDown(m_aKeys[CAM_ROTATE_Y_POS]) || IsKeyDown(m_aKeys[CAM_ROTATE_Y_NEG]) )
    {
        // Update the pitch & yaw angle based on mouse movement
        float fYawDelta   = m_vRotVelocity.x;
        float fPitchDelta = m_vRotVelocity.y;

        // Invert pitch if requested
        if( m_bInvertPitch )
            fPitchDelta = -fPitchDelta;

		if( m_bInvertYaw )
            fYawDelta = -fYawDelta;

        m_fCameraPitchAngle += fPitchDelta;
        m_fCameraYawAngle   += fYawDelta;
		

        // Limit pitch to straight up or straight down
        m_fCameraPitchAngle = max( -D3DX_PI/2.0f,  m_fCameraPitchAngle );
        m_fCameraPitchAngle = min( +D3DX_PI/2.0f,  m_fCameraPitchAngle );
    }


    // Make a rotation matrix based on the camera's yaw & pitch
    D3DXMATRIX mCameraRot;
    D3DXMatrixRotationYawPitchRoll( &mCameraRot, m_fCameraYawAngle, m_fCameraPitchAngle, 0 );

    // Transform vectors based on camera's rotation matrix
    D3DXVECTOR3 vWorldUp, vWorldAhead;
    D3DXVECTOR3 vLocalUp    = D3DXVECTOR3(0,1,0);
    D3DXVECTOR3 vLocalAhead = D3DXVECTOR3(0,0,1);
    D3DXVec3TransformCoord( &vWorldUp, &vLocalUp, &mCameraRot );
    D3DXVec3TransformCoord( &vWorldAhead, &vLocalAhead, &mCameraRot );

    // Transform the position delta by the camera's rotation 
    D3DXVECTOR3 vPosDeltaWorld;
    D3DXVec3TransformCoord( &vPosDeltaWorld, &vPosDelta, &mCameraRot );
    if( !m_bEnableYAxisMovement )
        vPosDeltaWorld.y = 0.0f;

    // Move the eye position 
    m_vEye += vPosDeltaWorld;
    if( m_bClipToBoundary )
        ConstrainToBoundary( &m_vEye );

    // Update the lookAt position based on the eye position 
    m_vLookAt = m_vEye + vWorldAhead;

    // Update the view matrix
    D3DXMatrixLookAtLH( &m_mView, &m_vEye, &m_vLookAt, &vWorldUp );

    //D3DXMatrixInverse( &m_mCameraWorld, NULL, &m_mView );
    #ifdef _DEBUG
    CLog::GetLog().Write(LOG_DEBUGOVERLAY, 0, " Camera Position %f %f %f", m_vEye.x, m_vEye.y, m_vEye.z);
    #endif
}
