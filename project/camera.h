#ifndef CAMERA_H
#define CAMERA_H

#include "bos.h"
#include <d3dx9.h>
#include <dxerr9.h>

#include "inputmessage.h"

#include "WmlVector3.h"
#include "WmlFrustum3.h"

using namespace Wml;

//class CObject;
class CPlayerVehicle;


//-----------------------------------------------------------------------------
// Name: struct CULLINFO
// Desc: Stores information that will be used when culling objects.  It needs
//       to be recomputed whenever the view matrix or projection matrix changes.
//-----------------------------------------------------------------------------
struct CULLINFO
{
    D3DXVECTOR3 vecFrustum[8];    // corners of the view frustum
    D3DXPLANE planeFrustum[6];    // planes of the view frustum
};


//-----------------------------------------------------------------------------
// Name: enum D3DUtil_CameraKeys 
// Desc: used by CCamera to map WM_KEYDOWN keys
//-----------------------------------------------------------------------------
enum D3DUtil_CameraKeys
{   // base camera actions
    CAM_STRAFE_LEFT = 0,
    CAM_STRAFE_RIGHT,
    CAM_MOVE_FORWARD,
    CAM_MOVE_BACKWARD,
    CAM_MOVE_UP,
    CAM_MOVE_DOWN,
    CAM_RESET,


	// extended actions
	CAM_ROTATE_X_POS,  // yaw
	CAM_ROTATE_X_NEG,
	CAM_ROTATE_Y_POS,  // pitch
	CAM_ROTATE_Y_NEG,
    CAM_MAX_KEYS,	

	// default
    CAM_UNKNOWN = 0xFF
};

//	CAM_ROTATE_Z,  // roll

#define KEY_WAS_DOWN_MASK 0x80
#define KEY_IS_DOWN_MASK  0x01

#define MOUSE_LEFT_BUTTON   0x01
#define MOUSE_MIDDLE_BUTTON 0x02
#define MOUSE_RIGHT_BUTTON  0x04
#define MOUSE_WHEEL         0x08


//-----------------------------------------------------------------------------
// Name: class CD3DCamera
// Desc:
//-----------------------------------------------------------------------------
class CD3DCamera
{
public:
    CD3DCamera();
    // Call these from client and use Get*Matrix() to read new matrices
	virtual void CD3DCamera::HandleInputMessages( CInputTaskMessage * pIMsg );
    virtual LRESULT HandleMessages( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
    virtual VOID    FrameMove( FLOAT fElapsedTime ) = 0;

    // Functions to change camera matrices
    virtual void Reset(); 
    VOID SetViewParams( D3DXVECTOR3* pvEyePt, D3DXVECTOR3* pvLookatPt );
    VOID SetProjParams( FLOAT fFOV, FLOAT fAspect, FLOAT fNearPlane, FLOAT fFarPlane );

    // Functions to change behavior
    VOID SetInvertPitch( bool bInvertPitch ) { m_bInvertPitch = bInvertPitch; }
    VOID SetDrag( bool bMovementDrag, FLOAT fTotalDragTimeToZero = 0.25f ) { m_bMovementDrag = bMovementDrag; m_fTotalDragTimeToZero = fTotalDragTimeToZero; }
    VOID SetEnableYAxisMovement( bool bEnableYAxisMovement ) { m_bEnableYAxisMovement = bEnableYAxisMovement; }
    VOID SetEnablePositionMovement( bool bEnablePositionMovement ) { m_bEnablePositionMovement = bEnablePositionMovement; }
    VOID SetClipToBoundary( bool bClipToBoundary, D3DXVECTOR3* pvMinBoundary, D3DXVECTOR3* pvMaxBoundary ) { m_bClipToBoundary = bClipToBoundary; if( pvMinBoundary ) m_vMinBoundary = *pvMinBoundary; if( pvMaxBoundary ) m_vMaxBoundary = *pvMaxBoundary; }
    VOID SetScalers( FLOAT fRotationScaler = 0.01f, FLOAT fMoveScaler = 5.0f )  { m_fRotationScaler = fRotationScaler; m_fMoveScaler = fMoveScaler; }
    VOID SetNumberOfFramesToSmoothMouseData( int nFrames ) { if( nFrames > 0 ) m_fFramesToSmoothMouseData = (float)nFrames; }
    VOID SetResetCursorAfterMove( bool bResetCursorAfterMove ) { m_bResetCursorAfterMove = bResetCursorAfterMove; }

    // Functions to get state
    D3DXMATRIX*  GetViewMatrix()            { return &m_mView; }
    D3DXMATRIX*  GetProjMatrix()            { return &m_mProj; }
    CULLINFO*    GetCullInfo()              { return &m_CullInfo; }
    bool IsBeingDragged() { return (m_bMouseLButtonDown || m_bMouseMButtonDown || m_bMouseRButtonDown); }
    bool IsMouseLButtonDown() { return m_bMouseLButtonDown; } 
    bool IsMouseMButtonDown() { return m_bMouseMButtonDown; } 
    bool IsMouseRButtonDown() { return m_bMouseRButtonDown; } 


    // camera update functions
    virtual void Update(){ /* does nothing */};
	virtual void Update( int iInput, bool bState ) { /* does nothing */};

    // updates frustum information for a view and projection matrix
    // defaults to matrices used by this camera
    void UpdateCullInfo(CULLINFO* pCullInfo = &m_CullInfo, D3DXMATRIX* pMatView = &m_mView, D3DXMATRIX* pMatProj = &m_mProj);

    Frustum3f * GetFrustum();

    Vector3f GetEye() { return Vector3f(m_vEye.x, m_vEye.y, m_vEye.z); };
    Vector3f GetLookAt() { return Vector3f(m_vLookAt.x, m_vLookAt.y, m_vLookAt.z); };
    Vector3f GetVelocity() { return Vector3f(m_vVelocity.x, m_vVelocity.y, m_vVelocity.z); };
    D3DXVECTOR3 * GetEyePtr() { return &m_vEye; };
    D3DXVECTOR3 * GetLookAtPtr() { return &m_vLookAt; };
    D3DXVECTOR3 * GetVelocityPtr() { return &m_vVelocity; };

protected:
    // Functions to map an input key to a D3DUtil_CameraKeys enum
    virtual D3DUtil_CameraKeys MapKey( UINT nKey );    
    BOOL IsKeyDown( BYTE key )  { return( (key & KEY_IS_DOWN_MASK) == KEY_IS_DOWN_MASK ); }
    BOOL WasKeyDown( BYTE key ) { return( (key & KEY_WAS_DOWN_MASK) == KEY_WAS_DOWN_MASK ); }

    void ConstrainToBoundary( D3DXVECTOR3* pV );
    void UpdateMouseDelta( float fElapsedTime );
    void UpdateVelocity( float fElapsedTime );

    static D3DXMATRIX            m_mView;         // View matrix 
    static D3DXMATRIX            m_mProj;         // Projection matrix
    static CULLINFO              m_CullInfo;      // frustrum information for this camera

    BYTE                  m_aKeys[CAM_MAX_KEYS];  // State of input - KEY_WAS_DOWN_MASK|KEY_IS_DOWN_MASK
    POINT                 m_ptLastMousePosition;  // Last absolute postion of mouse cursor
    bool                  m_bMouseLButtonDown;    // True if left button is down 
    bool                  m_bMouseMButtonDown;    // True if middle button is down 
    bool                  m_bMouseRButtonDown;    // True if right button is down 
    int                   m_nCurrentButtonMask;   // mask of which buttons are down
    int                   m_nMouseWheelDelta;     // Amount of middle wheel scroll (+/-) 
    D3DXVECTOR2           m_vMouseDelta;          // Mouse relative delta smoothed over a few frames
    float                 m_fFramesToSmoothMouseData; // Number of frames to smooth mouse data over

    D3DXVECTOR3           m_vDefaultEye;          // Default camera eye position
    D3DXVECTOR3           m_vDefaultLookAt;       // Default LookAt position
    D3DXVECTOR3           m_vEye;                 // Camera eye position
    D3DXVECTOR3           m_vLookAt;              // LookAt position
    float                 m_fCameraYawAngle;      // Yaw angle of camera
    float                 m_fCameraPitchAngle;    // Pitch angle of camera

    D3DXVECTOR3           m_vVelocity;            // Velocity of camera
    bool                  m_bMovementDrag;        // If true, then camera movement will slow to a stop otherwise movement is instant
    D3DXVECTOR3           m_vVelocityDrag;        // Velocity drag force
    FLOAT                 m_fDragTimer;           // Countdown timer to apply drag
    FLOAT                 m_fTotalDragTimeToZero; // Time it takes for velocity to go from full to 0
    D3DXVECTOR2           m_vRotVelocity;         // Velocity of camera

    float                 m_fFOV;                 // Field of view
    float                 m_fAspect;              // Aspect ratio
    float                 m_fNearPlane;           // Near plane
    float                 m_fFarPlane;            // Far plane

    float                 m_fRotationScaler;      // Scaler for rotation
    float                 m_fMoveScaler;          // Scaler for movement

    bool                  m_bInvertPitch;         // Invert the pitch axis
    bool                  m_bEnablePositionMovement; // If true, then the user can translate the camera/model 
    bool                  m_bEnableYAxisMovement; // If true, then camera can move in the y-axis

    bool                  m_bClipToBoundary;      // If true, then the camera will be clipped to the boundary
    D3DXVECTOR3           m_vMinBoundary;         // Min point in clip boundary
    D3DXVECTOR3           m_vMaxBoundary;         // Max point in clip boundary

    bool                  m_bResetCursorAfterMove;// If true, the class will reset the cursor position so that the cursor always has space to move 

    Frustum3f             m_Frustum;  // wml frustum information for this camera
private:

};

#endif
//end camera.h ================================================================