#ifndef CAMERAFREE_H
#define CAMERAFREE_H

#include "camera.h"


class CCameraFreeLook : public CD3DCamera
{
public:
    CCameraFreeLook();
    void Update( int iInput, bool bState );
    VOID    FrameMove( FLOAT fElapsedTime );
    D3DUtil_CameraKeys MapKey( UINT nKey );
protected:


private:
    bool m_bInvertYaw;
    D3DXMATRIX m_mCameraWorld;

};


#endif