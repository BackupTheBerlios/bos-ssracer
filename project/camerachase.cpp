#include "camerachase.h"
#include "timer.h"
#include "log.h"

void CCameraChase::SetVehicle( CVehicle * pkVehicle )
{
    if(!pkVehicle)  {
        CLog::GetLog().Write(LOG_GAMECONSOLE, IDS_RENDER_ERROR, "cannot chase a NULL pointer!" );	
        return;
    }

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

    m_pkVehicle = pkVehicle;
}

CCameraChase::CCameraChase()
{
    m_pkVehicle = NULL;
    m_bMovementDrag = true;  // want to lag movement btw frames
    m_fTotalDragTimeToZero = 0.5;
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
    ////m_vVelocity = D3DXVECTOR3(0,0,0);//UpdateVelocity( fElapsedTime );

    Vector3f vTemp;

    ////vTemp = Vector3f(m_pkObject->getTranslate());
    ////CLog::GetLog().Write(LOG_GAMECONSOLE, "worldpos %f %f %f", vTemp.X(), vTemp.Y() , vTemp.Z() );	

    D3DXVECTOR3 vPosDelta;
    vPosDelta = m_vVelocity * fElapsedTime;  //$$$TEMP once velocity in WC is updated try the following instead
    
    
    Vector3f vVel = m_pkVehicle->GetVehicleVelocityWC();
    //vVel.Normalize();
    //vPosDelta = D3DXVECTOR3(vVel.Z(), vVel.Y(), vVel.X()) * fElapsedTime;
    

    #ifdef _DEBUG
    CLog::GetLog().Write(LOG_DEBUGOVERLAY, 6, "car velWC: %f %f %f", vVel.X(), vVel.Y(), vVel.Z());
    CLog::GetLog().Write(LOG_DEBUGOVERLAY, 5, "pos Delta: %f %f %f", vPosDelta.x, vPosDelta.y, vPosDelta.z);
    #endif


    //vPosDelta = D3DXVECTOR3(vTemp.Z(), 0.0f, vTemp.X()) * fElapsedTime;//m_vVelocity * fElapsedTime;

    //vTemp = Vector3f(*m_pkVehicle->GetRotate());
    //m_fCameraYawAngle = -RADIANS(vTemp.X());//CTimer::GetTimer().GetTimeStep();;    
    //m_fCameraYawAngle = -vTemp.Y()*fElapsedTime;
    //m_fCameraYawAngle = m_vRotVelocity.x;
    //CLog::GetLog().Write(LOG_GAMECONSOLE, "yaw %f", m_fCameraYawAngle);	

    // Make a rotation matrix based on the camera's yaw & pitch
    D3DXMATRIX mCameraRot;
    D3DXMatrixRotationYawPitchRoll( &mCameraRot, m_fCameraYawAngle, m_fCameraPitchAngle, 0 );

    vTemp = *m_pkVehicle->GetRotate() ; ////
    vTemp = vTemp.Cross(Vector3f(0.0f, 0.0f, 1.0f));
    vTemp.Normalize();    
    
    // Transform vectors based on camera's rotation matrix
    D3DXVECTOR3 vWorldUp, vWorldAhead;
    D3DXVECTOR3 vLocalUp  = D3DXVECTOR3(0,1,0);
    // get the camera's local ahead vector based on the vehicles heading and velocity
    Vector3f vHeading = m_pkVehicle->GetVehicleVelocityWC();
    if (vHeading.Length() < 0.01f)  // if velocity is small use heading
        vHeading = m_pkVehicle->GetVehicleHeadingWC();

    vHeading.Normalize();
    D3DXVECTOR3 vLocalAhead = D3DXVECTOR3(vHeading.X(), vHeading.Y(), vHeading.Z());
    //D3DXVECTOR3 vLocalAhead = D3DXVECTOR3(0,0,1);
    D3DXVec3TransformCoord( &vWorldUp, &vLocalUp, &mCameraRot );
    D3DXVec3TransformCoord( &vWorldAhead, &vLocalAhead, &mCameraRot );

    // Transform the position delta by the camera's rotation 
    D3DXVECTOR3 vPosDeltaWorld;
    D3DXVec3TransformCoord( &vPosDeltaWorld, &vPosDelta, &mCameraRot );
    if( !m_bEnableYAxisMovement )
        vPosDeltaWorld.y = 0.0f;

    vTemp = Vector3f(*m_pkVehicle->GetTranslate());
//    CLog::GetLog().Write(LOG_GAMECONSOLE, "worldpos %f %f %f", vTemp.X(), vTemp.Y() , vTemp.Z() );	
    m_vEye = D3DXVECTOR3(vTemp.X(), 2.1f, vTemp.Z()) - vLocalAhead*7.5f;

    // Move the eye position 
    m_vEye += vPosDeltaWorld;
    if( m_bClipToBoundary )
        ConstrainToBoundary( &m_vEye );

//    CLog::GetLog().Write(LOG_GAMECONSOLE, "eye %f %f %f", m_vEye.x, m_vEye.y, m_vEye.z );	

    // Update the lookAt position based on the eye position 
    //m_vLookAt = m_vEye - vWorldAhead*5.2f;
    m_vLookAt = m_vEye + vLocalAhead*9.5f; /////
    //m_vLookAt = m_vEye + vWorldAhead;
    m_vLookAt.y = 0.5f;

//   	CLog::GetLog().Write(LOG_GAMECONSOLE, "look %f %f %f", m_vLookAt.x, m_vLookAt.y, m_vLookAt.z );	

    // Update the view matrix
    D3DXMatrixLookAtLH( &m_mView, &m_vEye, &m_vLookAt, &vWorldUp );
    D3DXMatrixInverse( &m_mCameraWorld, NULL, &m_mView );

    //SetViewParams( &m_vEye, &m_vLookAt);//, D3DXVECTOR3(0.0f,1.0f,0.0f));

    // update frustum information
    UpdateCullInfo();

    // update the Wml frustrum
    m_Frustum.Origin() = Vector3f( m_vEye.x, m_vEye.y, m_vEye.z );
    m_Frustum.UVector() = Vector3f( vWorldUp.x, vWorldUp.y, vWorldUp.z );    
    m_Frustum.DVector() = Vector3f( vWorldAhead.x, vWorldAhead.y, vWorldAhead.z );
    m_Frustum.LVector() = m_Frustum.UVector().UnitCross(m_Frustum.DVector());
    m_Frustum.Update();

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

