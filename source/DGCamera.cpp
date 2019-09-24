#include "DGCamera.hpp"

DGCamera::DGCamera()
{
    mPosition = DGPosition();

    SetCameraFrustum(24.0f, 32.0f, 16.0f, 1024.0f);
    SetLightFrustum(24.0f, 32.0f, 16.0f);
}

void DGCamera::SetCameraFrustum(float topEdge, float leftEdge, float nearDistance, float farDistance);
{
    GXSetCopyClamp(GX_CLAMP_TOP | GX_CLAMP_BOTTOM);

    MTXFrustum(&mCamMtx, topEdge * 0.5f, -topEdge * 0.5f, 
    -leftEdge * 0.5f, 
    leftEdge * 0.5f, 
    nearDistance, 
    farDistance);
}