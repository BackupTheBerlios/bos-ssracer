/*****************************************************************************
*
* File:  rendertask.cpp
*
* BurnOut Studios - Super Street Racer
* Module:  Renderer
* Author:  Jay Javier
* Modified by:  On: 
* Date Created:  Feb 19, 2004
*
******************************************************************************
* Desc:  
*****************************************************************************/

// --- system includes --- //
#include "bos.h"
#include "dxutil.h"

// --- internal library includes --- //
#include "rendertask.h"
#include "renderer.h"
#include "bosapp.h"
#include "kernel.h"
#include "timer.h"

#include "WmlVector3.h"
using namespace Wml;

//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
CRenderTask::CRenderTask()
{
    m_nTaskType = RENDER_TASK;

    CBOSApplication * pBOSApp = CBOSApplication::GetBOSAppPtr();

    // create the renderer for this app
    new CRenderer(pBOSApp->IsFullScreen(), pBOSApp->GetMainWindowHandle(),
                                 (UINT)pBOSApp->GetWidth(), (UINT)pBOSApp->GetHeight());
    m_pkRenderer = CRenderer::GetRendererPtr();
}



//-----------------------------------------------------------------------------
// Name:  CRenderTask()
// Desc:  Create the task for a specific renderer
//-----------------------------------------------------------------------------
CRenderTask::CRenderTask( CRenderer * pkRenderer )
{
  m_pkRenderer = pkRenderer;
}



//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
CRenderTask::~CRenderTask()
{
    delete CRenderer::GetRendererPtr();
}



//-----------------------------------------------------------------------------
// Name:  Start()
// Desc:  
//-----------------------------------------------------------------------------
bool CRenderTask::Start()
{
#ifdef _DEBUG
    CLog::GetLog().Write( LOG_APP, IDS_RENDER_MSG, "Starting Render Task" );
#endif

    // initialize D3D subsystem in renderer
    m_pkRenderer->Initialize();

    m_pkRenderer->InitializeState();

    // establish device caps and check if it meets the minimum requirements

    // get game settings for graphics

    // set up loaded map resources (textures meshes)
    //m_pkRenderer->CreateMeshes();

	return true;
}



//-----------------------------------------------------------------------------
// Name:  Update()
// Desc:  Swap frame buffers.  Note that this is independent of the refresh rate
//-----------------------------------------------------------------------------
void CRenderTask::Update()
{
    HandleMessages();

    // clear camera debug info
    #ifdef _DEBUG
    CLog::GetLog().Write(LOG_DEBUGOVERLAY, 0, "");
    CLog::GetLog().Write(LOG_DEBUGOVERLAY, 1, "");
    CLog::GetLog().Write(LOG_DEBUGOVERLAY, 2, "");
    CLog::GetLog().Write(LOG_DEBUGOVERLAY, 3, "");
    CLog::GetLog().Write(LOG_DEBUGOVERLAY, 4, "");
    CLog::GetLog().Write(LOG_DEBUGOVERLAY, 5, "");
    CLog::GetLog().Write(LOG_DEBUGOVERLAY, 6, "");
    CLog::GetLog().Write(LOG_DEBUGOVERLAY, 7, "");
    CLog::GetLog().Write(LOG_DEBUGOVERLAY, 8, "");
    CLog::GetLog().Write(LOG_DEBUGOVERLAY, 9, "");
    CLog::GetLog().Write(LOG_DEBUGOVERLAY, 10, "");
    #endif

    //--- update view from the camera position ---//
    m_pkRenderer->Click();       

    //$$$DEBUG display camera info
    #ifdef _DEBUG
    switch (CRenderer::GetRenderer().GetActiveCameraType())  {
    case CAMERA_FREELOOK:
        CLog::GetLog().Write(LOG_DEBUGOVERLAY, 0, "CAMERA_FREELOOK");
        break;
    case CAMERA_CHASE:
        CLog::GetLog().Write(LOG_DEBUGOVERLAY, 0, "CAMERA_CHASE");
        break;
    case CAMERA_BUMPER:
        CLog::GetLog().Write(LOG_DEBUGOVERLAY, 0, "CAMERA_BUMPER");
        break;
    default:
        CLog::GetLog().Write(LOG_DEBUGOVERLAY, 0, "CAMERA_UNKNOWN");
        break;
    }
    D3DXVECTOR3 * vEye = m_pkRenderer->GetActiveCameraPtr()->GetEyePtr();
    D3DXVECTOR3 * vLookAt = m_pkRenderer->GetActiveCameraPtr()->GetLookAtPtr();
    D3DXVECTOR3 * vVel = m_pkRenderer->GetActiveCameraPtr()->GetVelocityPtr();
    CLog::GetLog().Write(LOG_DEBUGOVERLAY, 1, "Cam Eye Position %f %f %f", vEye->x, vEye->y, vEye->z);
    CLog::GetLog().Write(LOG_DEBUGOVERLAY, 2, "Cam Look At %f %f %f", vLookAt->x, vLookAt->y, vLookAt->z);
    CLog::GetLog().Write(LOG_DEBUGOVERLAY, 3, "Cam Velocity %f %f %f", vVel->x, vVel->y, vVel->z);


    CLog::GetLog().Write(LOG_DEBUGOVERLAY, 7, "Cam viscull state%d", m_pkRenderer->IsVisCullingEnabled());
    #endif


    //--- render HUD if we're in-game ---//

    //--- render current scene ---//
    m_pkRenderer->RenderScene(); 
    
    //--- draw the console if down ---//
    if ( CBOSApplication::GetBOSApp().GetConsoleState() == TRUE ) 
        m_pkRenderer->DrawConsole(); 

    #ifdef _DEBUG
    if ( CBOSApplication::GetBOSApp().GetDebugOverlayState() == TRUE ) {
        CLog::GetLog().Write(LOG_DEBUGOVERLAY, 9, "press F12 to hide all this");
        CLog::GetLog().Write(LOG_DEBUGOVERLAY, 19, "J:  got lines 0-19");
        CLog::GetLog().Write(LOG_DEBUGOVERLAY, 20, "line 20");
        CLog::GetLog().Write(LOG_DEBUGOVERLAY, 30, "line 30");
        CLog::GetLog().Write(LOG_DEBUGOVERLAY, 40, "line 40");
        CLog::GetLog().Write(LOG_DEBUGOVERLAY, 100, "line 100");
        m_pkRenderer->DrawDebugOverlay();  // draw the debugging overlay
    }
    #endif
        
    //--- swap buffers to display rendered image ---//
    m_pkRenderer->DisplayBackBuffer();  
}



//-----------------------------------------------------------------------------
// Name:  Reset()
// Desc:  Tear down and re-initialize D3D
//-----------------------------------------------------------------------------
void CRenderTask::Reset()
{
    #ifdef _DEBUG
    CLog::GetLog().Write( LOG_APP, IDS_RENDER_MSG, "Resetting Render Task" );
    #endif
    Start();  // reinitialize D3D
}



//-----------------------------------------------------------------------------
// Name:  Stop()
// Desc:  
//-----------------------------------------------------------------------------
void CRenderTask::Stop()
{
    #ifdef _DEBUG
    CLog::GetLog().Write( LOG_APP, IDS_RENDER_MSG, "Stopping Render Task" );
    #endif

    // destroy the renderer
    m_pkRenderer->Cleanup();
}


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void CRenderTask::DoMessageHandle(ITaskMessage *cMsg) 
{
    #ifdef _DEBUG
    //CLog::GetLog().Write( LOG_MISC, IDS_RENDER_MSG, "Handled a message" );
    #endif

    // usually gets input messages
	switch ( cMsg->GetType() ) {

	case INPUT_TASK_MESSAGE:
		HandleInputMessage( (CInputTaskMessage *)cMsg );
		break;

	default:
		#ifdef _DEBUG
		CLog::GetLog().Write(LOG_MISC, "Render Task: Message type %d not recognized.", cMsg->GetType() );
		#endif
		break;
	}

   
}



//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void CRenderTask::HandleInputMessage( CInputTaskMessage * pIMsg )
{
    #ifdef _DEBUG
    //CLog::GetLog().Write( LOG_GAMECONSOLE, IDS_RENDER_MSG, "Handled an Input message" );
    #endif

    // forward it to the camera
    m_pkRenderer->GetActiveCameraPtr()->Update(pIMsg->m_keyValue, pIMsg->m_keyDown);

}

//END rendertask.cpp ==============================================================