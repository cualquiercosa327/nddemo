#ifndef INCLUDE_DGTEXPRO_HPP
#define INCLUDE_DGTEXPRO_HPP

#include <dolphin.h>

#include "DGCamera.hpp"
#include "DGTexMan.hpp"

class DGTexPro
{
private:
    DGTexMan *mTexMan;
    u16 mTexHandle;
    GXTexWrapMode mWrapS;
    GXTexWrapMode mWrapT;
    DGCamera *mCamera;
    void *mImagePtr;
    u16 mWidth;
    u16 mHeight;
    GXTexFmt mFormat;
    u8 mMipLevel;

public:
    DGTexPro(DGTexMan *texMan);
    DGTexPro(DGTexMan *texMan, char *fileName);
    ~DGTexPro();

    void GetLightMtx(Mtx &mtx);
    GXBool InitTexObj(GXTexObj *obj);
    void SetCamera(DGCamera *camera);
    void SetDirectTex(void *ptr, u16 width, u16 height, GXTexFmt format, u8 mipLevel);
};

#endif