/*****************************************************************************
*
* File:  quadtree.cpp
*
* BurnOut Studios - Super Street Racer
* Module:  AI
* Author:  Jay Javier
* Modified by:  On: 
* Date Created:  
*
******************************************************************************
* Desc:  
*****************************************************************************/

#include "bos.h"
#include "log.h"
#include "quadtree.h"

//#include "macros.h"

#define QUADTREE_LEVELS 4

enum { SW=0, SE, NW, NE };

CQuadTree::CQuadTree() {
    m_pkQRoot = NULL;
    m_vpNodes.clear();
    m_iLevels = QUADTREE_LEVELS;
}

CQuadTree::CQuadTree( float fNodeWidth ) 
{
    CQuadTree();
    m_fNodeWidth = fNodeWidth;
    m_iLevels = QUADTREE_LEVELS;  // min # of levels
   	
    // Construct a quadtree of TREE_LEVELS levels deep
	//traversal_count = 0;
	m_pkQRoot = new CQuadNode( Vector3f(fNodeWidth/2.0f, fNodeWidth/2.0f, 0), fNodeWidth/2.0f );
    
    // save the root node for deletion later
    m_vpNodes.push_back(m_pkQRoot);

    // compute the initial sub levels of the tree
	SubDivide(m_pkQRoot, m_iLevels);
}


CQuadTree::~CQuadTree() 
{
    // delete all quadtree pointers 
    for (vector <CQuadNode *>::iterator it = m_vpNodes.begin(); it!=m_vpNodes.end(); it++)
        delete (*it);
    m_vpNodes.clear();
}

void CQuadTree::Initialize( std::vector <CEntity *> * pvEntities )
{
/*    m_fNodeWidth = fNodeWidth;
    m_iLevels = QUADTREE_LEVELS;  // min # of levels
   	
    // Construct a quadtree of TREE_LEVELS levels deep
	//traversal_count = 0;
	m_pkQRoot = new CQuadNode( Vector3f(fNodeWidth/2.0f, fNodeWidth/2.0f, 0), fNodeWidth/2.0f );
    
    // save the root node for deletion later
    m_vpNodes.push_back(m_pkQRoot);

    // compute the initial sub levels of the tree
	SubDivide(m_pkQRoot, m_iLevels);
*/

    // find min/max extents of the quadtree
    vector <CEntity *>::iterator it = pvEntities->begin();
    m_vfMaxExtent = m_vfMinExtent = *(*it)->GetTranslate();
    m_vfMapOrigin = Vector3f(0,0,0);

    for (it = pvEntities->begin(); it!=pvEntities->end(); it++)  {
        
        // look for max extent
        //if (*(*it)->GetTranslate() >= m_vfMaxExtent)
        if ((*it)->GetTranslate()->X() >= m_vfMaxExtent.X() &&
            (*it)->GetTranslate()->Z() >= m_vfMaxExtent.Z() )
            m_vfMaxExtent = *(*it)->GetTranslate();

        // look for min extent
        //if (*(*it)->GetTranslate() <= m_vfMinExtent)
        if ((*it)->GetTranslate()->X() <= m_vfMinExtent.X() &&
            (*it)->GetTranslate()->Z() <= m_vfMinExtent.Z() )        
            m_vfMinExtent = *(*it)->GetTranslate();

        m_vfMapOrigin += *(*it)->GetTranslate();
    }

    // compute the 'center' of the map
    m_vfMapOrigin.Y() = 0.0f;
    m_vfMapOrigin /= (float)pvEntities->size();

    #ifdef _DEBUG
    CLog::GetLog().Write(LOG_GAMECONSOLE, "Quadtree max extent: %f %f %f", m_vfMaxExtent.X(), m_vfMaxExtent.Y(), m_vfMaxExtent.Z() );
    CLog::GetLog().Write(LOG_GAMECONSOLE, "Quadtree min extent: %f %f %f", m_vfMinExtent.X(), m_vfMinExtent.Y(), m_vfMinExtent.Z() );
    CLog::GetLog().Write(LOG_GAMECONSOLE, "Quadtree Map Origint: %f %f %f", m_vfMapOrigin.X(), m_vfMapOrigin.Y(), m_vfMapOrigin.Z() );
    #endif

    // compute width of root node quadtree will cover
    m_vfMinExtent.Y() = m_vfMaxExtent.Y() = 0.0f;
    m_fNodeWidth = max( m_vfMaxExtent.X()-m_vfMinExtent.X(), m_vfMinExtent.X() - m_vfMaxExtent.X());
    m_fNodeWidth = max( m_fNodeWidth, m_vfMaxExtent.Z()-m_vfMinExtent.Z());
    m_fNodeWidth = max( m_fNodeWidth, m_vfMinExtent.Z()-m_vfMaxExtent.Z());

    #ifdef _DEBUG
    CLog::GetLog().Write(LOG_GAMECONSOLE, "Quadtree root node width: %f", m_fNodeWidth);
    #endif

    // create the quadtree based on these statistics
    // Construct a quadtree of TREE_LEVELS levels deep
	//traversal_count = 0;
	m_pkQRoot = new CQuadNode( Vector3f(m_fNodeWidth/2.0f, m_fNodeWidth/2.0f, 0), m_fNodeWidth/2.0f );
    
    // save the root node for deletion later
    m_vpNodes.push_back(m_pkQRoot);

    // assuming a uniform distribution of entities, try to compute an optimal tree depth
    // want #levels = log(#entities)/log(#subdiv at each level=4)
    //m_iLevels = (int)Mathf::Ceil((Mathf::Log((float)pvEntities->size()))/(Mathf::Log(4.0f)));
    m_iLevels = 5;
    CLog::GetLog().Write(LOG_GAMECONSOLE,"Quadtree depth %d", m_iLevels);

    // compute the initial sub levels of the tree
	SubDivide(m_pkQRoot, m_iLevels);
    
    // add renderable game entities to the quadtree
    for (it = pvEntities->begin(); it!=pvEntities->end(); it++)  {
        //$$$TEMP for now, just add all entities
        Add(*it);
    }

    return;
}



void CQuadTree::Add(CEntity *pEntity)
{    
    //$$$TEMP once bounding boxes are fixed, I'll use this code
    /*
	// Add references for each corner of the bounding box
	addReference( gobj->bbox.max.x, gobj->bbox.max.y, gobj );
	addReference( gobj->bbox.max.x, gobj->bbox.min.y, gobj );
	addReference( gobj->bbox.min.x, gobj->bbox.max.y, gobj );
	addReference( gobj->bbox.min.x, gobj->bbox.min.y, gobj );    //
    */

    // for now, use the position of the entity to place in the tree
    AddReference(*pEntity->GetTranslate(), pEntity);
    return;
}



void CQuadTree::AddReference( Vector3f vOrigin, CEntity * pEntity )
{
	CQuadNode	*node;
	CQuadNode	*prev;		// to point to parent of node
	//Tjunc	*ptr;
	//Tjunc	*list;
    CQuadNode * ptr;
    CQuadNode * list;
	
	assert( m_iLevels > 1 ); 

	// Search in quadtree
	node = m_pkQRoot;
	for(int level = m_iLevels; level > 0; level--)
	{
		prev = node;
		if( vOrigin.X() <= node->m_vOrigin.X() && vOrigin.Z() <= node->m_vOrigin.Z() ) 
			node = node->m_pChildNode[SW];
		else if( vOrigin.X() > node->m_vOrigin.X() && vOrigin.Z() <= node->m_vOrigin.Z() ) 
			node = node->m_pChildNode[SE];
		else if( vOrigin.X() <= node->m_vOrigin.X() && vOrigin.Z() > node->m_vOrigin.Z() ) 
			node = node->m_pChildNode[NW];
		else 
			node = node->m_pChildNode[NE];
	}

	// We're below the last level of the tree now, the pointer points to a 
	// linked list of Tjunc elements.
	// cast the node pointer to a Tjunc pointer so we can search
	// the linked list
	//list = (Tjunc*) node;		
    list = node;
	
	// First check if the game object is already in the linked list
	ptr = list;
    
	while (ptr != NULL)
	{
		//if(ptr->gameObject->id == gobj->id )	// found it
        if(ptr->m_EntMap[pEntity->GetId()] != NULL)
			return;		// it's already in the list, do nothing!
		ptr = ptr->m_pNextNode;
	}

	// Add new item to head of the list
	//list = new Tjunc( gobj, list );
    list = new CQuadNode( pEntity, list );

	// And hang the list in the tree

	if( vOrigin.X() <= prev->m_vOrigin.X() && vOrigin.Z() <= prev->m_vOrigin.Z() ) 
		prev->m_pChildNode[SW] = list;
	else if( vOrigin.X() > prev->m_vOrigin.X() && vOrigin.Z() <= prev->m_vOrigin.Z() ) 
		prev->m_pChildNode[SE] = list;
	else if( vOrigin.X() <= prev->m_vOrigin.X() && vOrigin.Z() > prev->m_vOrigin.Z() ) 
		prev->m_pChildNode[NW] = list;
	else 
		prev->m_pChildNode[NE] = list;

    return;
}



void CQuadTree::ClearQuadTree()
{
    for (vector <CQuadNode *>::iterator it = m_vpNodes.begin(); it!=m_vpNodes.end(); it++)
        delete (*it);
    m_vpNodes.clear();

}

void CQuadTree::SubDivide( CQuadNode * pQNode, int iLevel )
{
	float		hw;

    assert(iLevel > 0);

	if( iLevel == 1 )	// lowest level of pQNodes, don't subdivide any further
		return;

	// Subdivide this Node into 4 and subdivide those even further if necessary
	hw = pQNode->m_fHalfWidth/2.0f;
    pQNode->m_pChildNode[NE] = new CQuadNode( Vector3f(pQNode->m_vOrigin.X() + hw, 0, pQNode->m_vOrigin.Z() + hw), hw );
    pQNode->m_pChildNode[SE] = new CQuadNode( Vector3f(pQNode->m_vOrigin.X() + hw, 0, pQNode->m_vOrigin.Z() - hw), hw );
	pQNode->m_pChildNode[SW] = new CQuadNode( Vector3f(pQNode->m_vOrigin.X() - hw, 0, pQNode->m_vOrigin.Z() - hw), hw );    
	pQNode->m_pChildNode[NW] = new CQuadNode( Vector3f(pQNode->m_vOrigin.X() - hw, 0, pQNode->m_vOrigin.Z() + hw), hw );
	

    // save these pointers for deletion later
    m_vpNodes.push_back(pQNode->m_pChildNode[SW]);
    m_vpNodes.push_back(pQNode->m_pChildNode[SE]);
    m_vpNodes.push_back(pQNode->m_pChildNode[NW]);
    m_vpNodes.push_back(pQNode->m_pChildNode[NE]);

	SubDivide(pQNode->m_pChildNode[SW], iLevel-1);
	SubDivide(pQNode->m_pChildNode[SE], iLevel-1);
	SubDivide(pQNode->m_pChildNode[NW], iLevel-1);
	SubDivide(pQNode->m_pChildNode[NE], iLevel-1);

	return;
}