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

#define QUADTREE_DEFAULT_LEVELS 4
#define QUADTREE_DEFAULT_NODE_WIDTH 25

enum { SW=0, SE, NW, NE };

CQuadTree::CQuadTree() {
    m_pkQRoot = NULL;
    m_iLevels = QUADTREE_DEFAULT_LEVELS;
    m_fNodeWidth = QUADTREE_DEFAULT_NODE_WIDTH;
    m_bIsInitialized = false;
    m_vpNodes.clear();
    Initialize();
}

CQuadTree::CQuadTree( float fNodeWidth ) 
{
    m_pkQRoot = NULL;
    m_iLevels = QUADTREE_DEFAULT_LEVELS;
    m_fNodeWidth = QUADTREE_DEFAULT_NODE_WIDTH;
    m_bIsInitialized = false;
    m_vpNodes.clear();
    m_fNodeWidth = fNodeWidth;
    Initialize();
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
    // use default values to create the quadtree centered at the origin
    if (!pvEntities)  {

        // Construct a quadtree of m_iLevels levels deep
	    m_pkQRoot = new CQuadNode( Vector3f(0, 0, 0), m_fNodeWidth/2.0f );
    
        // save the root node for deletion later
        m_vpNodes.push_back(m_pkQRoot);

        // compute the initial sub levels of the tree
	    SubDivide(m_pkQRoot, m_iLevels);

        m_bIsInitialized = true;
        return;
    }

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
    m_pkQRoot = new CQuadNode( m_vfMapOrigin, m_fNodeWidth/2.0f );
    
    // save the root node for deletion later
    m_vpNodes.push_back(m_pkQRoot);

    #ifdef _DEBUG
    CLog::GetLog().Write(LOG_ALL, "Root node origin: %f %f %f", m_pkQRoot->m_vOrigin.X(), m_pkQRoot->m_vOrigin.Y(), m_pkQRoot->m_vOrigin.Z());
    #endif

    // assuming a uniform distribution of entities, try to compute an optimal tree depth
    // want #levels = log(#entities)/log(#subdiv at each level=4)
    m_iLevels = (int)Mathf::Ceil( (Mathf::Log((float)pvEntities->size())) / (Mathf::Log(4.0f)) );
    //m_iLevels = 5;
    CLog::GetLog().Write(LOG_GAMECONSOLE,"Quadtree depth %d", m_iLevels);

    // compute the initial sub levels of the tree
	SubDivide(m_pkQRoot, m_iLevels);

    // quadtree is now initialized
    m_bIsInitialized = true;

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

    if(m_bIsInitialized == false) {
        #ifdef _DEBUG
        CLog::GetLog().Write(LOG_MISC|LOG_GAMECONSOLE, "ERROR:  Quadtree::add could not add entity QuadTree not initialized yet");
        #endif
        return;
    }

    // for now, use the position of the entity to place in the tree
    AddReference(*pEntity->GetTranslate(), pEntity);
    return;
}



void CQuadTree::AddReference( Vector3f vOrigin, CEntity * pEntity )
{
	CQuadNode	*node;
	CQuadNode	*prev;		// to point to parent of node

    assert( m_iLevels > 1 ); 

	// Search in quadtree for the node this entity should be in
	node = m_pkQRoot;

    //// update the pointers in each node to point to this entity
    //while (node != NULL) {

    //find lowest node in which this entity will fit
    for (int i=0; i<m_iLevels; i++)  {
        prev = node;
        //node->m_EntMap[pEntity->GetId()] = pEntity;
        //#ifdef _DEBUG
        //CLog::GetLog().Write(LOG_MISC, "quadtree:  entity %s ID %d added to node with origin at: %f %f %f", pEntity->GetName(), pEntity->GetId(), node->m_vOrigin.X(), node->m_vOrigin.Y(), node->m_vOrigin.Z());
        //#endif
        if( vOrigin.X() <= node->m_vOrigin.X() && vOrigin.Z() <= node->m_vOrigin.Z() ) 
			node = node->m_pChildNode[SW];
        else if( vOrigin.X() > node->m_vOrigin.X() && vOrigin.Z() <= node->m_vOrigin.Z() )
			node = node->m_pChildNode[SE];
        else if( vOrigin.X() <= node->m_vOrigin.X() && vOrigin.Z() > node->m_vOrigin.Z() ) 
			node = node->m_pChildNode[NW];
		else 
			node = node->m_pChildNode[NE];
    }

    // check if its already there
    if (prev->m_EntMap[pEntity->GetId()] != pEntity)  {
        #ifdef _DEBUG
        CLog::GetLog().Write(LOG_MISC, "quadtree:  entity %s ID %d added to node with origin at: %f %f %f", pEntity->GetName(), pEntity->GetId(), prev->m_vOrigin.X(), prev->m_vOrigin.Y(), prev->m_vOrigin.Z());
        #endif
        prev->m_EntMap[pEntity->GetId()] = pEntity;
    }
    else {
        #ifdef _DEBUG 
        CLog::GetLog().Write(LOG_MISC, "quadtree:  entity %s ID %d IS ALREADY IN node with origin at: %f %f %f", pEntity->GetName(), pEntity->GetId(), prev->m_vOrigin.X(), prev->m_vOrigin.Y(), prev->m_vOrigin.Z());
        #endif
        return;
    }

    #ifdef _DEBUG //spacer for log entry
    CLog::GetLog().Write(LOG_MISC, "\n\n\n");
    #endif

    return;
}



void CQuadTree::ClearQuadTree()
{
    for (vector <CQuadNode *>::iterator it = m_vpNodes.begin(); it!=m_vpNodes.end(); it++)
        delete (*it);
    m_vpNodes.clear();
    m_bIsInitialized = false;
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

    #ifdef _DEBUG
    CLog::GetLog().Write(LOG_MISC, "NE node origin: %f %f %f", pQNode->m_pChildNode[NE]->m_vOrigin.X(), pQNode->m_pChildNode[NE]->m_vOrigin.Y(), pQNode->m_pChildNode[NE]->m_vOrigin.Z());
    CLog::GetLog().Write(LOG_MISC, "NW node origin: %f %f %f", pQNode->m_pChildNode[NW]->m_vOrigin.X(), pQNode->m_pChildNode[NW]->m_vOrigin.Y(), pQNode->m_pChildNode[NW]->m_vOrigin.Z());
    CLog::GetLog().Write(LOG_MISC, "SE node origin: %f %f %f", pQNode->m_pChildNode[SE]->m_vOrigin.X(), pQNode->m_pChildNode[SE]->m_vOrigin.Y(), pQNode->m_pChildNode[SE]->m_vOrigin.Z());
    CLog::GetLog().Write(LOG_MISC, "SW node origin: %f %f %f", pQNode->m_pChildNode[SW]->m_vOrigin.X(), pQNode->m_pChildNode[SW]->m_vOrigin.Y(), pQNode->m_pChildNode[SW]->m_vOrigin.Z());
    #endif

	SubDivide(pQNode->m_pChildNode[SW], iLevel-1);
	SubDivide(pQNode->m_pChildNode[SE], iLevel-1);
	SubDivide(pQNode->m_pChildNode[NW], iLevel-1);
	SubDivide(pQNode->m_pChildNode[NE], iLevel-1);

	return;
}