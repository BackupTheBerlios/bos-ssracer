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
#include "game.h"

#include "WmlVector3.h"
using namespace Wml;

//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
CRenderTask::CRenderTask()
{
    m_nTaskType = RENDER_TASK;

//    m_pkRenderer = CBOSApplication::GetBOSApp().GetRendererPtr();
//    assert(m_pkRenderer);
    CBOSApplication * pBOSApp = CBOSApplication::GetBOSAppPtr();

    // create the renderer for this app
    m_pkRenderer = new CRenderer(pBOSApp->IsFullScreen(), pBOSApp->GetMainWindowHandle(),
                                 (UINT)pBOSApp->GetWidth(), (UINT)pBOSApp->GetHeight());
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
    delete m_pkRenderer;
    delete m_pkCamera;
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

    // set default camera model
    //m_pkRenderer->SetCamera();

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

    m_pkRenderer->Click();       // update view from the camera position

    m_pkRenderer->RenderScene(); // render current scene
    
    if ( CBOSApplication::GetBOSApp().GetConsoleState() == TRUE ) 
        m_pkRenderer->DrawConsole(); // draw the console
        
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


void CRenderTask::DoMessageHandle(ITaskMessage *cMsg) 
{
    #ifdef _DEBUG
    //CLog::GetLog().Write( LOG_MISC, IDS_RENDER_MSG, "Handled a message" );
    #endif
   
}

//END rendertask.cpp ==============================================================