#include "camerafreelook.h"
//#include "gameactions.h"
#include "log.h"
#include "timer.h"
#include "input.h"

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

		case GAME_RIGHT:
			return CAM_ROTATE_X_POS;
		case GAME_LEFT:
			return CAM_ROTATE_X_NEG;

		case GAME_UP:
			return CAM_ROTATE_Y_POS;
		case GAME_DOWN:
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

void CCameraFreeLook::Update( int iInput )
{
	int iAction = this->MapKey(iInput);
	CLog::GetLog().Write(LOG_GAMECONSOLE, "Camera Action Received: %d", iAction);
/*
	switch( iAction )
	{
    case CAM_UNKNOWN:
		CLog::GetLog().Write(LOG_GAMECONSOLE, "Unknown Camera Action: %d", iAction);
		return;

	case CAM_STRAFE_LEFT:

    case CAM_STRAFE_RIGHT:

    case CAM_MOVE_FORWARD:
		
    case CAM_MOVE_BACKWARD:

    case CAM_MOVE_UP:

    case CAM_MOVE_DOWN:

    case CAM_RESET:

	// extended actions
	case CAM_ROTATE_X:  // yaw

	case CAM_ROTATE_Y:  // pitch

	case CAM_ROTATE_Z:  // roll
		break;

	default:
		CLog::GetLog().Write(LOG_GAMECONSOLE, "Unknown Camera Action: %d", iAction);
		return;
	}

	this->UpdateVelocity(CTimer::GetTimer().GetCurrTime());
*/
    /*
	static float sfInputSpeed = 0.50f;
	static float sfInputSpeedRot = 0.02f;


	D3DXMATRIX mTrans;
	D3DXMATRIX mRot;

	float fXTran, fYTran, fZTran;
	fXTran = fYTran = fZTran = 0.0f;

	float fXRot, fYRot, fZRot;
	fXRot = fYRot = fZRot = 0.0f;

	//D3DXMatrixTranslation


	switch(iInput)
	{
	// yaw
	// adjust rotation about Y Axis
	case GAME_LEFT://GAME_DEBUG_CAMERA_LEFT:
		fYRot += sfInputSpeedRot;
		break;

	case GAME_RIGHT://GAME_DEBUG_CAMERA_RIGHT:
		fYRot -= sfInputSpeedRot;
		break;

	// pitch
	// adjust rotation about  X axis
	case GAME_UP://GAME_DEBUG_CAMERA_UP:
		fXRot += sfInputSpeedRot;
		break;

	case GAME_DOWN://GAME_DEBUG_CAMERA_DOWN:
		fXRot -= sfInputSpeedRot;
		break;

	// strafing along dir vector othongonal too look vector and upVector
	case 'a'://GAME_DEBUG_MOVE_LEFT:
	case 'A':
		fXTran += sfInputSpeed;
//		m_vEyePt.x    -= sfInputSpeed; //$$$DEBUG
//		m_vLookAtPt.x -= sfInputSpeed; //$$$DEBUG
		break;

	case 'd'://GAME_DEBUG_MOVE_RIGHT:
	case 'D':
		fXTran -= sfInputSpeed;
//		m_vEyePt.x    += sfInputSpeed; //$$$DEBUG
//		m_vLookAtPt.x += sfInputSpeed; //$$$DEBUG
		break;

	// strafing along look vector direction
	//translate point along look vector
	case 'w'://GAME_DEBUG_MOVE_FORWARD:    // positive 
	case 'W':
		fZTran -= sfInputSpeed;
//		m_vEyePt.z    += sfInputSpeed; //$$$DEBUG
//		m_vLookAtPt.z += sfInputSpeed; //$$$DEBUG
		break;

	case 's'://GAME_DEBUG_MOVE_BACKWARD:  // negative
	case 'S':
		fZTran += sfInputSpeed;
//		m_vEyePt.z    -= sfInputSpeed; //$$$DEBUG
//		m_vLookAtPt.z -= sfInputSpeed; //$$$DEBUG
		break;

	case ' '://GAME_DEBUG_MOVE_UP:  // negative
		fYTran -= sfInputSpeed;
//		m_vEyePt.y    += sfInputSpeed; //$$$DEBUG
//		m_vLookAtPt.y += sfInputSpeed; //$$$DEBUG
		break;

	case 'c'://GAME_DEBUG_MOVE_DOWN:  // negative
	case 'C':
		fYTran += sfInputSpeed;
//		m_vEyePt.y    -= sfInputSpeed; //$$$DEBUG
//		m_vLookAtPt.y -= sfInputSpeed; //$$$DEBUG
		break;

	case '+'://GAME_DEBUG_INPUT_SPEED_INC:  // negative
	case '=':
	case GAME_NUMPADENTER:
		sfInputSpeed += 0.01f;
        //sfInputSpeed = LERP(sfInputSpeed, (sfInputSpeed+0.01f)/2.0, sfInputSpeed+0.01f);
		sfInputSpeedRot += 0.003f;
		if (sfInputSpeed < 0.0f)
			sfInputSpeed = 0.001f;
		if (sfInputSpeedRot < 0.0f)
			sfInputSpeedRot = 0.001f;
		break;

	case '-'://GAME_DEBUG_INPUT_SPEED_DEC:  // negative
	case '_':
	case GAME_SUBTRACT:
		sfInputSpeed -= 0.01f;
		sfInputSpeedRot -= 0.003f;
		if (sfInputSpeed < 0.0f)
			sfInputSpeed = 0.001f;
		if (sfInputSpeedRot < 0.0f)
			sfInputSpeedRot = 0.001f;

		break;

	default:
		#ifdef _DEBUG
		//CLog::GetLog().Write(LOG_MISC, "Camera:  Unknown Action");
		#endif
		break;
	}


	// Chris fucking with Jay's Shit 
	// Probably going to get pistol whipped for it 
	m_trans.x += fXTran;
	m_trans.y += fYTran;
	m_trans.z += fZTran;

	// Chris fucking with Jay's Shit 
	// Probably going to get pistol whipped for it 
	m_rot.x += fXRot;
	m_rot.y += fYRot;
	m_rot.z += fZRot;

	// Chris fucking with Jay's Shit 
	// Probably going to get pistol whipped for it 

	// build transformation matrices
	D3DXMatrixTranslation( &mTrans, m_trans.x, m_trans.y, m_trans.z);
	//D3DXMatrixRotationYawPitchRoll( &mRot, fXRot, fYRot, fZRot);

	D3DXMATRIX mRotX;
	D3DXMATRIX mRotY;
	D3DXMATRIX mRotZ;

	// Chris fucking with Jay's Shit 
	// Probably going to get pistol whipped for it 
	D3DXMatrixRotationX( &mRotX, -m_rot.x);
	D3DXMatrixRotationY( &mRotY, -m_rot.y);
	D3DXMatrixRotationZ( &mRotZ, -m_rot.z);
	// multiply current camera view matrix
	//m_matView *= mRot;

	// Chris fucking with Jay's Shit 
	// Probably going to get pistol whipped for it 
	D3DXMatrixIdentity( &m_matView);

	m_matView *= mRotY;
	m_matView *= mRotX;
	m_matView *= mRotZ;
	m_matView *= mTrans;


	CLog::GetLog().Write(LOG_GAMECONSOLE, "Input speeds %f rot %f", sfInputSpeed, sfInputSpeedRot);
	CLog::GetLog().Write(LOG_GAMECONSOLE, "action %d", iInput );

	//this->SetViewParams(m_vEyePt, m_vLookAtPt, m_vUpVec);   // rebuild view parameters
 */   
}


#define INPUTSPEED 0.1f;
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
		m_vRotVelocity.x += INPUTSPEED;     //rot around X
	}
	if ( IsKeyDown(m_aKeys[CAM_ROTATE_X_NEG]) ) {
		//m_bInvertPitch = TRUE;
		m_vRotVelocity.x -= INPUTSPEED;     //rot around X
	}

	if ( IsKeyDown(m_aKeys[CAM_ROTATE_Y_POS]) ) {
		//m_bInvertYaw = FALSE;
		m_vRotVelocity.y += INPUTSPEED;  	//rot around Y
	}
	if ( IsKeyDown(m_aKeys[CAM_ROTATE_Y_NEG]) ) {
		//m_bInvertYaw = TRUE;
		m_vRotVelocity.y -= INPUTSPEED;  	//rot around Y
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
    CLog::GetLog().Write(LOG_GAMECONSOLE, " Camera Position %f %f %f", m_vEye.x, m_vEye.y, m_vEye.z);
    #endif
}
