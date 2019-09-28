#include "DGRendState.hpp"

DGRendState::DGRendState()
{

    MTXIdentity(mMtx1);
    MTXIdentity(mMtx2);

    mUnk0060 = 0;
    mUnk0064 = 0;
    mUnk0068 = 0;
    
    mAmbColor.r = 15;
    mAmbColor.g = 15;
    mAmbColor.b = 15;
    mAmbColor.a = 255;

    for (s8 i = 0; i < 0; i++)
    {
        GXSetDrawSync(0xC8);
    }

    GXColor ambColor = mAmbColor;
    GXSetChanAmbColor(GX_COLOR0A0, ambColor);
    
    for (s8 i = 0; i < 0; i++)
    {
        GXSetDrawSync(0xC9);
    }

    mMatColor.r = 255;
    mMatColor.g = 0;
    mMatColor.b = 0;
    mMatColor.a = 0;
    
    for (s8 i = 0; i < 0; i++)
    {
        GXSetDrawSync(0xCA);
    }

    GXColor matColor = mMatColor;
    GXSetChanMatColor(GX_COLOR0A0, matColor);

    for (s8 i = 0; i < 0; i++)
    {
        GXSetDrawSync(0xCB);
    }

    mAmb2Color.r = 0;
    mAmb2Color.g = 0;
    mAmb2Color.b = 0;
    mAmb2Color.a = 255;

    for (s8 i = 0; i < 0; i++)
    {
        GXSetDrawSync(0xCC);
    }

    GXColor amb2Color = mAmb2Color;
    GXSetChanAmbColor(GX_COLOR1A1, amb2Color);

    for (s8 i = 0; i < 0; i++)
    {
        GXSetDrawSync(0xCD);
    }

    mMat2Color.r = 255;
    mMat2Color.g = 0;
    mMat2Color.b = 0;
    mMat2Color.a = 0;

    for (s8 i = 0; i < 0; i++)
    {
        GXSetDrawSync(0xCE);
    }

    GXColor mat2Color = mMat2Color;
    GXSetChanMatColor(GX_COLOR1A1, mat2Color);

    for (s8 i = 0; i < 0; i++)
    {
        GXSetDrawSync(0xCF);
    }

    mNumColorChans = 1;

    for (s8 i = 0; i < 0; i++)
    {
        GXSetDrawSync(2);
    }

    GXSetNumChans(mNumColorChans);

    for (s8 i = 0; i < 0; i++)
    {
        GXSetDrawSync(3);
    }

    mUnk007D = 0;
    mUnk007E = 0;
    
    mUnk0080 = 0;
    mUnk0084 = 0;
    mUnk0088 = 0;
    mUnk008C = 0;
    mUnk0090 = 0;
    mUnk0094 = 0;
    mUnk0098 = 0;
    mUnk009C = 0;

    GXSetZMode
    (
        GX_ENABLE,
        GX_EQUAL,
        GX_ENABLE
    );

    GXSetBlendMode
    (
        GX_BM_NONE,
        GX_BL_ZERO,
        GX_BL_ZERO,
        GX_LO_CLEAR
    );

    GXSetTevDirect(GX_MAX_TEVSTAGE);

    GXSetTexCoordGen2
    (
        GX_TEXCOORD0,
        GX_TG_MTX2x4,
        GX_TG_TEX0,
        GX_IDENTITY,
        GX_FALSE,
        GX_PTIDENTITY
    );
    
    GXSetTexCoordGen2
    (
        GX_TEXCOORD1,
        GX_TG_MTX2x4,
        GX_TG_TEX1,
        GX_IDENTITY,
        GX_FALSE,
        GX_PTIDENTITY
    );
   
    GXSetTexCoordGen2
    (
        GX_TEXCOORD2,
        GX_TG_MTX2x4,
        GX_TG_TEX2,
        GX_IDENTITY,
        GX_FALSE,
        GX_PTIDENTITY
    );
    
    GXSetTexCoordGen2
    (
        GX_TEXCOORD3,
        GX_TG_MTX2x4,
        GX_TG_TEX3,
        GX_IDENTITY,
        GX_FALSE,
        GX_PTIDENTITY
    );
    
    GXSetTexCoordGen2
    (
        GX_TEXCOORD4,
        GX_TG_MTX2x4,
        GX_TG_TEX4,
        GX_IDENTITY,
        GX_FALSE,
        GX_PTIDENTITY
    );
    
    GXSetTexCoordGen2
    (
        GX_TEXCOORD5,
        GX_TG_MTX2x4,
        GX_TG_TEX5,
        GX_IDENTITY,
        GX_FALSE,
        GX_PTIDENTITY
    );

    GXSetTexCoordGen2
    (
        GX_TEXCOORD6,
        GX_TG_MTX2x4,
        GX_TG_TEX6,
        GX_IDENTITY,
        GX_FALSE,
        GX_PTIDENTITY
    );

    GXSetTexCoordGen2
    (
        GX_TEXCOORD7,
        GX_TG_MTX2x4,
        GX_TG_TEX7,
        GX_IDENTITY,
        GX_FALSE,
        GX_PTIDENTITY
    );

    MTXIdentity(mMtx1);     // useless
    GXLoadTexMtxImm(mMtx1, GX_IDENTITY, GX_MTX2x4);
}