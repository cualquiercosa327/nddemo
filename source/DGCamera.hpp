#ifndef INCLUDE_DGCAMERA_HPP
#define INCLUDE_DGCAMERA_HPP

#include <dolphin.h>

#include "DUMacro.hpp"
#include "DGPosition.hpp"

class DGCamera
{
    public:

    DGPosition mPosition;
    Mtx mCamMtx;

    enum enumDG_RENDMAN_TARGET_MODE
    {
        TARGET_MODE_NULL = 0,
    };

    DGCamera();
    ~DGCamera();

    void SetCameraFrustum(float topEdge, float leftEdge, float nearDistance, float farDistance);
    void SetCameraFrustumUpper(float t, float b, float l, float r);
    void SetCameraFrustumLower(float t, float b, float l, float r, float n);
    void SetLightFrustum(float t, float b, float l);
    void SetCamUp(Vec & up);
    void SetTargetPos(Vec & position);
    void SetTargetPos();
    void SetTargetMode(enumDG_RENDMAN_TARGET_MODE mode);
    void SetCamera(Mtx m);
    void SetProjectionMtx();
    void GetViewMtx(Mtx m);
    void GetLightMtx(Mtx m);
    void GetLightMtxYInverse(Mtx m);
    void SetFogType(GXFogType type);
    void SetFogRange(float rng1, float rng2);
    void SetFogRangeRatio(float rng1, float rng2);
    void SetFogColor(const & GXColor);
};

#endif