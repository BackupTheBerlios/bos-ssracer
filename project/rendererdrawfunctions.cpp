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

    //m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
    //m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_SELECTARG1 );

    // set texture filters to reduce seams
    //m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_POINT );
    //m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_POINT );
    //m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_POINT );

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
    m_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
    m_pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE, TRUE);

    // restore the texture filters
    m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
    m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
    m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR );
    m_pd3dDevice->SetSamplerState( 0, D3DSAMP_ADDRESSU,  D3DTADDRESS_WRAP ); 
    m_pd3dDevice->SetSamplerState( 0, D3DSAMP_ADDRESSV,  D3DTADDRESS_WRAP ); 

    // turn lighting back on
    m_pd3dDevice->SetRenderState( D3DRS_LIGHTING, TRUE );

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

	// orientation
	vTemp = pEntity->GetRotate();
    pMatrixStack->RotateAxis(&D3DXVECTOR3(0.0f, 0.0f, 1.0f), RADIANS(vTemp->Z()));
	pMatrixStack->RotateAxis(&D3DXVECTOR3(0.0f, 1.0f, 0.0f), RADIANS(vTemp->Y()));
	pMatrixStack->RotateAxis(&D3DXVECTOR3(1.0f, 0.0f, 0.0f), RADIANS(vTemp->X()));
	//pMatrixStack->RotateYawPitchRoll(vTemp->X(), vTemp->Y(), vTemp->Z());	

    // translation
	vTemp = pEntity->GetTranslate();		
	pMatrixStack->Translate(vTemp->X(), vTemp->Y(), vTemp->Z());

    //pMatrixStack->TranslateLocal(vTemp->X(), vTemp->Y(), vTemp->Z());

	// scale
	vTemp = pEntity->GetScale();
	pMatrixStack->Scale(vTemp->X(), vTemp->Y(), vTemp->Z());
    //pMatrixStack->ScaleLocal(vTemp->X(), vTemp->Y(), vTemp->Z());


	m_pd3dDevice->SetTransform( D3DTS_WORLD, pMatrixStack->GetTop() );

    //actual drawing of the mesh
    if ( FAILED(hr =  pEntity->GetMesh()->Render(m_pd3dDevice, true, true)) )  {
    //if ( FAILED(hr =  m_kMeshMap[pEntity->GetMesh()->m_strName]->Render(m_pd3dDevice)) )  {
		#ifdef _DEBUG
		CLog::GetLog().Write(LOG_MISC|LOG_GAMECONSOLE, IDS_RENDER_ERROR, "Mesh Drawing Failed");
        CLog::GetLog().Write(LOG_MISC|LOG_GAMECONSOLE, "Could not draw: %s", pEntity->GetMesh()->m_strName);
		#endif
	}
	else {
		#ifdef _DEBUG
		//CLog::GetLog().Write(LOG_GAMECONSOLE, "Drawing a mesh %s", pEntity->GetMesh()->m_strName);
		#endif
    }

   	pMatrixStack->Pop();
    m_pd3dDevice->SetTransform( D3DTS_WORLD, pMatrixStack->GetTop() );

    if (m_bDrawEntBBoxes == true)
        DrawBBox(pEntity->GetBoundingBox(), 10.0f, D3DCOLOR_ARGB(255, 220, 50, 50));

}



struct D3DVertex
{
    FLOAT x, y, z;//, w;
    FLOAT nx,ny,nz;
    FLOAT psize;
    DWORD color;
};

//#define D3DFVF_D3DVertex (D3DFVF_XYZW|D3DFVF_PSIZE|D3DFVF_DIFFUSE)
#define D3DFVF_D3DVertex (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_PSIZE|D3DFVF_DIFFUSE)
//#define D3DFVF_D3DVertex (D3DFVF_XYZ|D3DFVF_DIFFUSE)

void CRenderer::DrawBBox(Box3f * pBBox, float fPointSize, DWORD dwColor)
{

    LPDIRECT3DVERTEXBUFFER9 theBuffer;
    //CreateVertexBuffer( 3*sizeof(CUSTOMVERTEX), 0 /* Usage */, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &g_pVB )

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

    // turn lighting off
    //m_pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );

    m_pd3dDevice->DrawPrimitive( D3DPT_POINTLIST, 0, 8 );
    m_pd3dDevice->DrawPrimitive( D3DPT_LINELIST, 0, 12 );
    //m_pd3dDevice->DrawPrimitiveUP( D3DPT_LINELIST, 12, pVertices, sizeof(D3DVertex));

    // turn lighting back on
    //m_pd3dDevice->SetRenderState( D3DRS_LIGHTING, TRUE );

    // Destroy the vertex buffer
    theBuffer->Release();

}


/*
	CObject * pkObject; 
	CScene * pkScene = CGame::GetGame().GetScenePtr();

    assert(pkScene);
    
    int iMaxNumObj = pkScene->GetNumObjects();
	char strFileName[1024];
	char strDirName[1024] = ".\\media\\meshes\\debug\\";
	char strFullPath[1024] = "";


    ///$$$TEMP QUICK CAR LOADING ---
    pkObject = pkScene->GetObject(0);

    CTire * cTires = ((CTire *)((CPlayerVehicle *)pkObject)->getTires());
    // load tires
    // car already in scene so we can just add the meshses to the mesh vector
    for (int k=0; k<4 && pkObject; k++)  {
        //memset(strFullPath, 0, sizeof(strFullPath));
	    //strcpy(strFileName, ((CPlayerVehicle *)pkObject)->m_tires[j].getName());
	    //sprintf(strFileName, "%s%s", strFileName, ".x");
	    
        //sprintf(strFullPath, "%s%s", strDirName, strFileName);  //something wrong with filename setting
        sprintf( strFullPath, "%s", ".\\media\\meshes\\debug\\Wheel.x" );

        //something wrong with naming
        char * temp = ((CTire *)((CPlayerVehicle *)pkObject)->getTires())->getName();
        
		FILE* fp = fopen(strFullPath, "r");

		if(fp) {
            // put it in the mesh map for creation
            if ( !m_kMeshMap[strFullPath] ) {
                m_kMeshMap[strFullPath] = new CD3DMesh( strFullPath );
            }            
            cTires[k].setMesh(m_kMeshMap[strFullPath]); 
            fclose(fp);
        }
        else {
            assert(fp);
        }
    }

    ///$$$TEMP END QUICK CAR LOADING ---


// GIB'S MODIFICATION (JAY SAYS "MOVE THIS HERE, BITCH!!!")

    // load the meshes into memory and set mesh pointers in game objects (entitites)
    for (int j=0; j<iMaxNumObj ; j++) {

		memset(strFullPath, 0, sizeof(strFullPath));
		pkObject = pkScene->GetObject(j);

		// get mesh filename
		strcpy(strFileName, pkObject->getName());
		sprintf(strFileName, "%s%s", strFileName, ".x");
		sprintf(strFullPath, "%s%s", strDirName, strFileName);

		FILE* fp = fopen(strFullPath, "r");

		if(fp) {

            // only load up one instance of this mesh
            if ( !m_kMeshMap[strFullPath] ) {
			    m_kMeshMap[strFullPath] = new CD3DMesh( strFullPath );
			    assert(m_kMeshMap[strFullPath]);
            }

            pkObject->setMesh(m_kMeshMap[strFullPath]);
			fclose(fp);
		}
		else {
            assert(fp);// Model doesn't exist.
		}
*/


extern int iDrawnEnt, iTotalNodeEnt;

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
            iDrawnEnt++;
        }
        else {
            #ifdef _DEBUG
            //CLog::GetLog().Write(LOG_GAMECONSOLE, "Entity %d %s, is already drawn", it->second->GetId(), it->second->GetName());
            #endif
        }
        iTotalNodeEnt++;       
    }

    #ifdef _DEBUG
    CLog::GetLog().Write(LOG_DEBUGOVERLAY, 18, "Drew %d of %d entities in nodes", iDrawnEnt, iTotalNodeEnt);
    #endif

    if (m_bDrawQNodeBBoxes == true)//  && !pQNode->m_EntMap.empty())
        DrawBBox(&pQNode->m_BBox, 1.0f, D3DCOLOR_ARGB(150, 50, 200, 50));

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