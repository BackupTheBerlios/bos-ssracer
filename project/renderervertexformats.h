/*****************************************************************************
*
* File:  renderervertexformats.h
*
* BurnOut Studios - Super Street Racer
* Module:  Renderer
* Author:  Jay Javier
* Modified by:  On: 
* Date Created:  April, 2004
*
******************************************************************************
* Desc:  
*****************************************************************************/


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