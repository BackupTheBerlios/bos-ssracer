/*****************************************************************************
*
* File:  rendererdrawfunctions.cpp
*
* BurnOut Studios - Super Street Racer
* Module:  Renderer
* Author:  Jay Javier
* Modified by:  On: 
* Date Created:  
*
******************************************************************************
* Desc:  Drawing functions renderer uses
*****************************************************************************/

#include "WmlVector3.h"
using namespace Wml;

// --- internal library includes --- //
#include "timer.h"
#include "renderer.h"
#include "gamestatemanager.h"
#include "settings.h"
#include "cinputconsole.h"
#include "macros.h"
#include "quadtree.h"
#include "cfrontendmanager.h"
#include "renderervertexformats.h"


// --- system includes --- //
#define STL_USING_ALL
#include "stl.h"



//-----------------------------------------------------------------------------
// Name:  DrawConsole()
// Desc:  draws the contents of the in game console
//-----------------------------------------------------------------------------
void CRenderer::DrawConsole()
{
	int iConsoleLine = -1;
    unsigned int uiMaxLinesOnScreen = m_d3dpp.BackBufferHeight;
    SIZE kFontSize;                                   // font properties
    
    // get font dimensions so we know how far to space each line
    m_kFontMap[FONT_SMALL]->GetTextExtent(_T("A"), &kFontSize );
	iConsoleLine = m_d3dpp.BackBufferHeight-(kFontSize.cy);//*3/4;   // current Y coordinate in console

    // calculate how many lines we can actually display
    uiMaxLinesOnScreen /= kFontSize.cy;

    // get the buffer contents
    std::string * strInBuf = CInputConsole::GetConsolePtr()->getBuffer();

    // draw the blinking prompt if buffer is empty
    if ( ( (int)CTimer::GetTimer().GetCurrTime() % 2) || ( *strInBuf != std::string("")) )  {
        m_kFontMap[FONT_SMALL]->DrawText( 0.0f, (float)iConsoleLine, D3DCOLOR_ARGB(255,255,255,20), ">> ", D3DFONT_FILTERED);
    }

    // display contents of the current command buffer
    m_kFontMap[FONT_SMALL]->DrawText( (float)3*kFontSize.cx, (float)iConsoleLine, 
                                      D3DCOLOR_ARGB(255,255,255,20),
                                      strInBuf->c_str(), D3DFONT_FILTERED);

    // go through each string in the console buffer and render text
    std::deque< std::string >::reverse_iterator it;
	
    unsigned int i = 1;
    unsigned int uiNumNewlines = 1;
    const char * szBuf;
    for ( it=CLog::GetLog().m_kConsoleQueue.rbegin(); it!=CLog::GetLog().m_kConsoleQueue.rend(); it++)  {
        szBuf = it->c_str();        
        uiNumNewlines = 0;

        //find # of newline chars to adjust font spacing
        int iStrIndex=0;
        do {
             uiNumNewlines++;  
             iStrIndex = it->find("\n", iStrIndex);
             if (iStrIndex == -1) break;
             else iStrIndex++;
        }  while (iStrIndex < signed(it->length()));

        iConsoleLine -= kFontSize.cy*uiNumNewlines;      // font spacing
        m_kFontMap[FONT_SMALL]->DrawText( 0.0f, (float)iConsoleLine, D3DCOLOR_ARGB(255,255,255,20),
                                          szBuf, D3DFONT_FILTERED);
        if (i>uiMaxLinesOnScreen)  
            break;  // can't fit anymore lines on screen
        else 
            i += uiNumNewlines;
    }

}



//-----------------------------------------------------------------------------
// Name:  DrawSkyBox()
// Desc:  draws the currently loaded skybox mesh
//-----------------------------------------------------------------------------
void CRenderer::DrawSkyBox()
{
    // turn lighting off
    m_pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );

    // save the current view matrix
    D3DXMATRIXA16 matViewSave, matWorldSave;
    m_pd3dDevice->GetTransform( D3DTS_VIEW, &matViewSave );
    m_pd3dDevice->GetTransform( D3DTS_WORLD, &matWorldSave );

    D3DXMATRIXA16 matWorld;
    // scale the skybox up
    D3DXMatrixScaling( &matWorld, 10.0f, 10.0f, 10.0f );

    D3DXMATRIXA16 matView(*m_pActiveCamera->GetViewMatrix());
    // zero out rotations so the skybox doesn't rotate
    matView._41 = matView._42 = matView._43 = 0.0f;

    m_pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld );
    m_pd3dDevice->SetTransform( D3DTS_VIEW, &matView );
    m_pd3dDevice->SetTransform( D3DTS_PROJECTION, m_pActiveCamera->GetProjMatrix() );

    // use linear filtering with clamping to produce smoothed texture with no seams
    m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR ); //
    m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR ); //
    m_pd3dDevice->SetSamplerState( 0, D3DSAMP_ADDRESSU,  D3DTADDRESS_CLAMP ); //
    m_pd3dDevice->SetSamplerState( 0, D3DSAMP_ADDRESSV,  D3DTADDRESS_CLAMP ); //
    if( (m_d3dCaps.TextureAddressCaps & D3DPTADDRESSCAPS_MIRROR) == D3DPTADDRESSCAPS_MIRROR )
    {
        m_pd3dDevice->SetSamplerState( 0, D3DSAMP_ADDRESSU,  D3DTADDRESS_MIRROR );
        m_pd3dDevice->SetSamplerState( 0, D3DSAMP_ADDRESSV,  D3DTADDRESS_MIRROR );
    }

    m_pd3dDevice->SetRenderState( D3DRS_ZENABLE, FALSE );
    // Some cards do not disable writing to Z when 
    // D3DRS_ZENABLE is FALSE. So do it explicitly
    m_pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE, FALSE );

    // Render the skybox
    m_pSkyBox->Render( m_pd3dDevice );

    // Restore the render states
    m_pd3dDevice->SetTransform( D3DTS_WORLD,    &matWorldSave );
    m_pd3dDevice->SetTransform( D3DTS_VIEW,      &matViewSave );

/*    // Center view matrix for skybox and disable zbuffer
    D3DXMATRIXA16 matView, matViewSave;
    m_pd3dDevice->GetTransform( D3DTS_VIEW, &matViewSave );
    matView = matViewSave;

    // zero out rotations so the skybox doesn't rotate
    matView._41 = 0.0f; 
    matView._42 = -3.0f; 
    matView._43 = 0.0f;

    m_pd3dDevice->SetTransform( D3DTS_VIEW,      &matView );
    m_pd3dDevice->SetRenderState( D3DRS_ZENABLE, FALSE );
    // Some cards do not disable writing to Z when 
    // D3DRS_ZENABLE is FALSE. So do it explicitly
    m_pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE, FALSE );

    // Render the skybox
    m_pSkyBox->Render( m_pd3dDevice );

    // Restore the render states
    m_pd3dDevice->SetTransform( D3DTS_VIEW,      &matViewSave );
    m_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
    m_pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE, TRUE);
*/

}



//-----------------------------------------------------------------------------
// Name:  DrawDebugOverlay()
// Desc:  draws the debug overlay
//-----------------------------------------------------------------------------
void CRenderer::DrawDebugOverlay()
{
	int iLogSlotOnscreen = -1;
    SIZE kFontSize;      // font properties

    unsigned int uiMaxRowsOnScreen;
    unsigned int uiMaxColsOnScreen;

    // starting onscreen offset is top left
    unsigned int uiStartXPos = 0;//1*m_d3dpp.BackBufferWidth / 4;
    
    // get font dimensions so we know how far to space each line
    m_kFontMap[FONT_SMALL]->GetTextExtent(_T("A"), &kFontSize );
	iLogSlotOnscreen = 0;//m_d3dpp.BackBufferHeight-(kFontSize.cy);//*3/4;   // current Y coordinate in console

    // calculate how many lines we can actually display
    uiMaxRowsOnScreen = m_d3dpp.BackBufferHeight/kFontSize.cy;
    uiMaxColsOnScreen = m_d3dpp.BackBufferWidth/(kFontSize.cx*25); //average # of chars is about 25 chars per entry


    // go through each slot in the debug overlay and render text
	unsigned int i = 1;
    unsigned int uiNumNewlines = 1;
    const char * szBuf;

    for (unsigned int iSlot=0; iSlot<uiMaxRowsOnScreen*uiMaxColsOnScreen; iSlot++)  {
        iLogSlotOnscreen += kFontSize.cy*uiNumNewlines;      // font spacing

        if (CLog::GetLog().m_kDebugOverLay[iSlot] != "")  {
            szBuf = CLog::GetLog().m_kDebugOverLay[iSlot].c_str();        
            uiNumNewlines = 0;
            //find # of newline chars to adjust font spacing
            int iStrIndex=0;
            do {
                 uiNumNewlines++;  
                 iStrIndex = CLog::GetLog().m_kDebugOverLay[iSlot].find("\n", iStrIndex);
                 if (iStrIndex == -1) break;
                 else iStrIndex++;
            }  while (iStrIndex < signed(CLog::GetLog().m_kDebugOverLay[iSlot].length()));

            m_kFontMap[FONT_SMALL]->DrawText( (float)uiStartXPos, (float)iLogSlotOnscreen, D3DCOLOR_ARGB(255,255,150,20),
                                              szBuf, D3DFONT_FILTERED);
        }
        if (i>uiMaxRowsOnScreen)  {  // can't fit anymore lines in this column
            uiStartXPos += (1*m_d3dpp.BackBufferWidth / 3);  //move to the next column only 3 supported
            iLogSlotOnscreen = 0;
            i = 0;
            if ( uiStartXPos > m_d3dpp.BackBufferWidth)
                break;  //no more room for the next column
        }
        else 
            i += uiNumNewlines;
    }
}





//-----------------------------------------------------------------------------
// Name:  DrawEntity()
// Desc:  generic draw funciton for an entity
//-----------------------------------------------------------------------------
void CRenderer::DrawEntity( CEntity * pEntity )  {

    ID3DXMatrixStack* pMatrixStack;
    D3DXCreateMatrixStack( 0, &pMatrixStack);
    Vector3f * vTemp;
    HRESULT hr;

   	pMatrixStack->Push(); 
    pMatrixStack->LoadIdentity();

	//--- orientation ---//
	vTemp = pEntity->GetRotate();

//	pMatrixStack->RotateAxis(&D3DXVECTOR3(1.0f, 0.0f, 0.0f), RADIANS(vTemp->X()));
//	pMatrixStack->RotateAxis(&D3DXVECTOR3(0.0f, 1.0f, 0.0f), RADIANS(vTemp->Y()));
//    pMatrixStack->RotateAxis(&D3DXVECTOR3(0.0f, 0.0f, 1.0f), RADIANS(vTemp->Z()));

	//pMatrixStack->RotateYawPitchRoll(vTemp->X(), vTemp->Y(), vTemp->Z());	

        
    /* 1) alternate rotation method
    D3DXMATRIX temp;
    D3DXMatrixRotationZ( &temp, RADIANS(vTemp->Z()) );
    pMatrixStack->MultMatrix( &temp );
    D3DXMatrixRotationY( &temp, RADIANS(vTemp->Y()) );
    pMatrixStack->MultMatrix( &temp );
    D3DXMatrixRotationX( &temp, RADIANS(vTemp->X()) );
    pMatrixStack->MultMatrix( &temp );
    */

    //$$$TEMP Chris, this is what I was saying about local axes and world axes
    // somewhere along the line rotns are being performed on the local axes in car space
    // but this this totally different from the world coordinate system
    // the only fix to this is RotateAxisLocal which performs the rotation about the cars origin
    // uncomment lines marked WORKING to try the different methods

    // 2) rotation method part deux
    ////pMatrixStack->RotateAxis(&D3DXVECTOR3(0.0f, 0.0f, 1.0f), RADIANS(vTemp->Z()));
    pMatrixStack->RotateAxisLocal(&D3DXVECTOR3(0.0f, 0.0f, 1.0f), RADIANS(vTemp->Z()));  //// 1 WORKING    
    pMatrixStack->RotateAxis(&D3DXVECTOR3(0.0f, 1.0f, 0.0f), RADIANS(vTemp->Y()));       //// 1 WORKING
    ////pMatrixStack->RotateAxisLocal(&D3DXVECTOR3(0.0f, 1.0f, 0.0f), RADIANS(vTemp->Y())); ///FUKD for some reason
    ////pMatrixStack->RotateAxis(&D3DXVECTOR3(1.0f, 0.0f, 0.0f), RADIANS(vTemp->X()));
    pMatrixStack->RotateAxisLocal(&D3DXVECTOR3(1.0f, 0.0f, 0.0f), RADIANS(vTemp->X()));  //// 1 WORKING

    // 3) yet another rotation method
    //pMatrixStack->RotateYawPitchRoll(RADIANS(vTemp->X()), RADIANS(vTemp->Y()), RADIANS(vTemp->Z()));
    
    //$$$NOTE this also works too, but note the rotations I'm using here in each parameter...
    //pMatrixStack->RotateYawPitchRollLocal(RADIANS(vTemp->Y()), RADIANS(vTemp->X()), RADIANS(vTemp->Z())); /// 2 ALSO WORKING


    
    //--- translation ---//
	vTemp = pEntity->GetTranslate();		
	pMatrixStack->Translate(vTemp->X(), vTemp->Y(), vTemp->Z());
    //pMatrixStack->TranslateLocal(vTemp->X(), vTemp->Y(), vTemp->Z());

	//--- scale ---//
	vTemp = pEntity->GetScale();
	pMatrixStack->Scale(vTemp->X(), vTemp->Y(), vTemp->Z());
    //pMatrixStack->ScaleLocal(vTemp->X(), vTemp->Y(), vTemp->Z());


	m_pd3dDevice->SetTransform( D3DTS_WORLD, pMatrixStack->GetTop() ); // set the transformation of the D3D device

    //actual drawing of the mesh
    if ( FAILED(hr =  pEntity->GetMesh()->Render(m_pd3dDevice, true, true)) )  {
		#ifdef _DEBUG
		CLog::GetLog().Write(LOG_GAMECONSOLE, IDS_RENDER_ERROR, "Mesh Drawing Failed");
        CLog::GetLog().Write(LOG_GAMECONSOLE, "Could not draw: %s", pEntity->GetMesh()->m_strName);
		#endif
	}
	else {
		#ifdef _DEBUG
		//CLog::GetLog().Write(LOG_GAMECONSOLE, "Drawing a mesh %s", pEntity->GetMesh()->m_strName);
		#endif
    }

    pMatrixStack->Pop();
    m_pd3dDevice->SetTransform( D3DTS_WORLD, pMatrixStack->GetTop() ); // restore the world matrix

    pMatrixStack->Release();

    if (m_bDrawEntBBoxes == true)  {
        DrawBBox(pEntity->GetBoundingBox(), 10.0f, D3DCOLOR_ARGB(255, 220, 50, 50));
    }

}





void CRenderer::DrawBBox(Box3f * pBBox, float fPointSize, DWORD dwColor)
{
    // load debug renderstates
    m_pSBMap[RENSB_DEBUGSTATE]->Apply();

    LPDIRECT3DVERTEXBUFFER9 theBuffer;

    if( FAILED( m_pd3dDevice->CreateVertexBuffer( 24*sizeof(D3DVertex), 0, D3DFVF_D3DVertex, D3DPOOL_DEFAULT, &theBuffer, NULL) ) )
    {
        return;
    }

    D3DVertex myBox[24];  // 8 points + 4 points to complete the line list

    Vector3f vBBox[8];
    //pEntity->GetBoundingBox()->ComputeVertices(vBBox);
    pBBox->ComputeVertices(vBBox);

    // copy the vertices of the bounding box for rendering
    // top edges
    int j;
    for(j=0; j<8; j++)  {
        myBox[j].x = vBBox[j].X();
        myBox[j].y = vBBox[j].Y();
        myBox[j].z = vBBox[j].Z();
        myBox[j].nx = 0.0f;
        myBox[j].ny = 1.0f;
        myBox[j].nz = 0.0f;

        //myBox[j].w = 1.0f;
        myBox[j].psize = fPointSize;
        myBox[j].color = dwColor;
    }

    //top edges
    myBox[8] = myBox[2];
    myBox[9] = myBox[6];
    myBox[10] = myBox[3];
    myBox[11] = myBox[7];

    // bottom edges
    myBox[12] = myBox[1];
    myBox[13] = myBox[5];
    myBox[14] = myBox[4];
    myBox[15] = myBox[0];

    // front side edges
    myBox[16] = myBox[7];
    myBox[17] = myBox[4];
    myBox[18] = myBox[6];
    myBox[19] = myBox[5];

    // back side edges
    myBox[20] = myBox[3];
    myBox[21] = myBox[0];
    myBox[22] = myBox[2];
    myBox[23] = myBox[1];


    // Copy box vertices into the buffer
    VOID* pVertices;
    if( FAILED( theBuffer->Lock( 0, sizeof(myBox), (void**)&pVertices, 0 ) ) )
        return;// E_FAIL;
    memcpy( pVertices, myBox, sizeof(myBox) );
    theBuffer->Unlock();


    // Draw the vertex buffer
    m_pd3dDevice->SetStreamSource( 0, theBuffer, 0,  sizeof(D3DVertex) );
    m_pd3dDevice->SetFVF( D3DFVF_D3DVertex );

    m_pd3dDevice->DrawPrimitive( D3DPT_POINTLIST, 0, 8 );
    m_pd3dDevice->DrawPrimitive( D3DPT_LINELIST, 0, 12 );

    // Destroy the vertex buffer
    theBuffer->Release();

    m_pDefaultSB->Apply();  // restore default states

}



void CRenderer::DrawRect( Rectangle3f * pRect, float fPointSize, DWORD dwColor)
{
    // load debug renderstates
    m_pSBMap[RENSB_DEBUGSTATE]->Apply();

    LPDIRECT3DVERTEXBUFFER9 theBuffer;

    if( FAILED( m_pd3dDevice->CreateVertexBuffer( 5*sizeof(D3DVertex), 0, D3DFVF_D3DVertex, D3DPOOL_DEFAULT, &theBuffer, NULL) ) )
    {
        return;
    }

    D3DVertex myRect[5];  // 5 points to complete the line strip list
    Vector3f vecOrigin = pRect->Origin(), vecPt;
    //vecPt = vecOrigin + pRect->Edge0()/2.0f + pRect->Edge1()/2.0f;
	vecPt = vecOrigin;
    myRect[0].x = vecPt.X();
    myRect[0].y = vecPt.Y();
    myRect[0].z = vecPt.Z();  // top corner ++
    myRect[0].psize = fPointSize;
    myRect[0].color = dwColor;

    //vecPt = vecOrigin + pRect->Edge0()/2.0f - pRect->Edge1()/2.0f;
	vecPt = vecOrigin + pRect->Edge0();
    myRect[1].x = vecPt.X();
    myRect[1].y = vecPt.Y();
    myRect[1].z = vecPt.Z();  
    myRect[1].psize = fPointSize;
    myRect[1].color = dwColor; // +-

    //vecPt = vecOrigin - pRect->Edge0()/2.0f - pRect->Edge1()/2.0f;
	vecPt = vecOrigin + pRect->Edge0() + pRect->Edge1();
    myRect[2].x = vecPt.X();
    myRect[2].y = vecPt.Y();
    myRect[2].z = vecPt.Z();  
    myRect[2].psize = fPointSize;
    myRect[2].color = dwColor;

    //vecPt = vecOrigin - pRect->Edge0()/2.0f + pRect->Edge1()/2.0f;
	vecPt = vecOrigin + pRect->Edge1();
    myRect[3].x = vecPt.X();
    myRect[3].y = vecPt.Y();
    myRect[3].z = vecPt.Z();  
    myRect[3].psize = fPointSize;
    myRect[3].color = dwColor;

    // to close the rectangle
    myRect[4] = myRect[0];

    // Copy rect vertices into the buffer
    VOID* pVertices;
    if( FAILED( theBuffer->Lock( 0, sizeof(myRect), (void**)&pVertices, 0 ) ) )
        return;// E_FAIL;
    memcpy( pVertices, myRect, sizeof(myRect) );
    theBuffer->Unlock();

    // Draw the vertex buffer
    m_pd3dDevice->SetStreamSource( 0, theBuffer, 0,  sizeof(D3DVertex) );
    //m_pd3dDevice->SetFVF( D3DFVF_D3DVertex );

    m_pd3dDevice->DrawPrimitive( D3DPT_POINTLIST, 0, 4 );
    //m_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 4 );
    m_pd3dDevice->DrawPrimitive( D3DPT_LINESTRIP, 0, 4 );
    
    // Destroy the vertex buffer
    theBuffer->Release();

    m_pDefaultSB->Apply();  // restore default states
}


void CRenderer::DrawWayPoint( CWaypoint * pWayPt, float fPointSize, DWORD dwColor)
{
    // load debug renderstates
    m_pSBMap[RENSB_DEBUGSTATE]->Apply();

    LPDIRECT3DVERTEXBUFFER9 theBuffer;

    if( FAILED( m_pd3dDevice->CreateVertexBuffer( 5*sizeof(D3DVertex), 0, D3DFVF_D3DVertex, D3DPOOL_DEFAULT, &theBuffer, NULL) ) )
    {
        return;
    }

    D3DVertex myWayPt[5];  // 5 points to show a waypoint
    Vector3f vecOrigin = *pWayPt->GetTranslate(), vecPt;


	vecPt = vecOrigin + pWayPt->Radius()*Vector3f(1,0,0);
    myWayPt[0].x = vecPt.X();
    myWayPt[0].y = vecPt.Y();
    myWayPt[0].z = vecPt.Z();  
    myWayPt[0].psize = fPointSize;
    myWayPt[0].color = dwColor - D3DCOLOR_ARGB( 0, 55, 55, 55 );


	vecPt = vecOrigin - pWayPt->Radius()*Vector3f(1,0,0);
    myWayPt[1].x = vecPt.X();
    myWayPt[1].y = vecPt.Y();
    myWayPt[1].z = vecPt.Z();  
    myWayPt[1].psize = fPointSize;
    myWayPt[1].color = dwColor - D3DCOLOR_ARGB( 0, 55, 55, 55 );


  	vecPt = vecOrigin;
    myWayPt[2].x = vecPt.X();
    myWayPt[2].y = vecPt.Y();
    myWayPt[2].z = vecPt.Z(); 
    myWayPt[2].psize = fPointSize;
    myWayPt[2].color = dwColor;
    
    
    vecPt = vecOrigin + pWayPt->Radius()*Vector3f(0,0,1);
    myWayPt[3].x = vecPt.X();
    myWayPt[3].y = vecPt.Y();
    myWayPt[3].z = vecPt.Z();  
    myWayPt[3].psize = fPointSize;
    myWayPt[3].color = dwColor - D3DCOLOR_ARGB( 0, 55, 55, 55 );

    
	vecPt = vecOrigin - pWayPt->Radius()*Vector3f(0,0,1);
    myWayPt[4].x = vecPt.X();
    myWayPt[4].y = vecPt.Y();
    myWayPt[4].z = vecPt.Z();  
    myWayPt[4].psize = fPointSize;
    myWayPt[4].color = dwColor - D3DCOLOR_ARGB( 0, 55, 55, 55 );




    // Copy rect vertices into the buffer
    VOID* pVertices;
    if( FAILED( theBuffer->Lock( 0, sizeof(myWayPt), (void**)&pVertices, 0 ) ) )
        return;// E_FAIL;
    memcpy( pVertices, myWayPt, sizeof(myWayPt) );
    theBuffer->Unlock();

    // Draw the vertex buffer
    m_pd3dDevice->SetStreamSource( 0, theBuffer, 0,  sizeof(D3DVertex) );
    //m_pd3dDevice->SetFVF( D3DFVF_D3DVertex );

    m_pd3dDevice->DrawPrimitive( D3DPT_POINTLIST, 0, 5 );
    //m_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 4 );
    m_pd3dDevice->DrawPrimitive( D3DPT_LINESTRIP, 0, 4 );
    
    // Destroy the vertex buffer
    theBuffer->Release();

    m_pDefaultSB->Apply();  // restore default states
}


#ifdef _DEBUG
extern int iDrawnEnt, iTotalNodeEnt;
#endif

//-----------------------------------------------------------------------------
// Name:  DrawQuadTreeNode()
// Desc:  recursively draws all entities within a quad tree node
//-----------------------------------------------------------------------------
void CRenderer::DrawQuadTreeNode( CQuadNode * pQNode )
{
    // draw its entities if any
    map<int, CEntity *>::iterator it;
    for (it=pQNode->m_EntMap.begin(); it!=pQNode->m_EntMap.end(); it++) {
        if (!m_kDrawnEntIDs[it->second->GetId()])  {
            DrawEntity(it->second);
            m_kDrawnEntIDs[it->second->GetId()] = true;
            #ifdef _DEBUG
            iDrawnEnt++;
            #endif
        }
        else {
            #ifdef _DEBUG
            //CLog::GetLog().Write(LOG_GAMECONSOLE, "Entity %d %s, is already drawn", it->second->GetId(), it->second->GetName());
            #endif
        }
        #ifdef _DEBUG
        iTotalNodeEnt++;       
        #endif
    }

    #ifdef _DEBUG
    CLog::GetLog().Write(LOG_DEBUGOVERLAY, 18, "Drew %d of %d entities in nodes", iDrawnEnt, iTotalNodeEnt);
    #endif

    if (m_bDrawQNodeBBoxes == true)  {//  && !pQNode->m_EntMap.empty())
        DrawBBox(&pQNode->m_BBox, 1.0f, D3DCOLOR_ARGB(150, 50, 200, 50));
    }

/*    
    //$$$TEMP THE FOLLOWING DRAWS CHILD NODES EVEN IF EMPTY
    // recursively draw the visible child nodes
    if (!pQNode->m_pChildNode[NE])  {
        return; // no children to draw
    }
    else {
        DrawQuadTreeNode(pQNode->m_pChildNode[NE]);
    }

    if (!pQNode->m_pChildNode[NW])  {
        return; // no children to draw
    }
    else {
        DrawQuadTreeNode(pQNode->m_pChildNode[NW]);
    }

    if (!pQNode->m_pChildNode[SE])  {
        return; // no children to draw
    }
    else {
        DrawQuadTreeNode(pQNode->m_pChildNode[SE]);
    }

    if (!pQNode->m_pChildNode[SW])  {
        return; // no children to draw
    }
    else {
        DrawQuadTreeNode(pQNode->m_pChildNode[SW]);
    }
*/
    return;
}




//-----------------------------------------------------------------------------
// Name:  DrawVehicle()
// Desc:  Draw a vehicle with effects if any
//-----------------------------------------------------------------------------
void CRenderer::DrawVehicle( CVehicle * pVehicle )
{
    //m_pd3dDevice->SetRenderState( D3DRS_LIGHTING, TRUE );

    // draw body
    DrawEntity( pVehicle );

    // draw tires
    for (int i=0; i<4; i++)
        DrawEntity( pVehicle->GetTire(i) );

    //$$$TODO draw shadow

    //$$$TODO draw exhaust
    // get position of exhaust in local coords

    //$$$TODO draw headlights
    // get position of headlights in local coords
}



//-----------------------------------------------------------------------------
// Name:  DrawScreenText()
// Desc:  Draw text using screen coordinates without any effects using font size
// Defaults: dwFlags = 0, eFType = FONT_MENU
//-----------------------------------------------------------------------------
void CRenderer::DrawScreenText(  FLOAT fXPos, FLOAT fYPos, DWORD dwColor, char * szText, DWORD dwFlags, FontType eFType )
{
    m_kFontMap[eFType]->DrawText( fXPos, fYPos, dwColor, szText, dwFlags);
    return;
}



//-----------------------------------------------------------------------------
// Name:  Draw3DTextScaled()
// Desc:  Draw a scaled text relative to screen size in world coordinates
// Defaults: dwFlags = 0, eFType = FONT_MENU
//-----------------------------------------------------------------------------
void CRenderer::Draw3DTextScaled( FLOAT fXPos, FLOAT fYPos, FLOAT fZPos, DWORD dwColor, char * szText, FLOAT fXScale, FLOAT fYScale, DWORD dwFlags, FontType eFType )
{
    m_kFontMap[eFType]->DrawTextScaled(fXPos, fYPos, fZPos, fXScale, fYScale, dwColor, szText, dwFlags);
    return;
}

void CRenderer::DrawFrontEnd()
{    
    DrawScreen(CFrontendManager::GetFrontendManagerPtr()->CurScreen());
}

void CRenderer::DrawScreen(CScreen * pScreen)
{
    pScreen->draw();
}




//-----------------------------------------------------------------------------
// Name:  DrawHUD()
// Desc:  draw heads up display for in game
//-----------------------------------------------------------------------------
bool CRenderer::DrawHUD()  
{
    //$$$TEMP STILL HAVE TO OPTIMIZE VERTEX BUFFERING!!!!
    LPDIRECT3DVERTEXBUFFER9 Vertex_Buffer = NULL;   // Vertex buffer for hold our main object.

    // apply HUD render states
    m_pSBMap[RENSB_HUD]->Apply();

    //D3DXMATRIX matOrth;
    //D3DXMatrixOrthoLH(&matOrth, 2, 2, 0, 1 );
    //
    //D3DXMatrixOrthoLH(&matOrth, (float)((float)m_iWidth/(float)m_iHeight)*2.0f, (float)((float)m_iHeight/(float)m_iWidth)*2.0f, 0, 1 );

    //m_pd3dDevice->SetTransform( D3DTS_VIEW, &matOrth );
    //m_pd3dDevice->SetTransform( D3DTS_PROJECTION, &matOrth );


    // Square data for its position and texture coords.
/*	D3DTexMappedVertex Polygon_Data[4] = {
		{-0.5f, 0.5f, 0.0f, 0.0, 0.0},
      {0.5f, 0.5f, 0.0f, 1.0, 0.0},
	   {-0.5f, -0.5f, 0.0f, 0.0, 1.0},
      {0.5f, -0.5f, 0.0f, 1.0, 1.0}
	};
*/

  	D3DTexMappedVertex Polygon_Data[4] = {
		{0.7f, -0.4f, 0.5f, D3DCOLOR_ARGB( 100, 255, 255, 255 ), 0.0, 0.0},  // BL -+
        {1.3f, -0.4f, 0.5f, D3DCOLOR_ARGB( 100, 255, 255, 255 ), 1.0, 0.0},   // TR ++
	    {0.7f, -1.0f, 0.5f, D3DCOLOR_ARGB( 100, 255, 255, 255 ), 0.0, 1.0}, // TL --
        {1.3f, -1.0f, 0.5f, D3DCOLOR_ARGB( 100, 255, 255, 255 ), 1.0, 1.0}   // BR +-
	};

    // Create the vertex buffer that will hold the square.
    if(FAILED(m_pd3dDevice->CreateVertexBuffer(4*sizeof(D3DTexMappedVertex),
                                            0, D3DFVF_D3DTMVertex,
                                            D3DPOOL_DEFAULT, &Vertex_Buffer, NULL)))
    {
     return false;  // Exit this function if there is some kind of problem.
    }
	
    // Pointer to the buffer.
    VOID* Vertices;

    // Lock the buffer we can write to it.
    if(FAILED(Vertex_Buffer->Lock(0, sizeof(Polygon_Data), (void**)&Vertices, 0)))
      return false;

    // Here we copy the square's data into the vertex buffer.
    memcpy(Vertices, Polygon_Data, sizeof(Polygon_Data));

    // Unlock when your done copying data into the buffer.
    Vertex_Buffer->Unlock();


    // This will bind the vertex data in the buffer to the Direct3D device.
    m_pd3dDevice->SetStreamSource(0, Vertex_Buffer, 0, sizeof(D3DTexMappedVertex));

    // Set the vertex stream declaration.
    //m_pd3dDevice->SetFVF(D3DFVF_D3DTMVertex);

    // SetTexture will add the image in the Texture object to all things draw after this.
    m_pd3dDevice->SetTexture(0, m_pTextureMap["rpm_gauge.bmp"]);

    // This will draw everything in the buffer (the square we created in InitializeObject().
    m_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

    // SetTexture will add the image in the Texture object to all things draw after this.
    m_pd3dDevice->SetTexture(0, m_pTextureMap["mpg_gear.bmp"]);

    // This will draw everything in the buffer (the square we created in InitializeObject().
    m_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);



    SAFE_RELEASE(Vertex_Buffer);

    // restore default states
    m_pDefaultSB->Apply();  
    
    return true;
}
