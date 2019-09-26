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

void DGCamera::SetCameraFrustumLower(float topEdge, float leftEdge, float nearDistance, float farDistance, float range)
{
    mNearDistance = nearDistance;
    mFarDistance  = farDistance;

    float topScale =  2.0f / range;
    float leftScale = leftEdge * 0.5f;

    MTXFrustum
    (
        mCamMtx,
        topScale * topEdge,
        -topEdge + topScale * topEdge,
        -leftScale,
        leftScale,
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

void DGCamera::SetCamUp(Vec up)
{
    mCamUp = up;
}

void DGCamera::SetTargetPos(Vec position)
{
    mTargetPos = position;
}

Vec DGCamera::GetTargetPos()
{
    return mTargetPos;
}

void DGCamera::SetTargetMode(enumDG_RENDMAN_TARGET_MODE mode)
{
    mMode = mode;
}

void DGCamera::SetCamera(Mtx mtx)
{
    /*
    mflr      r0
    stw       r0, sender_lr(r1)
    stwu      r1, back_chain(r1)
    stw       r31, 0x20+var_4(r1)
    addi      r31, r4, 0
    stw       r30, 0x20+var_8(r1)
    */
    
    SetProjectionMtx();

    addi      r3, r30, 0
    addi      r4, r31, 0
    bl        GetViewMtx__8DGCameraFRA3_A4_f # DGCamera::GetViewMtx((float (&)[3][4]))
    lwz       r0, 0x11C(r30)
    addi      r4, r1, 0x20+var_10
    stw       r0, 0x20+var_10(r1)
    lwz       r3, 0x120(r30)
    lfs       f1, 0x124(r30)
    lfs       f2, 0x128(r30)
    lfs       f3, 0xF8(r30)
    lfs       f4, 0xFC(r30)
    bl        GXSetFog
    lwz       r0, 0x20+sender_lr(r1)
    lwz       r31, 0x20+var_4(r1)
    lwz       r30, 0x20+var_8(r1)
    mtlr      r0
    addi      r1, r1, 0x20
    blr
}

void DGCamera::SetProjectionMtx()
{
    GXSetProjection(mCamMtx, GX_PERSPECTIVE);
}

void DGCamera::SetFogColor(GXColor const & color)
{
    mFogColor = color;
}

void DGCamera::SetFogRange(float start, float end)
{
    mFogStartZ = mNearDistance + (start * (mFarDistance - mNearDistance));
    mFogEndZ = mNearDistance + (end * (mFarDistance - mNearDistance))
}