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
using namespace Wml;

#include "entity.h"


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

    Box3f m_BBox;  //bounding box for this node
    
    CQuadNode(Vector3f vOrigin, float fHalfWidth) {
        m_vOrigin = vOrigin;
        m_fHalfWidth = fHalfWidth;
        for (int i=0; i<4; i++)  m_pChildNode[i] = NULL;
        m_EntMap.clear();
        m_BBox.Center() = vOrigin;
        m_BBox.Extent(0) = m_BBox.Extent(1) = m_BBox.Extent(2) = fHalfWidth;
        m_BBox.Axis(0) = Vector3f(1,0,0);  // axis aligned
        m_BBox.Axis(1) = Vector3f(0,1,0);
        m_BBox.Axis(2) = Vector3f(0,0,1);
    };

    
};



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

private:
	void SubDivide( CQuadNode * pQNode, int iLevel );
	void AddReference( Vector3f vOrigin, CEntity * pEntity);
	void CQuadTree::Render( CQuadNode * pQNode, int cullcode, int iLevel );
	CQuadNode	* m_pkQRoot;
	int			m_iTraversalCount;
    float       m_fNodeWidth;
    int         m_iLevels;
    bool        m_bIsInitialized;

    // scene stats used to construct the quadtree properly
    Vector3f m_vfMaxExtent;  // max xyz of all entities
    Vector3f m_vfMinExtent;  // min xyz of all entities
    Vector3f m_vfMapOrigin;  // 'center' point of quadtree


    std::vector <CQuadNode *> m_vpNodes;  // a vector to manage node pointers
};

#endif
//end quadtree.h =============================================================