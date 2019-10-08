#ifndef INCLUDE_DGOBJ_HPP
#define INCLUDE_DGOBJ_HPP

#include <dolphin.h>

#include "DUMacro.hpp"
#include "DGTexMan.hpp"

#define VAT_POS 0
#define VAT_NORMAL 1
#define VAT_COLOR 2
#define VAT_TEXCOORD 3

static const GXTexMapID GXTEXMAP_TABLE[GX_MAX_TEXMAP] =
{
    GX_TEXMAP0,
    GX_TEXMAP1,
    GX_TEXMAP2,
    GX_TEXMAP3,
    GX_TEXMAP4,
    GX_TEXMAP5,
    GX_TEXMAP6,
    GX_TEXMAP7
};

static const u32 TevStageID_TABLE[GX_MAX_TEVSTAGE] =
{
    GX_TEVSTAGE0,
    GX_TEVSTAGE1,
    GX_TEVSTAGE2,
    GX_TEVSTAGE3,
    GX_TEVSTAGE4,
    GX_TEVSTAGE5,
    GX_TEVSTAGE6,
    GX_TEVSTAGE7,
    GX_TEVSTAGE8,
    GX_TEVSTAGE9,
    GX_TEVSTAGE10,
    GX_TEVSTAGE11,
    GX_TEVSTAGE12,
    GX_TEVSTAGE13,
    GX_TEVSTAGE14,
    GX_TEVSTAGE15
};

static const u32 TexCoordID_TABLE[GX_MAX_TEXCOORD + 1] =
{
    GX_TEXCOORD0,
    GX_TEXCOORD1,
    GX_TEXCOORD2,
    GX_TEXCOORD3,
    GX_TEXCOORD4,
    GX_TEXCOORD5,
    GX_TEXCOORD6,
    GX_TEXCOORD7,
    GX_TEXCOORD_NULL
};

static const GXAttr TexAttrBlock[8] =
{
    GX_VA_TEX0,            // input texture coordinate 0
    GX_VA_TEX1,            // input texture coordinate 1
    GX_VA_TEX2,            // input texture coordinate 2
    GX_VA_TEX3,            // input texture coordinate 3
    GX_VA_TEX4,            // input texture coordinate 4
    GX_VA_TEX5,            // input texture coordinate 5
    GX_VA_TEX6,            // input texture coordinate 6
    GX_VA_TEX7,            // input texture coordinate 7
};

class DGObject
{
    public:

    struct DGObjVAT
    {
        GXCompCnt mNumComp;
        GXCompType mCompType;
        u8 mFractional;
        u8 mStride;
    };

    struct NDMObjBlock
    {
        u16 handleArray[8];     // 0000 - 000F
        u32 unkLen;             // 0010
        u32 streamLen;          // 0014
        u32 dispLen;            // 0018
        u16 texWrapS;           // 001C
        u16 texWrapT;           // 001E
    };
    
    struct NDMBlock
    {
        u32 padding;        // 0000
        u32 imgLen;         // 0004
        u16 vCompType;      // 0008
        u16 nCompType;      // 000A
        u16 cCompType;      // 000C
        u16 tCompType;      // 000E
        u8 cmptField;       // 0010
        u32 normOff;        // 0014
        u32 colorOff;       // 0018
        u32 texCordOff;     // 001C
    };

    u16 mReferCount;        // 0000
    DGTexMan * mTex;        // 0004

    GXAttrType mPosAttr;     // 0008
    GXAttrType mNormAttr;    // 000C
    GXAttrType mColorAttr;   // 0010
    GXAttrType mTexAttr;     // 0014

    DGObjVAT mVATTable[4];  // 0018-0045

    /*
    GXCompCnt mPosNumComp;      // 0018
    GXCompType mPosCompType;    // 001C
    u8 mPosFractional;          // 0020
    u8 mPosStride;              // 0021
    
    GXCompCnt mNormNumComp;     // 0024
    GXCompType mNormCompType;   // 0028
    u8 mNormFractional;         // 002C
    u8 mNormStride;             // 002D

    GXCompCnt mColrNumComp;     // 0030
    GXCompType mColrCompType;   // 0034
    u8 mColrFractional;         // 0038
    u8 mColrStride;             // 0039

    GXCompCnt mTexNumComp;      // 003C
    GXCompType mTexCompType;    // 0040
    u8 mTexFractional;          // 0044
    u8 mTexStride;              // 0045
    */

    u8 * mArrayImg;             // 0048
    u32 mImgLen;                // 004C
    
    void * mNormArray;          // 0050
    void * mColorArray;         // 0054
    void * mTexCordArray;       // 0058
    void * mObjStream;          // 005C
    void * mDispList;           // 0060
    u16 mHandleArray[8];        // 0064
    u16 mTexWrapS;              // 0074
    u16 mTexWrapT;              // 0076
    void * mPartsBlock;         // 0078


    DGObject(DGTexMan * tex);
    ~DGObject();

    void Draw();
    void SetArrayFormat(u16 vCompType, u16 nCompType, u16 cCompType, u16 tCompType);
    void LoadNDMPartsBlock(DUDvd & dvd);
    void oscmdExtend0(u8 *& command);
    void oscmdVtxDesc(u8 *& command);
    void IncRefer();
    void DecRefer();
};

#endif