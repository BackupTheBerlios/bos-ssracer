#include "entity.h"
#include "renderer.h"
#include "gamestatemanager.h"
#include "settings.h"


// load a mesh and intitialize it using the renderer
// stored in the meshes vector of the scene
int CEntity::LoadMesh()
{
    assert(CRenderer::GetRendererPtr());
    
    string strPath = CSettingsManager::GetSettingsManager().GetGameSetting(DIRDYNVEHICLES);
    strPath += m_strName;  // meshes are in their own directory
    strPath += "\\";
    strPath += m_strName;
    strPath.append(".x\0");  // DONT FORGET TO ADD THE NULL CHAR TO THE END, 
                             // OTHERWISE THE C_STR IS FACKED FOR SOME GAY REASON

    char szPath[512];
    sprintf(szPath,"%s", strPath.c_str());

    m_pMesh = new CD3DMesh(_T(m_strName));

    if (!CRenderer::GetRenderer().CreateMesh( m_pMesh, szPath ))
        return 0;  // Failure

    return 1;  // Success
}