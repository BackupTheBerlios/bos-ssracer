#include "camerachase.h"
#include "timer.h"
#include "log.h"

#include "WmlMatrix3.h"

void CCameraChase::SetVehicle( CVehicle * pkVehicle )
{
    if(!pkVehicle)  {
        CLog::GetLog().Write(LOG_GAMECONSOLE, IDS_RENDER_ERROR, "cannot chase a NULL pointer!" );	
        return;
    }

    m_pkVehicle = pkVehicle;

    // get heading of vehicle
    Vector3f vHeading = pkVehicle->GetVehicleHeadingWC();
    vHeading.Normalize();

	// look at vector is a little past the vehicles origin
	Vector3f vOrigin = Vector3f(*pkVehicle->GetTranslate());
//    CLog::GetLog().Write(LOG_GAMECONSOLE, "worldpos of vehicle %f %f %f", vOrigin.X(), vOrigin.Y() , vOrigin.Z() );	
    Vector3f vTemp = vOrigin + vHeading*1.2f; //need to know the length of the car to set the offset properly
    vTemp.Y() += 0.7f;  //raise the look at point a little

	m_vDefaultLookAt = D3DXVECTOR3( vTemp.X(), vTemp.Y() , vTemp.Z()) ;
	m_vLookAt = m_vDefaultLookAt;
	CLog::GetLog().Write(LOG_GAMECONSOLE, "look %f %f %f", m_vDefaultLookAt.x, m_vDefaultLookAt.y, m_vDefaultLookAt.z );	

    // start at car's origin
	//m_vDefaultEye = m_vDefaultLookAt;
    m_vDefaultEye = D3DXVECTOR3(vOrigin.X(), vOrigin.Y(), vOrigin.Z());

    // get heading of car
    //vTemp = vHeading;
	//vTemp.Normalize();

    // want to set the eye behind the car so negate heading
    //D3DXVECTOR3 vDir = D3DXVECTOR3( -vTemp.X() , -vTemp.Y(), -vTemp.Z());
    D3DXVECTOR3 vDir = D3DXVECTOR3( -vHeading.X() , -vHeading.Y(), -vHeading.Z());

    CLog::GetLog().Write(LOG_GAMECONSOLE, "negative dir of heading %f %f %f", vDir.x, vDir.y, vDir.z );	

	// translate eye in -dir
	m_vDefaultEye += vDir*7.5f;

    // elevate the eye point
    m_vDefaultEye.y += 1.2f;  //should really use the height of the vehicle to calculate this
	m_vEye = m_vDefaultEye;

   	CLog::GetLog().Write(LOG_GAMECONSOLE, "eye %f %f %f", m_vDefaultEye.x, m_vDefaultEye.y, m_vDefaultEye.z );	

    SetViewParams( &m_vEye, &m_vLookAt);
    
    // set default proj params
    SetProjParams( CAMERA_CHASE_DEFAULT_FOV, 1.0f ,1.0f ,800.0f );

    FrameMove( CTimer::GetTimer().GetTimeElapsed() );
}

CCameraChase::CCameraChase()
{
    m_pkVehicle = NULL;
    m_bMovementDrag = true;  // want to lag movement btw frames
    m_fTotalDragTimeToZero = 0.2f;
}

// create an object for this camera to chase
CCameraChase::CCameraChase( CVehicle * pkVehicle ) : CD3DCamera()
{	
	m_pkVehicle = pkVehicle;
}


// just update the position;
void CCameraChase::Update()
{
    FrameMove( CTimer::GetTimer().GetTimeElapsed() );
}


// update the vehicles position 
// ignores user input
void CCameraChase::Update(int iInput, bool bState)
{
    if (!m_pkVehicle)
        return; //cant update if there is no vehicle to track!
	FrameMove(CTimer::GetTimer().GetTimeElapsed());
}


//-----------------------------------------------------------------------------
// Name: FrameMove
// Desc: Update the view matrix based on user input & elapsed time
//-----------------------------------------------------------------------------
VOID CCameraChase::FrameMove( FLOAT fElapsedTime )
{

    #ifdef _DEBUG
    if (!m_pkVehicle)  {
        CLog::GetLog().Write(LOG_DEBUGOVERLAY, 10, "cam ERROR: null vehicle!" );	
        return;
    }
    else {
        CLog::GetLog().Write(LOG_DEBUGOVERLAY, 10, "cam status OK" );
    }
    #endif

    UpdateVelocity( fElapsedTime );

    // get vehicle velocity and heading
    Vector3f vVel = m_pkVehicle->GetVehicleVelocityWC();
    Vector3f vHeading = m_pkVehicle->GetVehicleHeadingWC();

    Vector3f vTemp;

    D3DXVECTOR3 vPosDelta;
    vPosDelta = m_vVelocity * fElapsedTime;
    
    ////////////  CANT USE UNTIL ROTATION AND VELOCITY FIXED
    //vTemp = vHeading * fElapsedTime * 0.2f;
    //vPosDelta = D3DXVECTOR3(vTemp.X(), vTemp.Y(), vTemp.Z());
    

    // Make a rotation matrix based on the camera's yaw & pitch
    D3DXMATRIX mCameraRot;
    //D3DXMatrixRotationYawPitchRoll( &mCameraRot, m_fCameraYawAngle, m_fCameraPitchAngle, 0 );
    D3DXMatrixRotationYawPitchRoll( &mCameraRot, -m_fCameraYawAngle, 0, 0 );
    //D3DXMatrixRotationYawPitchRoll( &mCameraRot, -RADIANS(m_pkVehicle->GetRotate()->Y()), 0, 0 );  //SOMETHING WRONG WITH ITS ROTATION

    //CLog::GetLog().Write(LOG_DEBUGOVERLAY, 51, "cam rotate %f",  m_pkVehicle->GetRotate()->Y() );
    
    // Transform vectors based on camera's rotation matrix
    D3DXVECTOR3 vWorldUp, vWorldAhead;
    D3DXVECTOR3 vLocalUp  = D3DXVECTOR3(0,1,0);


    #ifdef _DEBUG
    CLog::GetLog().Write(LOG_DEBUGOVERLAY, 5, "car headingWC: %f %f %f", vHeading.X(), vHeading.Y(), vHeading.Z());
    CLog::GetLog().Write(LOG_DEBUGOVERLAY, 6, "car velWC: %f %f %f", vVel.X(), vVel.Y(), vVel.Z());
    //CLog::GetLog().Write(LOG_DEBUGOVERLAY, 5, "pos Delta: %f %f %f", vPosDelta.x, vPosDelta.y, vPosDelta.z);    
    #endif
    
    // get the camera's local ahead vector based on the vehicles heading and velocity
    if (vVel.Length() < 20.0f)  {// if velocity is small use heading
        vTemp = m_pkVehicle->GetVehicleHeadingWC();
        #ifdef _DEBUG
        CLog::GetLog().Write(LOG_DEBUGOVERLAY, 7, "using car heading");    
        #endif
    }
    else  {  // interpolate between velocity and heading
        //$$$TEMP not sure if i'm using the velocity correctly yet???
        /*
        // get angle between velocity and heading and make a rotation matrix
        float fAngle = m_pkVehicle->GetVehicleHeadingWC().Dot(m_pkVehicle->GetVehiclVelocityWC()) * fElapsedTime;
        Matrix3f matRot = Matrix3f( Vector3f(0,1,0),  fAngle);
  
        // rotate heading around Y to get this direction
        vTemp = matRot*m_pkVehicle->GetVehicleHeadingWC();
        
        #ifdef _DEBUG
        CLog::GetLog().Write(LOG_DEBUGOVERLAY, 7, "using angle %.4f", fAngle );    
        #endif
        */
        //$$$TEMP just use the heading for now
        vTemp = m_pkVehicle->GetVehicleHeadingWC();
        #ifdef _DEBUG
        CLog::GetLog().Write(LOG_DEBUGOVERLAY, 7, "using heading until I get velocity in WC..." );    
        #endif
    }

    vTemp.Y() = 0;
    vTemp.Normalize();
    D3DXVECTOR3 vLocalAhead = D3DXVECTOR3(vTemp.X(), vTemp.Y(), vTemp.Z());
    D3DXVec3TransformCoord( &vWorldUp, &vLocalUp, &mCameraRot );
    D3DXVec3TransformCoord( &vWorldAhead, &vLocalAhead, &mCameraRot );

    // Transform the position delta by the camera's rotation 
    D3DXVECTOR3 vPosDeltaWorld;
    D3DXVec3TransformCoord( &vPosDeltaWorld, &vPosDelta, &mCameraRot );

    if( !m_bEnableYAxisMovement )
        vPosDeltaWorld.y = 0.0f;

    float fEyeDelta = 1.0f, fVelDelta = 0.0f;

    // pull the camera back if we're going fast enough
    if (m_pkVehicle->GetVehicleVelocityWC().Length() > 20.0f)  {
        // get change in velocity so we can scale things accordingly
        fVelDelta = (m_pkVehicle->GetVehicleHeadingWC().Length() - 20.0f)*0.008f;

        if (m_pkVehicle->GetVehicleVelocityWC().Length() > 30.0f)  {
            // start widening the fov
            SetProjParams( CAMERA_CHASE_DEFAULT_FOV+fVelDelta*0.09f, 1.0f ,1.0f ,800.0f );

        }
        fEyeDelta = 1.0f + fVelDelta;

        //$$$TODO turn motion blur on
    }
    else { 
        fEyeDelta = 1.0f;
    }
    
    // place eye position based on vehicle's origin
    vTemp = Vector3f(*m_pkVehicle->GetTranslate());
    m_vEye = D3DXVECTOR3(vTemp.X(), 0, vTemp.Z());
    m_vEye -= vLocalAhead*5.5f*fEyeDelta;

    // Move the eye position 
    //m_vEye += vPosDeltaWorld;
    //if( m_bClipToBoundary )
    //    ConstrainToBoundary( &m_vEye );


    // Update the lookAt position based on the eye position 
    vWorldAhead.y = 0.0f;
    //m_vLookAt = m_vEye + vWorldAhead*10.2f;
    m_vLookAt = m_vEye + vLocalAhead*7.5f; /////

    // offset the points from the ground
    m_vLookAt.y = 1.0f;
    m_vEye.y = 2.1f; 

    // Update the view matrix
    D3DXMatrixLookAtLH( &m_mView, &m_vEye, &m_vLookAt, &vWorldUp );
    D3DXMatrixInverse( &m_mCameraWorld, NULL, &m_mView );

    // update frustum information
    UpdateCullInfo();

/*
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
    */
}

