#include "camera.h"
#include "input.h"


// static menbers
D3DXMATRIX CD3DCamera::m_mView;              // View matrix 
D3DXMATRIX CD3DCamera::m_mProj;              // Projection matrix
CULLINFO   CD3DCamera::m_CullInfo;           // frustrum information for this camera




//-----------------------------------------------------------------------------
// Name: CD3DCamera
// Desc: Constructor
//-----------------------------------------------------------------------------
CD3DCamera::CD3DCamera()
{
    ZeroMemory( m_aKeys, sizeof(BYTE)*CAM_MAX_KEYS );

    // Set attributes for the view matrix
    D3DXVECTOR3 vEyePt    = D3DXVECTOR3(0.0f,0.0f,0.0f);
    D3DXVECTOR3 vLookatPt = D3DXVECTOR3(0.0f,0.0f,1.0f);

    // Setup the view matrix
    SetViewParams( &vEyePt, &vLookatPt );

    // Setup the projection matrix
    SetProjParams( D3DX_PI/4, 1.0f, 1.0f, 1000.0f );

    GetCursorPos( &m_ptLastMousePosition );
    m_bMouseLButtonDown = false;
    m_bMouseMButtonDown = false;
    m_bMouseRButtonDown = false;
    m_nCurrentButtonMask = 0;
    m_nMouseWheelDelta = 0;

    m_fCameraYawAngle = 0.0f;
    m_fCameraPitchAngle = 0.0f;

    m_vVelocity     = D3DXVECTOR3(0,0,0);
    m_bMovementDrag = false;
    m_vVelocityDrag = D3DXVECTOR3(0,0,0);
    m_fDragTimer    = 0.0f;
    m_fTotalDragTimeToZero = 0.25;
    m_vRotVelocity = D3DXVECTOR2(0,0);

    m_fRotationScaler = 0.01f;           
    m_fMoveScaler = 5.0f;           

    m_bInvertPitch = false;
    m_bEnableYAxisMovement = true;
    m_bEnablePositionMovement = true;

    m_vMouseDelta   = D3DXVECTOR2(0,0);
    m_fFramesToSmoothMouseData = 2.0f;

    m_bClipToBoundary = false;
    m_vMinBoundary = D3DXVECTOR3(-1,-1,-1);
    m_vMaxBoundary = D3DXVECTOR3(1,1,1);

    m_bResetCursorAfterMove = false;
    //m_pkObject = NULL;
}


//-----------------------------------------------------------------------------
// Name: SetViewParams
// Desc: Client can call this to change the position and direction of camrea
//-----------------------------------------------------------------------------
VOID CD3DCamera::SetViewParams( D3DXVECTOR3* pvEyePt, D3DXVECTOR3* pvLookatPt )
{
    if( NULL == pvEyePt || NULL == pvLookatPt )
        return;

    m_vDefaultEye = m_vEye = *pvEyePt;
    m_vDefaultLookAt = m_vLookAt = *pvLookatPt;

    // Calc the view matrix
    D3DXVECTOR3 vUp(0,1,0);
    D3DXMatrixLookAtLH( &m_mView, pvEyePt, pvLookatPt, &vUp );

    D3DXMATRIX mInvView;
    D3DXMatrixInverse( &mInvView, NULL, &m_mView );

    // The axis basis vectors and camera position are stored inside the 
    // position matrix in the 4 rows of the camera's world matrix.
    // To figuire out the yaw/pitch of the camera, we just need the Z basis vector
    D3DXVECTOR3* pZBasis = (D3DXVECTOR3*) &mInvView._31;

    m_fCameraYawAngle   = atan2f( pZBasis->x, pZBasis->z );
    float fLen = sqrtf(pZBasis->z*pZBasis->z + pZBasis->x*pZBasis->x);
    m_fCameraPitchAngle = -atan2f( pZBasis->y, fLen );

    // update frustum information
    UpdateCullInfo();
}




//-----------------------------------------------------------------------------
// Name: SetProjParams
// Desc: Calculates the projection matrix based on input params
//-----------------------------------------------------------------------------
VOID CD3DCamera::SetProjParams( FLOAT fFOV, FLOAT fAspect, FLOAT fNearPlane,
                                   FLOAT fFarPlane )
{
    // Set attributes for the projection matrix
    m_fFOV        = fFOV;
    m_fAspect     = fAspect;
    m_fNearPlane  = fNearPlane;
    m_fFarPlane   = fFarPlane;

    D3DXMatrixPerspectiveFovLH( &m_mProj, fFOV, fAspect, fNearPlane, fFarPlane );

    // update frustum information
    UpdateCullInfo();
}




//-----------------------------------------------------------------------------
// Name: HandleMessages
// Desc: Call this from your message proc so this class can handle window messages
//-----------------------------------------------------------------------------
LRESULT CD3DCamera::HandleMessages( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
    UNREFERENCED_PARAMETER( hWnd );
    UNREFERENCED_PARAMETER( lParam );

    switch( uMsg )
    {
        case WM_KEYDOWN:
        {
            // Map this key to a D3DUtil_CameraKeys enum and update the
            // state of m_aKeys[] by adding the KEY_WAS_DOWN_MASK|KEY_IS_DOWN_MASK mask
            // only if the key is not down
            D3DUtil_CameraKeys mappedKey = MapKey( (UINT)wParam );
            if( mappedKey != CAM_UNKNOWN )
            {
                if( FALSE == IsKeyDown(m_aKeys[mappedKey]) )
                    m_aKeys[ mappedKey ] = KEY_WAS_DOWN_MASK | KEY_IS_DOWN_MASK;
            }
            break;
        }

        case WM_KEYUP:
        {
            // Map this key to a D3DUtil_CameraKeys enum and update the
            // state of m_aKeys[] by removing the KEY_IS_DOWN_MASK mask.
            D3DUtil_CameraKeys mappedKey = MapKey( (UINT)wParam );
            if( mappedKey != CAM_UNKNOWN )
                m_aKeys[ mappedKey ] &= ~KEY_IS_DOWN_MASK;
            break;
        }

        case WM_RBUTTONDOWN: 
        case WM_MBUTTONDOWN: 
        case WM_LBUTTONDOWN: 
        {
            // Update member var state
            if( uMsg == WM_LBUTTONDOWN ) { m_bMouseLButtonDown = true; m_nCurrentButtonMask |= MOUSE_LEFT_BUTTON; }
            if( uMsg == WM_MBUTTONDOWN ) { m_bMouseMButtonDown = true; m_nCurrentButtonMask |= MOUSE_MIDDLE_BUTTON; }
            if( uMsg == WM_RBUTTONDOWN ) { m_bMouseRButtonDown = true; m_nCurrentButtonMask |= MOUSE_RIGHT_BUTTON; }

            // Capture the mouse, so if the mouse button is 
            // released outside the window, we'll get the WM_LBUTTONUP message
            SetCapture(hWnd);
            GetCursorPos( &m_ptLastMousePosition ); 
            return TRUE;
        }

        case WM_RBUTTONUP: 
        case WM_MBUTTONUP: 
        case WM_LBUTTONUP:   
        {
            // Update member var state
            if( uMsg == WM_LBUTTONUP ) { m_bMouseLButtonDown = false; m_nCurrentButtonMask &= ~MOUSE_LEFT_BUTTON; }
            if( uMsg == WM_MBUTTONUP ) { m_bMouseMButtonDown = false; m_nCurrentButtonMask &= ~MOUSE_MIDDLE_BUTTON; }
            if( uMsg == WM_RBUTTONUP ) { m_bMouseRButtonDown = false; m_nCurrentButtonMask &= ~MOUSE_RIGHT_BUTTON; }

            // Release the capture if no mouse buttons down
            if( !m_bMouseLButtonDown  && 
                !m_bMouseRButtonDown &&
                !m_bMouseMButtonDown )
            {
                ReleaseCapture();
            }
            break;
        }

        case WM_MOUSEWHEEL:
            // Update member var state
            m_nMouseWheelDelta = (short)HIWORD(wParam) / 120;
            break;
    }

    return FALSE;
}




//-----------------------------------------------------------------------------
// Name: UpdateMouseDelta
// Desc: Figure out the mouse delta based on mouse movement
//-----------------------------------------------------------------------------
void CD3DCamera::UpdateMouseDelta( float fElapsedTime )
{
    UNREFERENCED_PARAMETER( fElapsedTime );

    POINT ptCurMouseDelta;
    POINT ptCurMousePos;
    
    // Get current position of mouse
    GetCursorPos( &ptCurMousePos );

    // Calc how far it's moved since last frame
    ptCurMouseDelta.x = ptCurMousePos.x - m_ptLastMousePosition.x;
    ptCurMouseDelta.y = ptCurMousePos.y - m_ptLastMousePosition.y;

    // Record current position for next time
    m_ptLastMousePosition = ptCurMousePos;

    if( m_bResetCursorAfterMove )
    {
        // Set position of camera to center of desktop, 
        // so it always has room to move.  This is very useful
        // if the cursor is hidden.  If this isn't done and cursor is hidden, 
        // then invisible cursor will hit the edge of the screen 
        // and the user can't tell what happened
        POINT ptCenter;
        RECT rcDesktop;
        GetWindowRect( GetDesktopWindow(), &rcDesktop );
        ptCenter.x = (rcDesktop.right - rcDesktop.left) / 2;
        ptCenter.y = (rcDesktop.bottom - rcDesktop.top) / 2;   
        SetCursorPos( ptCenter.x, ptCenter.y );
        m_ptLastMousePosition = ptCenter;
    }

    // Smooth the relative mouse data over a few frames so it isn't 
    // jerky when moving slowly at low frame rates.
    float fPercentOfNew =  1.0f / m_fFramesToSmoothMouseData;
    float fPercentOfOld =  1.0f - fPercentOfNew;
    m_vMouseDelta.x = m_vMouseDelta.x*fPercentOfOld + ptCurMouseDelta.x*fPercentOfNew;
    m_vMouseDelta.y = m_vMouseDelta.y*fPercentOfOld + ptCurMouseDelta.y*fPercentOfNew;

    m_vRotVelocity = m_vMouseDelta * m_fRotationScaler;
}




//-----------------------------------------------------------------------------
// Name: UpdateVelocity
// Desc: Figure out the velocity based on keyboard input & drag if any
//-----------------------------------------------------------------------------
void CD3DCamera::UpdateVelocity( float fElapsedTime )
{
    D3DXMATRIX mRotDelta;
    D3DXVECTOR3 vAccel = D3DXVECTOR3(0,0,0);

    if( m_bEnablePositionMovement )
    {
        // Update acceleration vector based on keyboard state
        if( IsKeyDown(m_aKeys[CAM_MOVE_FORWARD]) )
            vAccel.z += 1.0f;
        if( IsKeyDown(m_aKeys[CAM_MOVE_BACKWARD]) )
            vAccel.z -= 1.0f;
        if( m_bEnableYAxisMovement )
        {
            if( IsKeyDown(m_aKeys[CAM_MOVE_UP]) )
                vAccel.y += 1.0f;
            if( IsKeyDown(m_aKeys[CAM_MOVE_DOWN]) )
                vAccel.y -= 1.0f;
        }
        if( IsKeyDown(m_aKeys[CAM_STRAFE_RIGHT]) )
            vAccel.x += 1.0f;
        if( IsKeyDown(m_aKeys[CAM_STRAFE_LEFT]) )
            vAccel.x -= 1.0f;
    }

    // Normalize vector so if moving 2 dirs (left & forward), 
    // the camera doesn't move faster than if moving in 1 dir
    D3DXVec3Normalize( &vAccel, &vAccel );

    // Scale the acceleration vector
    vAccel *= m_fMoveScaler;

    if( m_bMovementDrag )
    {
        // Is there any acceleration this frame?
        if( D3DXVec3LengthSq( &vAccel ) > 0 )
        {
            // If so, then this means the user has pressed a movement key\
            // so change the velocity immediately to acceleration 
            // upon keyboard input.  This isn't normal physics
            // but it will give a quick response to keyboard input
            m_vVelocity = vAccel;
            m_fDragTimer = m_fTotalDragTimeToZero;
            m_vVelocityDrag = vAccel / m_fDragTimer;
        }
        else 
        {
            // If no key being pressed, then slowly decrease velocity to 0
            if( m_fDragTimer > 0 )
            {
                // Drag until timer is <= 0
                m_vVelocity -= m_vVelocityDrag * fElapsedTime;
                m_fDragTimer -= fElapsedTime;
            }
            else
            {
                // Zero velocity
                m_vVelocity = D3DXVECTOR3(0,0,0);
            }
        }
    }
    else
    {
        // No drag, so immediatly change the velocity
        m_vVelocity = vAccel;
    }
}




//-----------------------------------------------------------------------------
// Name: ConstrainToBoundary
// Desc: Clamps pV to lie inside m_vMinBoundary & m_vMaxBoundary
//-----------------------------------------------------------------------------
void CD3DCamera::ConstrainToBoundary( D3DXVECTOR3* pV )
{
    // Constrain vector to a bounding box 
    pV->x = max(pV->x, m_vMinBoundary.x);
    pV->y = max(pV->y, m_vMinBoundary.y);
    pV->z = max(pV->z, m_vMinBoundary.z);

    pV->x = min(pV->x, m_vMaxBoundary.x);
    pV->y = min(pV->y, m_vMaxBoundary.y);
    pV->z = min(pV->z, m_vMaxBoundary.z);
}


//-----------------------------------------------------------------------------
// Name: Reset
// Desc: Reset the camera's position back to the default
//-----------------------------------------------------------------------------
VOID CD3DCamera::Reset()
{
    SetViewParams( &m_vDefaultEye, &m_vDefaultLookAt );
}


//-----------------------------------------------------------------------------
// Name: MapKey
// Desc: Maps a windows virtual key to an enum
//-----------------------------------------------------------------------------
D3DUtil_CameraKeys CD3DCamera::MapKey( UINT nKey )
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

        case GAME_UP: 
			return CAM_MOVE_UP;        
        case GAME_DOWN:  
			return CAM_MOVE_DOWN;      

        case 'c':
		case 'C':
			return CAM_MOVE_DOWN;

        case ' ': //spacebar
			return CAM_MOVE_UP;

        case GAME_HOME:   
			return CAM_RESET;
    }

    return CAM_UNKNOWN;
}


void CD3DCamera::HandleInputMessages( CInputTaskMessage * pIMsg )
{
    switch( pIMsg->m_keyDown )
    {
        case TRUE:  // key is down
        {
            // Map this key to a D3DUtil_CameraKeys enum and update the
            // state of m_aKeys[] by adding the KEY_WAS_DOWN_MASK|KEY_IS_DOWN_MASK mask
            // only if the key is not down
            D3DUtil_CameraKeys mappedKey = MapKey( pIMsg->m_keyValue );
            if( mappedKey != CAM_UNKNOWN )
            {
                if( FALSE == IsKeyDown(m_aKeys[mappedKey]) )
                    m_aKeys[ mappedKey ] = KEY_WAS_DOWN_MASK | KEY_IS_DOWN_MASK;
            }
            break;
        }

        case FALSE:  // key is up
        {
            // Map this key to a D3DUtil_CameraKeys enum and update the
            // state of m_aKeys[] by removing the KEY_IS_DOWN_MASK mask.
            D3DUtil_CameraKeys mappedKey = MapKey( pIMsg->m_keyValue );
            if( mappedKey != CAM_UNKNOWN )
                m_aKeys[ mappedKey ] &= ~KEY_IS_DOWN_MASK;
            break;
        }
	}

/*
        case WM_RBUTTONDOWN: 
        case WM_MBUTTONDOWN: 
        case WM_LBUTTONDOWN: 
        {
            // Update member var state
            if( uMsg == WM_LBUTTONDOWN ) { m_bMouseLButtonDown = true; m_nCurrentButtonMask |= MOUSE_LEFT_BUTTON; }
            if( uMsg == WM_MBUTTONDOWN ) { m_bMouseMButtonDown = true; m_nCurrentButtonMask |= MOUSE_MIDDLE_BUTTON; }
            if( uMsg == WM_RBUTTONDOWN ) { m_bMouseRButtonDown = true; m_nCurrentButtonMask |= MOUSE_RIGHT_BUTTON; }

            // Capture the mouse, so if the mouse button is 
            // released outside the window, we'll get the WM_LBUTTONUP message
            SetCapture(hWnd);
            GetCursorPos( &m_ptLastMousePosition ); 
            return TRUE;
        }

        case WM_RBUTTONUP: 
        case WM_MBUTTONUP: 
        case WM_LBUTTONUP:   
        {
            // Update member var state
            if( uMsg == WM_LBUTTONUP ) { m_bMouseLButtonDown = false; m_nCurrentButtonMask &= ~MOUSE_LEFT_BUTTON; }
            if( uMsg == WM_MBUTTONUP ) { m_bMouseMButtonDown = false; m_nCurrentButtonMask &= ~MOUSE_MIDDLE_BUTTON; }
            if( uMsg == WM_RBUTTONUP ) { m_bMouseRButtonDown = false; m_nCurrentButtonMask &= ~MOUSE_RIGHT_BUTTON; }

            // Release the capture if no mouse buttons down
            if( !m_bMouseLButtonDown  && 
                !m_bMouseRButtonDown &&
                !m_bMouseMButtonDown )
            {
                ReleaseCapture();
            }
            break;
        }

        case WM_MOUSEWHEEL:
            // Update member var state
            m_nMouseWheelDelta = (short)HIWORD(wParam) / 120;
            break;
			
    }

    return FALSE;
	*/
}


//-----------------------------------------------------------------------------
// Name: UpdateCullInfo()
// Desc: Sets up the frustum planes, endpoints, and center for the frustum
//       defined by a given view matrix and projection matrix.  
// Defaults: this cameras own view and projection matrix
//-----------------------------------------------------------------------------
void CD3DCamera::UpdateCullInfo( CULLINFO* pCullInfo, D3DXMATRIX* pMatView, D3DXMATRIX* pMatProj )
{
    D3DXMATRIXA16 mat;

    D3DXMatrixMultiply( &mat, pMatView, pMatProj );
    D3DXMatrixInverse( &mat, NULL, &mat );

    pCullInfo->vecFrustum[0] = D3DXVECTOR3(-1.0f, -1.0f,  0.0f); // xyz
    pCullInfo->vecFrustum[1] = D3DXVECTOR3( 1.0f, -1.0f,  0.0f); // Xyz
    pCullInfo->vecFrustum[2] = D3DXVECTOR3(-1.0f,  1.0f,  0.0f); // xYz
    pCullInfo->vecFrustum[3] = D3DXVECTOR3( 1.0f,  1.0f,  0.0f); // XYz
    pCullInfo->vecFrustum[4] = D3DXVECTOR3(-1.0f, -1.0f,  1.0f); // xyZ
    pCullInfo->vecFrustum[5] = D3DXVECTOR3( 1.0f, -1.0f,  1.0f); // XyZ
    pCullInfo->vecFrustum[6] = D3DXVECTOR3(-1.0f,  1.0f,  1.0f); // xYZ
    pCullInfo->vecFrustum[7] = D3DXVECTOR3( 1.0f,  1.0f,  1.0f); // XYZ

    for( INT i = 0; i < 8; i++ )
        D3DXVec3TransformCoord( &pCullInfo->vecFrustum[i], &pCullInfo->vecFrustum[i], &mat );

    D3DXPlaneFromPoints( &pCullInfo->planeFrustum[0], &pCullInfo->vecFrustum[0], 
        &pCullInfo->vecFrustum[1], &pCullInfo->vecFrustum[2] ); // Near
    D3DXPlaneFromPoints( &pCullInfo->planeFrustum[1], &pCullInfo->vecFrustum[6], 
        &pCullInfo->vecFrustum[7], &pCullInfo->vecFrustum[5] ); // Far
    D3DXPlaneFromPoints( &pCullInfo->planeFrustum[2], &pCullInfo->vecFrustum[2], 
        &pCullInfo->vecFrustum[6], &pCullInfo->vecFrustum[4] ); // Left
    D3DXPlaneFromPoints( &pCullInfo->planeFrustum[3], &pCullInfo->vecFrustum[7], 
        &pCullInfo->vecFrustum[3], &pCullInfo->vecFrustum[5] ); // Right
    D3DXPlaneFromPoints( &pCullInfo->planeFrustum[4], &pCullInfo->vecFrustum[2], 
        &pCullInfo->vecFrustum[3], &pCullInfo->vecFrustum[6] ); // Top
    D3DXPlaneFromPoints( &pCullInfo->planeFrustum[5], &pCullInfo->vecFrustum[1], 
        &pCullInfo->vecFrustum[0], &pCullInfo->vecFrustum[4] ); // Bottom
}


//-----------------------------------------------------------------------------
// Name: GetFrustum
// Desc: converts the D3DX CULLINFO to a wml frustrum 
//-----------------------------------------------------------------------------
Frustum3f * CD3DCamera::GetFrustum() 
{
    return &m_Frustum;
}
