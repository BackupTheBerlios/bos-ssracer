#include "entity.h"
#include "renderer.h"
#include "gamestatemanager.h"
#include "settings.h"

CEntity::CEntity()
{
    strcpy(m_strName, "DefaultName");
    m_id = rand()%30000 + 10000; // generate a random ID in case this isn't set explicitly
	m_rotate = Vector3f(0.0f, 0.0f, 0.0f);
	m_translate = Vector3f(0.0f, 0.0f, 0.0f);
	m_scale = Vector3f(1.0f, 1.0f, 1.0f);
    m_bIsDynamic = false;
}
// load a mesh and intitialize it using the renderer
// stored in the meshes vector of the scene
int CEntity::LoadMesh()
{
    assert(0);  //SHOULD NEVER BE CALLED

    /*********** THIS CODE IS KIND OF FUCKED ***************/

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


// load a mesh in a certain directory
int CEntity::LoadMesh( string strDir )
{
    assert(CRenderer::GetRendererPtr());
    
    string strPath = strDir;
    strPath += m_strName;
    strPath.append(".x\0");

    char szPath[512];
    sprintf(szPath,"%s", strPath.c_str());

    // check if this mesh is already loaded in the meshmap
    if (CGameStateManager::GetGameStateManager().GetScenePtr()->IsMeshLoaded( string(m_strName) )) {
        CLog::GetLog().Write(LOG_MISC, "WARNING CEntity::LoadMesh: Mesh %s is already loaded in the mesh map", m_strName);
        // set the mesh to the loaded one
        m_pMesh = CGameStateManager::GetGameStateManager().GetScenePtr()->GetMeshPtrFromMap(string(m_strName));
        return 1;
    }

    // mesh isn't loaded yet so create a new one
    m_pMesh = new CD3DMesh(_T(m_strName));

    // use the current working directory trick to make DX load the textures from the same dir
    if (!SetCurrentDirectory(strDir.c_str()))
        return 0;
    if (!CRenderer::GetRenderer().CreateMesh( m_pMesh, szPath ))  {
        // set the CWD back
        if (!SetCurrentDirectory(CSettingsManager::GetSettingsManager().GetGameSetting(DIRCURRENTWORKING).c_str()))
            return 0;
        return 0;  // Failure
    }
    // set the CWD back
    if (!SetCurrentDirectory(CSettingsManager::GetSettingsManager().GetGameSetting(DIRCURRENTWORKING).c_str()))
        return 0;

    return 1;  // Success
}