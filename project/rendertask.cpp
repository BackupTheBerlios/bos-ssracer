/*****************************************************************************
*
* File:  rendertask.cpp
*
* BurnOut Studios - Super Street Racer
* Module:  Renderer
* Author:  Jay Javier
* Modified by:  On: 
* Date Created:  Feb 19, 2003
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
    m_pkRenderer->CreateMeshes();

	return true;
}



//-----------------------------------------------------------------------------
// Name:  Update()
// Desc:  Swap frame buffers.  Note that this is independent of the refresh rate
//-----------------------------------------------------------------------------
void CRenderTask::Update()
{
    HandleMessages();

    m_pkRenderer->Click();       // update view from the camera position

    #ifdef _DEBUG
    D3DXVECTOR3 * vEye = m_pkRenderer->GetActiveCameraPtr()->GetEyePtr();
    D3DXVECTOR3 * vLookAt = m_pkRenderer->GetActiveCameraPtr()->GetLookAtPtr();
    D3DXVECTOR3 * vVel = m_pkRenderer->GetActiveCameraPtr()->GetVelocityPtr();
    CLog::GetLog().Write(LOG_DEBUGOVERLAY, 0, "Cam Eye Position %f %f %f", vEye->x, vEye->y, vEye->z);
    CLog::GetLog().Write(LOG_DEBUGOVERLAY, 1, "Cam Look At %f %f %f", vLookAt->x, vLookAt->y, vLookAt->z);
    CLog::GetLog().Write(LOG_DEBUGOVERLAY, 2, "Cam Velocity %f %f %f", vVel->x, vVel->y, vVel->z);
    #endif

    m_pkRenderer->RenderScene(); // render current scene
    
    if ( CBOSApplication::GetBOSApp().GetConsoleState() == TRUE ) 
        m_pkRenderer->DrawConsole(); // draw the console if down

    #ifdef _DEBUG
    if ( CBOSApplication::GetBOSApp().GetDebugOverlayState() == TRUE ) {
        CLog::GetLog().Write(LOG_DEBUGOVERLAY, 5, "J: slots 0-9 in the LOG_DEBUGOVERLAY are mine");
        CLog::GetLog().Write(LOG_DEBUGOVERLAY, 6, "reserve your own slots");
        CLog::GetLog().Write(LOG_DEBUGOVERLAY, 7, "usage Write(LOG_DEBUGOVERLAY, slot#,...)");
        CLog::GetLog().Write(LOG_DEBUGOVERLAY, 8, "use this to monitor variables");
        CLog::GetLog().Write(LOG_DEBUGOVERLAY, 9, "press F12 to hide all this");
        CLog::GetLog().Write(LOG_DEBUGOVERLAY, 10, "line 10");
        CLog::GetLog().Write(LOG_DEBUGOVERLAY, 20, "line 20");
        CLog::GetLog().Write(LOG_DEBUGOVERLAY, 30, "line 30");
        CLog::GetLog().Write(LOG_DEBUGOVERLAY, 40, "line 40");
        CLog::GetLog().Write(LOG_DEBUGOVERLAY, 100, "line 100");
        m_pkRenderer->DrawDebugOverlay();  // draw the debugging overlay
    }
    #endif
        
    m_pkRenderer->DisplayBackBuffer();  // swap buffers
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