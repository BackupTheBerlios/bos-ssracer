#include "entity.h"
#include "renderer.h"
#include "gamestatemanager.h"


// load a mesh and intitialize it using the renderer
// stored in the meshes vector of the scene
int CEntity::LoadMesh()
{
    char szBuf[256];
    sprintf(szBuf, "%s%s", m_strName, ".x");

    assert(CRenderer::GetRendererPtr());
    
    if (!CRenderer::GetRenderer().CreateMesh(m_strName ,m_pMesh))
        return 0;  // Failure

    return 1;  // Success
}