#include "DGCamera.hpp"

DGCamera::DGCamera()
{   
    SetCameraFrustum(24.0f, 32.0f, 16.0f, 1024.0f);
    SetLightFrustrum(24.0f, 32.0f, 16.0f);
}

void DGCamera::SetCameraFrustum(float topEdge, float leftEdge, float nearDistance, float farDistance)
{
    mNearDistance = nearDistance;
    mFarDistance = farDistance;
    
    GXSetCopyClamp((GXFBClamp)(GX_CLAMP_TOP | GX_CLAMP_BOTTOM));

    float scale = 0.5f;

    MTXFrustum
    (
        mCamMtx, 
        topEdge * scale, 
        -topEdge * scale, 
        -leftEdge * scale, 
        leftEdge * scale, 
        nearDistance, 
        farDistance
    );
}

void DGCamera::SetCameraFrustumUpper(float topEdge, float leftEdge, float nearDistance, float farDistance)
{

    mNearDistance = nearDistance;
    mFarDistance = farDistance;

    float scale = 0.5f;
    
    MTXFrustum
    (
        mCamMtx,
        topEdge * scale,
        -topEdge * scale,
        -leftEdge * scale,
        leftEdge * scale,
        nearDistance,
        farDistance
    );
}

void DGCamera::SetLightFrustrum(float height, float width, float nearZ) 
{
    float scale = 0.5f;
    
    MTXLightFrustum
    (
        mLightMtx,
        (height * scale), (-height * scale),
        (-width * scale), (width * scale),
        nearZ, 0.5f, 0.5f, 0.5f, 0.5f
    );

    MTXLightFrustum
    (
        mLight2Mtx,
        (height * scale), (-height * scale),
        (-width * scale), (width * scale),
        nearZ, 0.5f, -0.5F, 0.5f, 0.5f
    );
}

void DGCamera::SetTargetMode(enumDG_RENDMAN_TARGET_MODE mode)
{
    mMode = mode;
}

void DGCamera::SetFogColor(GXColor const & color)
{
    mFogColor = color;
}