/*****************************************************************************
*
* File:  quadtree.h
*
* BurnOut Studios - Super Street Racer
* Module:  AI
* Author:  Jay Javier
* Modified by:  On: 
* Date Created:  March 2004
*
******************************************************************************
* Desc:  
*****************************************************************************/
#ifndef QUADTREE_H
#define QUADTREE_H

#define STL_USING_VECTOR
#define STL_USING_MAP
#include "stl.h"

#include "wmlvector3.h"
#include "wmlbox3.h"
#include "wmlsphere3.h"
using namespace Wml;

#include "entity.h"

enum { SW=0, SE, NW, NE };

//-----------------------------------------------------------------------------
// Name: enum CULLSTATE
// Desc: Represents the result of the culling calculation on an object.
//-----------------------------------------------------------------------------
enum CULLSTATE
{
    CS_UNKNOWN,      // cull state not yet computed
    CS_INSIDE,       // object bounding box is at least partly inside the frustum
    CS_OUTSIDE,      // object bounding box is outside the frustum
//    CS_INSIDE_SLOW,  // OBB is inside frustum, but it took extensive testing to determine this
//    CS_OUTSIDE_SLOW, // OBB is outside frustum, but it took extensive testing to determine this
};


//-----------------------------------------------------------------------------
// Name: class CQuadNode 
// Desc: a node in the quadtree
//-----------------------------------------------------------------------------
class CQuadNode
{
public:
	Vector3f	m_vOrigin;
	float		m_fHalfWidth;
	CQuadNode * m_pChildNode[4];

    // map of entities within this quad indexed by ID
    std::map <int , CEntity *> m_EntMap; 

    Box3f m_BBox;        // bounding box for this node
    Sphere3f m_BSphere;  // bounding sphere
    
    CQuadNode(Vector3f vOrigin, float fHalfWidth);

    
};


class CD3DCamera;  // forward declaration

//-----------------------------------------------------------------------------
// Name: class CQuadTree  
// Desc: a tree structure to allow fast spatial lookup of game objects
// manages all pointers to nodes in a vector
//-----------------------------------------------------------------------------
class CQuadTree
{
public:
	CQuadTree( float fNodeWidth );
    CQuadTree();
    ~CQuadTree();

    void Update(){};  //update the quadtree to account for movement of dynamic entities

	void Add( CEntity * pEntity );
	void Render( void );
    void ClearQuadTree();
    
    int GetNumLevels(){ return m_iLevels;};
    int GetNumNodes(){ return m_vpNodes.size();};

    void Initialize( std::vector <CEntity *> * pvEntities = NULL);  // use loaded scene info to create this quadtree
    bool IsInitialized(){ return m_bIsInitialized; };
    vector <CQuadNode *> * GetVisibleNodesPtr(){ return &m_vpVisibleNodes; };

    void CullVisibility(CD3DCamera * pCamera, CQuadNode* pNode = m_pkQRoot, bool bTestChildren = true);
    CQuadNode * GetRootNodePtr(){ return m_pkQRoot; };

private:
	void SubDivide( CQuadNode * pQNode, int iLevel );
	void AddReference( Vector3f vOrigin, CEntity * pEntity);
    void AddReference( Box3f box, CEntity * pEntity,  CQuadNode * node );
	static CQuadNode	* m_pkQRoot;
	int			m_iTraversalCount;
    float       m_fNodeWidth;
    int         m_iLevels;
    bool        m_bIsInitialized;

    // scene stats used to construct the quadtree properly
    Vector3f m_vfMaxExtent;  // max xyz of all entities
    Vector3f m_vfMinExtent;  // min xyz of all entities
    Vector3f m_vfMapOrigin;  // 'center' point of quadtree


    std::vector <CQuadNode *> m_vpNodes;         // a vector to manage node pointers
    std::vector <CQuadNode *> m_vpVisibleNodes;  // all visible nodes in the scene

};

#endif
//end quadtree.h =============================================================