#include "CObject.h"






void CObject::setName(char* newName)
{
	strcpy(m_name, newName);
}

void CObject::setType(int objectType)
{
	m_type = objectType;
}

void CObject::setId(int id)
{
	m_id = id;
}

void CObject::setTranslate(Vector3f translate)
{
	m_translate = translate;
}

void CObject::setRotate (Vector3f rotate)
{
	m_rotate = rotate;
}

void CObject::setScale (Vector3f scale)
{
	m_scale = scale;
}

void CObject::setBoundingBox(Box3f &rect)
{
	m_box = rect;
}

void CObject::setBoundingSphere(Sphere3f &sphere)
{
	m_sphere = sphere;
}

char* CObject::getName()
{
	return m_name;
}

int CObject::getType()
{
	return m_type;
}

int CObject::getId()
{
	return m_id;
}

Vector3f CObject::getTranslate()
{
	return m_translate;
}

Vector3f CObject::getRotate()
{
	return m_rotate;
}

Vector3f CObject::getScale()
{
	return m_scale;
}

Sphere3f CObject::getBoundingSphere()
{
	return m_sphere;
}

Box3f CObject::getBoundingBox()
{
	return m_box;
}


//void CObject::applyObjectTransform(tBoundingRectangle *currentRectangle, tBoundingRectangle *returnRectangle)
//{
	/*** Scale the bounding box ***/
	//returnRectangle->minPoint = currentRectangle->minPoint * m_scale;
	//returnRectangle->vecX = currentRectangle->vecX * m_scale;
	//returnRectangle->vecY = currentRectangle->vecY * m_scale;
	//returnRectangle->vecZ = currentRectangle->vecZ * m_scale;
	/*** End scale bounding box ***/

	/*** Rotate the bounding box ***/
	//CQuaternion rotate, Qx, Qy, Qz, tempQuaternion, resultQuaternion;
	//CVector3 tempPoint;

	// Construct 3 quaternions corresponding to the rotation about each axis(X, Y, Z)
	//Qx = CQuaternion( float(cos(DEG2RAD(m_rotate.x/2.0))), CVector3(float(sin(DEG2RAD(m_rotate.x/2.0))), 0.0, 0.0));
	//Qy = CQuaternion( float(cos(DEG2RAD(m_rotate.y/2.0))), CVector3(0.0, float(sin(DEG2RAD(m_rotate.y/2.0))), 0.0));
	//Qz = CQuaternion( float(cos(DEG2RAD(m_rotate.z/2.0))), CVector3(0.0, 0.0, float(DEG2RAD(sin(m_rotate.z/2.0)))));
	
	// Amalgamate the 3 quaternions
	//rotate = Qz * Qy * Qx;
	//rotate.Normalize();

	//CQuaternion rotateInverse = rotate.Inverse();

	// Rotate the minPoint
	//tempPoint = returnRectangle->minPoint;
	//tempQuaternion = CQuaternion(0, tempPoint);
	//resultQuaternion = rotate * tempQuaternion * rotateInverse;
	//CVector3 newMinPoint = resultQuaternion.V();

	// Rotate vecX
	//tempPoint = returnRectangle->minPoint + returnRectangle->vecX;
	//tempQuaternion = CQuaternion(0, tempPoint);
	//resultQuaternion = rotate * tempQuaternion * rotateInverse;
	//returnRectangle->vecX = resultQuaternion.V() - newMinPoint;

	// Rotate vecY
	//tempPoint = returnRectangle->minPoint + returnRectangle->vecY;
	//tempQuaternion = CQuaternion(0, tempPoint);
	//resultQuaternion = rotate * tempQuaternion * rotateInverse;
	//returnRectangle->vecY = resultQuaternion.V() - newMinPoint;

	// Rotate vecZ
	//tempPoint = returnRectangle->minPoint + returnRectangle->vecZ;
	//tempQuaternion = CQuaternion(0, tempPoint);
	//resultQuaternion = rotate * tempQuaternion * rotateInverse;
	//returnRectangle->vecZ = resultQuaternion.V() - newMinPoint;


	//returnRectangle->minPoint = newMinPoint;

	/*** End rotate bounding box ***/

	/*** Translate the bounding box ***/
	//returnRectangle->minPoint = returnRectangle->minPoint + m_translate;
	/*** End translate bounding box ***/
//}

/*
void CObject::createWmlBoundingBox(tBoundingRectangle* rect, Box3f* wmlRect)
{
	CVector3 center, temp;
	float magnitude;
	center = rect->minPoint + (rect->vecX/2.0f) + (rect->vecY/2.0f) + (rect->vecZ/2.0f);

	wmlRect->Center() = Vector3f(center.x, center.y, center.z);

	temp = rect->vecX;

	magnitude = temp.Magnitude()/2.0f;
	temp.Normalize();

	wmlRect->Axis(0) = Vector3f(temp.x, temp.y, temp.z);
	wmlRect->Extent(0) = magnitude;

	temp = rect->vecY;

	magnitude = temp.Magnitude()/2.0f;
	temp.Normalize();

	wmlRect->Axis(1) = Vector3f(temp.x, temp.y, temp.z);
	wmlRect->Extent(1) = magnitude;

	temp = rect->vecZ;

	magnitude = temp.Magnitude()/2.0f;
	temp.Normalize();

	wmlRect->Axis(2) = Vector3f(temp.x, temp.y, temp.z);
	wmlRect->Extent(2) = magnitude;
	

}
*/

