#ifndef INCLUDE_DGOBJ_HPP
#define INCLUDE_DGOBJ_HPP

#include <dolphin.h>

#include "DUMacro.hpp"
#include "DGTexMan.hpp"

#define VAT_POS 0
#define VAT_NORMAL 1
#define VAT_COLOR 2
#define VAT_TEXCOORD 3

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

    u16 mReferCount;        // 0000
    DGTexMan * mTex;        // 0004

    BOOL mHasPos;           // 0008
    BOOL mHasNorm;          // 000C
    BOOL mHasColr;          // 0010
    BOOL mHasTex;           // 0014

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

    void * mArrayImg;             // 0048
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
    void SetArrayFormat(u16 fmt1, u16 fmt2, u16 fmt3, u16 fmt4);
};

#endif