#include "entity.h"
#include "renderer.h"
#include "gamestatemanager.h"


// load a mesh and intitialize it using the renderer
// stored in the meshes vector of the scene
int CEntity::LoadMesh()
{
    assert(CRenderer::GetRendererPtr());
    
    string strPath;/* = ".\\media\\meshes";
    strPath.append("\\dynamic\\vehicles\\");  ///$$$TEMP  only wnat a car now
    strPath.append(m_strName);
    strPath.append("\\");
    strPath += m_strName;  //should be taken from GS manager
    strPath.append(".x");*/

    strPath += m_strName;
    strPath.append(".x");

    char szPath[256];
    sprintf(szPath,"%s", strPath.c_str());

    m_pMesh = new CD3DMesh(_T(szPath));

    if (!CRenderer::GetRenderer().CreateMesh( m_pMesh, szPath ))
        return 0;  // Failure

    return 1;  // Success
}