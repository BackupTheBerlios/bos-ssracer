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
#include "camera.h"

//#include "WmlDistVec3Fru3.h"
#include "WmlDistVec3Box3.h"
#include "WmlIntrBox3Fru3.h"
#include "WmlContBox3.h"
#include "WmlContSphere3.h"
#include "WmlPlane3.h"
#include "WmlIntrLin3Box3.h"
#include "WmlSegment3.h"
#include "WmlIntrBox3Box3.h"


//#include "macros.h"

#define QUADTREE_DEFAULT_LEVELS 4
#define QUADTREE_DEFAULT_NODE_WIDTH 25


// static member initialization
CQuadNode * CQuadTree::m_pkQRoot = NULL;


CQuadNode::CQuadNode(Vector3f vOrigin, float fHalfWidth) {
    m_vOrigin = vOrigin;
    m_fHalfWidth = fHalfWidth;
    for (int i=0; i<4; i++)  m_pChildNode[i] = NULL;
    m_EntMap.clear();

    // set the AABBox
    m_BBox.Center() = vOrigin;
    m_BBox.Extent(0) = m_BBox.Extent(1) = m_BBox.Extent(2) = fHalfWidth;
    m_BBox.Axis(0) = Vector3f(1,0,0);  // axis aligned
    m_BBox.Axis(1) = Vector3f(0,1,0);
    m_BBox.Axis(2) = Vector3f(0,0,1);

    // set the bounding sphere
    //m_BSphere.Center() = vOrigin;
    // use diagonal of box to get bounding sphere
    //m_BSphere.Radius() = (Vector3f(max(m_BBox.Extent(0), m_BBox.Extent(2)), 0, max(m_BBox.Extent(0), m_BBox.Extent(2))) 
    //    + Vector3f(min(m_BBox.Extent(0), m_BBox.Extent(2)), 0, min(m_BBox.Extent(0), m_BBox.Extent(2)))).Length()/2.0f; 
    //m_BSphere.Radius() = fHalfWidth*1.1f;
    //m_BSphere.Radius() = 1.0f;
    
    Vector3f vBox[8];
    m_BBox.ComputeVertices(vBox);
    m_BSphere = ContSphereOfAABB(8, vBox);
};



CQuadTree::CQuadTree() {
    m_pkQRoot = NULL;
    m_iLevels = QUADTREE_DEFAULT_LEVELS;
    m_fNodeWidth = QUADTREE_DEFAULT_NODE_WIDTH;
    m_bIsInitialized = false;
    m_vpNodes.clear();
    m_vpVisibleNodes.clear();
    Initialize();
}

CQuadTree::CQuadTree( float fNodeWidth ) 
{
    m_pkQRoot = NULL;
    m_iLevels = QUADTREE_DEFAULT_LEVELS;
    m_fNodeWidth = QUADTREE_DEFAULT_NODE_WIDTH;
    m_bIsInitialized = false;
    m_vpNodes.clear();
    m_vpVisibleNodes.clear();
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
	    m_pkQRoot = new CQuadNode( Vector3f(0, 0, 0), m_fNodeWidth );
    
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
    m_fNodeWidth = max( abs(m_vfMaxExtent.X()-m_vfMinExtent.X()), abs(m_vfMinExtent.X() - m_vfMaxExtent.X()));
    m_fNodeWidth = max( m_fNodeWidth, abs(m_vfMaxExtent.Z()-m_vfMinExtent.Z()));
    m_fNodeWidth = max( m_fNodeWidth, abs(m_vfMinExtent.Z()-m_vfMaxExtent.Z()));
    m_fNodeWidth *= 0.9f;//0.75f;//2.0f;   

    //$$$TEMP optimal for map_final only
    //m_fNodeWidth = 2200.0f;  

    #ifdef _DEBUG
    CLog::GetLog().Write(LOG_GAMECONSOLE, "Quadtree root node width: %f", m_fNodeWidth);
    #endif

    // create the quadtree based on these statistics
    m_pkQRoot = new CQuadNode( m_vfMapOrigin, m_fNodeWidth );
    
    // save the root node for deletion later
    m_vpNodes.push_back(m_pkQRoot);

    #ifdef _DEBUG
    CLog::GetLog().Write(LOG_ALL, "Root node origin: %f %f %f", m_pkQRoot->m_vOrigin.X(), m_pkQRoot->m_vOrigin.Y(), m_pkQRoot->m_vOrigin.Z());
    #endif

    // assuming a uniform distribution of entities, try to compute an optimal tree depth
    // want #levels = log(#entities)/log(#subdiv at each level=4)
    m_iLevels = (int)Mathf::Ceil( (Mathf::Log((float)pvEntities->size())) / (Mathf::Log(4.0f)) ) +2 ;
    //m_iLevels = 6;//m_iLevels = 7;///GOOD
    
    #ifdef _DEBUG
    CLog::GetLog().Write(LOG_GAMECONSOLE,"Quadtree depth %d", m_iLevels);
    #endif

    // compute the initial sub levels of the tree
	SubDivide(m_pkQRoot, m_iLevels);

    // quadtree is now initialized
    m_bIsInitialized = true;

    // add renderable game entities to the quadtree
    for (it = pvEntities->begin(); it!=pvEntities->end(); it++)  {
        
        // only add static and renderable entities
        if ((*it)->getIsStatic() && (*it)->getIsRenderable())
            Add(*it);
    }


    return;
}



void CQuadTree::Add(CEntity *pEntity)
{    

    if(m_bIsInitialized == false) {
        #ifdef _DEBUG
        CLog::GetLog().Write(LOG_MISC|LOG_GAMECONSOLE, "ERROR:  Quadtree::add could not add entity QuadTree not initialized yet");
        #endif
        return;
    }

    // for now, use the position of the entity to place in the tree
    //AddReference(*pEntity->GetTranslate(), pEntity);

    /*
    Vector3f vBox[8];
    pEntity->GetBoundingBox()->ComputeVertices(vBox);
    // zero out the y to keep these boxes on the ground plane
    for (int i=0; i<8; i++)  {
        vBox[i].Y() = 0.0f;
    }

    // Add references for each corner of the bounding box  <-- not accurate
  	//AddReference( vBox[0], pEntity);  // NE +z +x
    //AddReference( vBox[1], pEntity);  // NW +z -x
    //AddReference( vBox[4], pEntity);  // SE -z +x
    //AddReference( vBox[5], pEntity);  // SW -z -x
    */

    // add reference to each box that this intersects
    AddReference( m_pkQRoot->m_BBox, pEntity, m_pkQRoot);
    return;
}



void CQuadTree::AddReference( Vector3f vOrigin, CEntity * pEntity )
{
	CQuadNode	*node;
	CQuadNode	*prev;		// to point to parent of node

    #ifdef _DEBUG
    assert( m_iLevels > 1 ); 
    #endif

	// Search in quadtree for the node this entity should be in
	node = m_pkQRoot;

    // copy this entity into each child node
    for (int i=0; i<m_iLevels; i++)  {
        prev = node;
        node->m_EntMap[pEntity->GetId()] = pEntity;
        //#ifdef _DEBUG
        //CLog::GetLog().Write(LOG_MISC, "quadtree:  entity %s ID %d added to node with origin at: %f %f %f", pEntity->GetName(), pEntity->GetId(), node->m_vOrigin.X(), node->m_vOrigin.Y(), node->m_vOrigin.Z());
        //#endif

        // check corners of the OBB
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
    CLog::GetLog().Write(LOG_MISC, "\n");
    #endif

    return;
}



void CQuadTree::AddReference( Box3f box, CEntity * pEntity, CQuadNode * node )  {

    assert( m_iLevels > 1 ); 

    Box3f boxTemp =  box;
    Box3f boxEnt = *pEntity->GetBoundingBox();

    // move box to the entity's height
    boxTemp.Center().Y() = boxEnt.Center().Y();
    //box.Extent(1) = 100.0f; //extend this box infinitely

    bool bEntInQuad = false;

    Vector3f vBoxVerts[8];
    bool abValid[8] = { 1,1,1,1,1,1,1,1 };//{ 0,0,0,0,0,0,0,0 };
    bool bEntBoxInNode = false;
    bool bNodeInEntBox = false;

    switch(TestIntersection( boxTemp,  boxEnt ) ) 
    {
        case true:  // box intersects
            node->m_EntMap[pEntity->GetId()] = pEntity; 
            bEntInQuad = true;  // find if the children intersect too
            break;

        case false:  // ent box is INSIDE or OUTSIDE the node
            // get vertices for the bounding box                
            boxEnt.ComputeVertices(vBoxVerts);

            // if entities box is contained in node box
            for (int j=0; j<8; j++ ) {
                if (InBox( vBoxVerts[j], boxTemp))  {
                    bEntBoxInNode = true;
                }
            }

            if (bEntBoxInNode ==true)  {
            //if (ContOrientedBox (8, vBoxVerts, abValid, node->m_BBox))  {
                node->m_EntMap[pEntity->GetId()] = pEntity; //entity is in this node
                bEntInQuad = true;  // find out what child quads also contain this
            }
            else { // OUTSIDE or entities box contains the bounding box!
                boxTemp.ComputeVertices(vBoxVerts);
                
                // if node box  is contained in entities box
                for (int j=0; j<8; j++ ) {
                    if (InBox( vBoxVerts[j], boxEnt))  {
                        bNodeInEntBox = true;
                    }
                }

                if (bNodeInEntBox == true)  {
                //if (ContOrientedBox (8, vBoxVerts, abValid, boxTemp))  {
                    node->m_EntMap[pEntity->GetId()] = pEntity; //entity is in this node
                    bEntInQuad = true;  // find out what child quads also contain this
                }
                else {
                    // entity is outside, so don't add
                    bEntInQuad = false;
                    return;
                }
            }
            break;
    }

    // now this box will also intersect/be contained in the children as well
    if (bEntInQuad == true )  {
        if (node->m_pChildNode[NE] != NULL)  {
            AddReference( node->m_pChildNode[NE]->m_BBox, pEntity, node->m_pChildNode[NE]);
            //node->m_pChildNode[NE]->m_EntMap[pEntity->GetId()] = pEntity;
        }
        if (node->m_pChildNode[NW] != NULL)  {
            AddReference( node->m_pChildNode[NW]->m_BBox, pEntity, node->m_pChildNode[NW]);
            //node->m_pChildNode[NW]->m_EntMap[pEntity->GetId()] = pEntity;
        }
        if (node->m_pChildNode[SE] != NULL)  {
            AddReference( node->m_pChildNode[SE]->m_BBox, pEntity, node->m_pChildNode[SE]);
            //node->m_pChildNode[SE]->m_EntMap[pEntity->GetId()] = pEntity;
        }
        if (node->m_pChildNode[SW] != NULL)  {
            AddReference( node->m_pChildNode[SW]->m_BBox, pEntity, node->m_pChildNode[SW]);
            //node->m_pChildNode[SW]->m_EntMap[pEntity->GetId()] = pEntity;
        }        
    }

    return;
}





void CQuadTree::ClearQuadTree()
{
    //for (vector <CQuadNode *>::iterator it = m_vpNodes.begin(); it!=m_vpNodes.end(); it++)
    //    delete (*it);
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
    pQNode->m_pChildNode[SW] = new CQuadNode( Vector3f(pQNode->m_vOrigin.X() - hw, 0, pQNode->m_vOrigin.Z() - hw), hw );    
    pQNode->m_pChildNode[SE] = new CQuadNode( Vector3f(pQNode->m_vOrigin.X() + hw, 0, pQNode->m_vOrigin.Z() - hw), hw );
	pQNode->m_pChildNode[NW] = new CQuadNode( Vector3f(pQNode->m_vOrigin.X() - hw, 0, pQNode->m_vOrigin.Z() + hw), hw );
    pQNode->m_pChildNode[NE] = new CQuadNode( Vector3f(pQNode->m_vOrigin.X() + hw, 0, pQNode->m_vOrigin.Z() + hw), hw );

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

    SubDivide(pQNode->m_pChildNode[NE], iLevel-1);
   	SubDivide(pQNode->m_pChildNode[NW], iLevel-1);
   	SubDivide(pQNode->m_pChildNode[SE], iLevel-1);
	SubDivide(pQNode->m_pChildNode[SW], iLevel-1);

	return;
}


enum { INSIDE=0, OUTSIDE, INTERSECT };

int FrustumContainsSphere( CD3DCamera * pCamera, Sphere3f pSphere)
{
   	// various distances
	float fDistance;

    //$$$TEMP get the frustum planes from the camera's CULLINFO
    Plane3f plane[6];
    CULLINFO *cInfo = pCamera->GetCullInfo();
    for (int j=0; j<6; j++)  {
        plane[j] = Plane3f( Vector3f(cInfo->planeFrustum[j].a,  cInfo->planeFrustum[j].b,  cInfo->planeFrustum[j].c), cInfo->planeFrustum[j].d);
    }


	// calculate our distances to each of the planes
	for(int i = 0; i < 6; ++i) {

		// find the distance to this plane
		//fDistance = plane[i].GetNormal().Dot(pSphere.Center()) + plane[i].GetNormal().Length();
        //fDistance = plane[i].GetNormal().Dot(pSphere.Center()) + plane[i].DistanceTo(pSphere.Center());
        fDistance = plane[i].GetNormal().Dot(pSphere.Center()) + plane[i][3];

		// if this distance is < -sphere.radius, we are outside
		if(fDistance < -pSphere.Radius())
			return(OUTSIDE);

		// else if the distance is between +- radius, then we intersect
		if((float)fabs(fDistance) < pSphere.Radius())
			return(INTERSECT);
	}

	// otherwise we are fully in view
    return (INSIDE);
}



int FrustumContainsBox( CD3DCamera * pCamera, Box3f BBox )
{
    Vector3f vCorner[8];
	int iTotalIn = 0;

    Plane3f * plane = pCamera->GetCullInfo()->wmlPlaneFrustum;

	// get the corners of the box into the vCorner array
	BBox.ComputeVertices(vCorner);

	// test all 8 corners against the 6 sides 
	// if all points are behind 1 specific plane, we are out
	// if we are in with all points, then we are fully in
	for(int p = 0; p < 6; ++p) {
	
		int iInCount = 8;
		int iPtIn = 1;

		for(int i = 0; i < 8; ++i) {

			// test this point against the planes
            if( plane[p].WhichSide(vCorner[i]) == Plane3f::NEGATIVE_SIDE ) {
                iPtIn = 0;
				--iInCount;
			}
		}

		// were all the points outside of plane p?
        if(iInCount == 0)  {
            return(OUTSIDE);
        }

		// check if they were all on the right side of the plane
		iTotalIn += iPtIn;
	}

	// so if iTotalIn is 6, then all are inside the view
    if(iTotalIn == 6)  {
        return(INSIDE); 
    }

	// we must be partly in then otherwise
 
	return(INTERSECT);  //WORKING

}



// recursively cull nodes that are not visible to the camera
void CQuadTree::CullVisibility(CD3DCamera * pCamera, CQuadNode* pNode, bool bTestChildren)
{
	// do we need to check for clipping?
	if(bTestChildren) {
        // check if we are not inside this node first
        if(InBox (pCamera->GetEye(), pNode->m_BBox) == false )  {
            
            // check if frustrum constains bounding sphere for node
            switch (FrustumContainsSphere(pCamera, pNode->m_BSphere))  {
            //switch( FrustumContainsBox(pCamera, pNode->m_BBox) )  {            
                case OUTSIDE:  // outside, so cull this node
                    return;
        
                case INSIDE:  // inside so render this node and it's children
                    AddVisibleNode( pNode );  
                    bTestChildren = false;
                    return;
                    break;

                case INTERSECT:  // intersects, so check the AABB
                     switch( FrustumContainsBox(pCamera, pNode->m_BBox) )  {
                        case OUTSIDE:  // outside the AABB, so cull
                            return;

                        case INSIDE:   // inside the AABB, so render
                            AddVisibleNode( pNode );  
                            bTestChildren = false;
                            return;
                            break;

                        case INTERSECT:
                            bTestChildren = true;  // need to test the children                            
                            break;
                    }
                    break;
            }// end switch (
    
        }// end if (InBox
        else {
            bTestChildren = true;  // need to test the children since we're in this node 
        }
	}// end if (bTestChildren ...
    

    // check the children if this node intersects or camera intersects the bounding box for this node
    if (bTestChildren)  {
        if (pNode->m_pChildNode[NE] )  {
            CullVisibility( pCamera, pNode->m_pChildNode[NE], true);

        }
        else{
            AddVisibleNode( pNode );
            //return;
        }

        if (pNode->m_pChildNode[NW])  {
            CullVisibility( pCamera, pNode->m_pChildNode[NW], true);

        }
        else{
            AddVisibleNode( pNode );  
            //return;
        }
       
        if (pNode->m_pChildNode[SE])  {
            CullVisibility( pCamera, pNode->m_pChildNode[SE], true);

        }
        else{
            AddVisibleNode( pNode );
            //return;
        }

        if (pNode->m_pChildNode[SW])  {
            CullVisibility( pCamera, pNode->m_pChildNode[SW], true);

        }
        else{
            AddVisibleNode( pNode );
            //return;
        }
    }

    return;
}
