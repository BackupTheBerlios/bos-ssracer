#ifndef CAMERACHASE_H
#define CAMERACHASE_H


#include "camera.h"
#include "vehicle.h"


class CCameraChase : public CD3DCamera
{
public:
	CCameraChase();
	CCameraChase( CVehicle * pkVehicle );

    void Update();
    void Update( int iInput, bool bState );
    
    // Call these from client and use Get*Matrix() to read new matrices
    virtual VOID FrameMove( FLOAT fElapsedTime );

    // Functions to get state
    D3DXVECTOR3  GetWorldRight()            { return D3DXVECTOR3( m_mCameraWorld._11, m_mCameraWorld._12, m_mCameraWorld._13 ); } 
    D3DXVECTOR3  GetWorldUp()               { return D3DXVECTOR3( m_mCameraWorld._21, m_mCameraWorld._22, m_mCameraWorld._23 ); }
    D3DXVECTOR3  GetWorldAhead()            { return D3DXVECTOR3( m_mCameraWorld._31, m_mCameraWorld._32, m_mCameraWorld._33 ); }
    D3DXVECTOR3  GetEyePt()                 { return D3DXVECTOR3( m_mCameraWorld._41, m_mCameraWorld._42, m_mCameraWorld._43 ); }

	void SetVehicle( CVehicle * pkVehicle );   // set this camera to chase an entity

protected:
    D3DXMATRIX m_mCameraWorld;       // World matrix of the camera (inverse of the view matrix)

private:
    CVehicle * m_pkVehicle;
};


#endif