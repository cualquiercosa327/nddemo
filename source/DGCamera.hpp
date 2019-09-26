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
    void SetCameraFrustumLower(float topEdge, float leftEdge, float nearDistance, float farDistance, float range);
    void SetLightFrustrum(float height, float width, float nearZ);
    void SetCamUp(Vec up);
    void SetTargetPos(Vec position);
    Vec GetTargetPos();
    void SetTargetMode(enumDG_RENDMAN_TARGET_MODE mode);
    void SetCamera(Mtx mtx);
    void SetProjectionMtx();
    void SetFogColor(GXColor const & color);

};

#endif