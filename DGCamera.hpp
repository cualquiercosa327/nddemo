#ifndef INCLUDE_DGCAMERA_HPP
#define INCLUDE_DGCAMERA_HPP

#include <dolphin.h>

#include "DUMacro.hpp"
#include "DGPosition.hpp"

class DGCamera
{
    
    public:

    enum enumDG_RENDMAN_TARGET_MODE
    {
        DGR_TARGET_POSITION,
    };

    DGPosition mPosition;
    Mtx44 mCamMtx;
    Mtx mLightMtx;
    Mtx mLight2Mtx;
    float mNearDistance;
    float mFarDistance;
    Vec mCamUp;
    Vec mTargetPos;
    enumDG_RENDMAN_TARGET_MODE mMode;
    GXColor mFogColor;
    GXFogType mFogType;
    float mFogStartZ;
    float mFogEndZ;

    DGCamera();
    ~DGCamera();

    void SetCameraFrustum(float topEdge, float leftEdge, float nearDistance, float farDistance);
    void SetCameraFrustumUpper(float topEdge, float leftEdge, float nearDistance, float farDistance);
    void SetLightFrustrum(float height, float width, float nearZ);
    void SetTargetMode(enumDG_RENDMAN_TARGET_MODE mode);
    void SetFogColor(GXColor const & color);

};

#endif