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

// --- internal library includes --- //
#include "bos.h"
#include "task.h"
#include "renderer.h"



//-----------------------------------------------------------------------------
// Class:  CRenderTask
//
// Desc:  
//-----------------------------------------------------------------------------
class CRenderTask : public ITask
{
public:
    CRenderTask();
    CRenderTask( CRenderer * pkRenderer );
    void DoMessageHandle ( ITaskMessage *cMsg );
	virtual ~CRenderTask();
    
	bool Start();
	void Update();
	void Stop();
	void Reset();

private:
    CRenderer * m_pkRenderer;  // the renderer attached to this task 
    void HandleInputMessage( CInputTaskMessage * pIMsg );
};



//$$$TODO
//-----------------------------------------------------------------------------
// Class:  CRenderTaskMessage
//
// Desc:  
//-----------------------------------------------------------------------------
class CRenderTaskMessage : public ITaskMessage
{
public:
    CRenderTaskMessage() { m_nMessageType = RENDER_TASK_MESSAGE; };
};