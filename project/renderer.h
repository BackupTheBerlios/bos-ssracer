/*****************************************************************************
*
* File:  renderer.h
*
* BurnOut Studios - Super Street Racer
* Module:  Renderer
* Author:  Jay Javier
* Modified by:  On: 
* Date Created:  Feb 12, 2004
*
******************************************************************************
* Desc:  
*****************************************************************************/
#ifndef RENDERER_H
#define RENDERER_H

// --- system includes --- //
#include "bos.h"
#include <D3D9.h>
#define STL_USING_ALL
#include "stl.h"

// --- internal library includes --- //
#include "camerafreelook.h"
#include "camerachase.h"
#include "log.h"
#include "d3denumeration.h"
#include "d3dsettings.h"
#include "d3dfont.h"
#include "d3dfile.h"

// --- defines and constants --- //
// fonts available to render
#define FONT_DEFAULT 0
#define FONT_SYSTEM 1
#define FONT_SMALL 2

class CRenderTask; // forward declaration
//class CObject;
//class CPlayerVehicle;

// camera types renderer uses
enum CameraType 
{
    CAMERA_FREELOOK,
    CAMERA_CHASE,
    CAMERA_BUMPER,
    CAMERA_UNKNOWN = 0xFF
};

class CQuadNode;

//-----------------------------------------------------------------------------
// Class: CRenderer
// Desc: 
//-----------------------------------------------------------------------------
class CRenderer 
{
    friend class CRenderTask;
    /////////////////////////////// class members /////////////////////////////
public:

protected:
    BOOL              m_bFullScreen;
    BOOL              m_bConsoleDown;      // indicates if console overlay is to be drawn
    
    static CD3DSettings      m_d3dSettings;
    static CD3DEnumeration   m_d3dEnumeration;

    D3DPRESENT_PARAMETERS m_d3dpp;         // Parameters for CreateDevice/Reset
    HWND              m_hWnd;              // The main app window
    //HWND              m_hWndFocus;         // The D3D focus window (usually same as m_hWnd)
    //HMENU             m_hMenu;             // App menu bar (stored here when fullscreen)
    static LPDIRECT3D9       m_pD3D;              // The main D3D object
    static LPDIRECT3DDEVICE9 m_pd3dDevice;        // The D3D rendering device
    D3DCAPS9          m_d3dCaps;           // Caps for the device
    D3DSURFACE_DESC   m_d3dsdBackBuffer;   // Surface desc of the backbuffer
    DWORD             m_dwCreateFlags;     // Indicate sw or hw vertex processing
    DWORD             m_dwWindowStyle;     // Saved window style for mode switches
    RECT              m_rcWindowBounds;    // Saved window bounds for mode switches
    RECT              m_rcWindowClient;    // Saved client area size for mode switches

    bool              m_bDeviceLost;
    bool              m_bCursorVisible;
    RECT              m_rcWindow;

    bool              m_bVisCullingEnabled; // enable culling
    bool              m_bDrawEntBBoxes;     //$$$DEBUG show bounding boxed for entities
    bool              m_bDrawQNodeBBoxes;     //$$$DEBUG show bounding boxed for quadtree nodes

    static HRESULT ms_hResult;
	static CRenderer * ms_pkRenderer;

private:
    // window parameters
    UINT m_iXpos, m_iYpos, m_iWidth, m_iHeight, m_iQuantity;

    std::map< unsigned int, CD3DFont * > m_kFontMap;       // fonts available to this app    
    static std::map< unsigned int, CD3DCamera * > m_pkCameraMap;  // cameras used by this renderer
    //static std::map< std::string, CD3DMesh * > m_kMeshMap;       // meshes available to this app

    std::map< int, bool > m_kDrawnEntIDs;

    CD3DCamera * m_pActiveCamera; // active camera in game
    static CameraType m_eActiveCamType;     // type of active camera

    CD3DMesh * m_pSkyBox;

    // renderer capabilities
    bool m_bCapMultitexture;
    bool m_bCapSpecularAfterTexture;
    bool m_bCapPlanarReflection;
    bool m_bCapPlanarShadow;
    bool m_bCapTextureClampToBorder;
    bool m_bCapTextureApplyAdd;
    bool m_bCapTextureApplyCombine;
    bool m_bCapTextureApplyCombineDot3;
    bool m_bCapDot3BumpMapping;


    ////////////////////////////// member functions ///////////////////////////
public:
    CRenderer (BOOL bFullScreen, HWND hWnd, UINT iWidth, UINT iHeight);

	static CRenderer & GetRenderer();
    static CRenderer * GetRendererPtr();

	LPDIRECT3DDEVICE9 GetDevice() {return m_pd3dDevice;}

    HRESULT Initialize();
    void Cleanup();
    int CreateMesh( CD3DMesh * pMesh, char * pcFileName );
  
    void EstablishCapabilities ();

    bool CheckDevice();
    //IDevice* GetDevice ();
    void ResetDevice();
    void OnDeviceLost();

    // set a camera to use a different model
    CD3DCamera * SetCamera ( CD3DCamera* pkCamera, CameraType eCameraName = CAMERA_FREELOOK );
    
    // get a camera by type
    CD3DCamera * GetCameraPtr ( CameraType eCameraName = CAMERA_FREELOOK );

    // set the active camera for viewing
    bool SetActiveCamera( CameraType eCameraName );

    // get the camera being currently used
    CD3DCamera * GetActiveCameraPtr() { return m_pActiveCamera; };

    // get the camera type currently being used
    CameraType GetActiveCameraType() { return m_eActiveCamType; };

    bool IsVisCullingEnabled() {return m_bVisCullingEnabled;};
    void SetVisCulling( bool bState) { m_bVisCullingEnabled = bState;};

    bool IsDrawEntBBoxesEnabled() {return m_bDrawEntBBoxes;};
    void SetDrawEntBBoxes( bool bState) { m_bDrawEntBBoxes = bState;};

    bool IsQNodeBBoxesEnabled() {return m_bDrawQNodeBBoxes;};
    void SetDrawQNodeBBoxes( bool bState) { m_bDrawQNodeBBoxes = bState;};


    void InitializeState();
    //void SetState (const RenderStatePtr aspkState[]);

    void RenderScene();
    //virtual bool BeginScene ();
    //virtual void EndScene ();

    void ToggleFullScreen (int  riNewWidth, int  riNewHeight);
    bool IsWindowed () { return m_d3dSettings.IsWindowed; }; 
    void ShowCursor (bool bShow){  m_pd3dDevice->ShowCursor(bShow); };

    void DisplayBackBuffer ();

    void Click();  // update the view from the active camera(s)

    //virtual void Move (int iXPos, int iYPos);
    //virtual void Resize (int iWidth, int iHeight);
    //virtual void Reshape (int iStartX, int iStartY, int iEndX, int iEndY);
    
    //virtual void Activate ();
    //virtual void Suspend ();
    //virtual void Resume ();

    int GetX() const;
    int GetY() const;
    int GetWidth () const;
    int GetHeight () const;

    //void DrawObject( CObject * pkObject );    
    //void DrawVehicle( CPlayerVehicle * pkObject);

protected:
    CRenderer();
    ~CRenderer ();

    // draw functions
    void DrawConsole();
    void DrawSkyBox();
    void DrawDebugOverlay();
    void DrawEntity( CEntity * pEntity );
    void DrawQuadTreeNode( CQuadNode * pQNode );
    void DrawBBox( Box3f * pBBox, float fPointSize = 1.0f, DWORD dwColor = D3DCOLOR_ARGB( 255, 155, 155, 155 ));
    void DrawVehicle( CVehicle * pVehicle );


private:
};
#endif
//end renderer.h ==============================================================