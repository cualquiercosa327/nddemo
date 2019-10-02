#include "DGObject.hpp"

static const u32 GXTEXMAP_TABLE[GX_MAX_TEXMAP] =
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

DGObject::DGObject(DGTexMan * tex)
{
    mReferCount = 0;
    mTex = tex;
    
    mHasPos = false;
    mHasNorm = false;
    mHasColr = false;
    mHasTex = false;

    mVATTable[VAT_POS].mNumComp = GX_POS_XYZ;
    mVATTable[VAT_POS].mCompType = GX_F32;
    mVATTable[VAT_POS].mFractional = 0;
    mVATTable[VAT_POS].mStride = 0;

    mVATTable[VAT_NORMAL].mNumComp = GX_NRM_XYZ;
    mVATTable[VAT_NORMAL].mCompType = GX_F32;
    mVATTable[VAT_NORMAL].mFractional = 0;
    mVATTable[VAT_NORMAL].mStride = 0;

    mVATTable[VAT_COLOR].mNumComp = GX_CLR_RGBA;
    mVATTable[VAT_COLOR].mCompType = GX_RGBA8;
    mVATTable[VAT_COLOR].mFractional = 0;
    //mVATTable[VAT_COLOR].mStride = 0;              uninitialized

    mVATTable[VAT_TEXCOORD].mNumComp = GX_TEX_ST;
    mVATTable[VAT_TEXCOORD].mCompType = GX_F32;
    mVATTable[VAT_TEXCOORD].mFractional = 0;
    mVATTable[VAT_TEXCOORD].mStride = 0;

    mArrayImg = NULL;
    mImgLen = 0;

    mNormArray = NULL;
    mColorArray = NULL;
    mTexCordArray = NULL;
}

DGObject::~DGObject()
{
    if (mReferCount != 0)
    {
        OSReport("Error DGObject::~DGObject ReferCount>0\n");
    }

    if (mArrayImg != NULL)
    {
        delete mArrayImg;
        mArrayImg = NULL;
    }
}

void DGObject::Draw()
{
    if (mHasPos)
    {
        GXSetVtxAttrFmt
        (
            GX_VTXFMT0,
            GX_VA_POS,
            mVATTable[VAT_POS].mNumComp,
            mVATTable[VAT_POS].mCompType,
            mVATTable[VAT_POS].mFractional
        );

        GXSetArray
        (
            GX_VA_POS,
            mArrayImg,
            mVATTable[VAT_POS].mStride
        );
    }
    
    if (mHasNorm)
    {
        GXSetVtxAttrFmt
        (
            GX_VTXFMT0,
            GX_VA_NRM,
            mVATTable[VAT_NORMAL].mNumComp,
            mVATTable[VAT_NORMAL].mCompType,
            mVATTable[VAT_NORMAL].mFractional
        );

        GXSetArray
        (
            GX_VA_NRM,
            mNormArray,
            mVATTable[VAT_NORMAL].mStride
        );
    }

    if (mHasColr)
    {
        GXSetVtxAttrFmt
        (
            GX_VTXFMT0,
            GX_VA_CLR0,
            mVATTable[VAT_COLOR].mNumComp,
            mVATTable[VAT_COLOR].mCompType,
            0
        );

        GXSetVtxAttrFmt
        (
            GX_VTXFMT0,
            GX_VA_CLR1,
            mVATTable[VAT_COLOR].mNumComp,
            mVATTable[VAT_COLOR].mCompType,
            0
        );

        /*  uses the color fractional for stride
            fractional should always be zero for color
            and assuming they don't use a stride for color,
            this should warrant no issue
        */
        GXSetArray
        (
            GX_VA_CLR0,
            mColorArray,
            mVATTable[VAT_COLOR].mFractional
        );

        GXSetArray
        (
            GX_VA_CLR1,
            mColorArray,
            mVATTable[VAT_COLOR].mFractional
        );
    }

    if (mHasTex)
    {
       GXSetVtxAttrFmt
        (
            GX_VTXFMT0,
            GX_VA_TEX0,
            mVATTable[VAT_TEXCOORD].mNumComp,
            mVATTable[VAT_TEXCOORD].mCompType,
            mVATTable[VAT_TEXCOORD].mFractional
        );

        GXSetVtxAttrFmt
        (
            GX_VTXFMT0,
            GX_VA_TEX1,
            mVATTable[VAT_TEXCOORD].mNumComp,
            mVATTable[VAT_TEXCOORD].mCompType,
            mVATTable[VAT_TEXCOORD].mFractional
        );

        GXSetVtxAttrFmt
        (
            GX_VTXFMT0,
            GX_VA_TEX2,
            mVATTable[VAT_TEXCOORD].mNumComp,
            mVATTable[VAT_TEXCOORD].mCompType,
            mVATTable[VAT_TEXCOORD].mFractional
        );

        GXSetVtxAttrFmt
        (
            GX_VTXFMT0,
            GX_VA_TEX3,
            mVATTable[VAT_TEXCOORD].mNumComp,
            mVATTable[VAT_TEXCOORD].mCompType,
            mVATTable[VAT_TEXCOORD].mFractional
        );

        GXSetVtxAttrFmt
        (
            GX_VTXFMT0,
            GX_VA_TEX4,
            mVATTable[VAT_TEXCOORD].mNumComp,
            mVATTable[VAT_TEXCOORD].mCompType,
            mVATTable[VAT_TEXCOORD].mFractional
        );

        GXSetVtxAttrFmt
        (
            GX_VTXFMT0,
            GX_VA_TEX5,
            mVATTable[VAT_TEXCOORD].mNumComp,
            mVATTable[VAT_TEXCOORD].mCompType,
            mVATTable[VAT_TEXCOORD].mFractional
        );

        GXSetVtxAttrFmt
        (
            GX_VTXFMT0,
            GX_VA_TEX6,
            mVATTable[VAT_TEXCOORD].mNumComp,
            mVATTable[VAT_TEXCOORD].mCompType,
            mVATTable[VAT_TEXCOORD].mFractional
        );

        GXSetVtxAttrFmt
        (
            GX_VTXFMT0,
            GX_VA_TEX7,
            mVATTable[VAT_TEXCOORD].mNumComp,
            mVATTable[VAT_TEXCOORD].mCompType,
            mVATTable[VAT_TEXCOORD].mFractional
        );

       GXSetArray
        (
            GX_VA_TEX0,
            mTexCordArray,
            mVATTable[VAT_TEXCOORD].mStride
        );

        GXSetArray
        (
            GX_VA_TEX1,
            mTexCordArray,
            mVATTable[VAT_TEXCOORD].mStride
        );
        
        GXSetArray
        (
            GX_VA_TEX2,
            mTexCordArray,
            mVATTable[VAT_TEXCOORD].mStride
        );
        
        GXSetArray
        (
            GX_VA_TEX3,
            mTexCordArray,
            mVATTable[VAT_TEXCOORD].mStride
        );

        GXSetArray
        (
            GX_VA_TEX4,
            mTexCordArray,
            mVATTable[VAT_TEXCOORD].mStride
        );

        GXSetArray
        (
            GX_VA_TEX5,
            mTexCordArray,
            mVATTable[VAT_TEXCOORD].mStride
        );

        GXSetArray
        (
            GX_VA_TEX6,
            mTexCordArray,
            mVATTable[VAT_TEXCOORD].mStride
        );

        GXSetArray
        (
            GX_VA_TEX7,
            mTexCordArray,
            mVATTable[VAT_TEXCOORD].mStride
        );
    }

    
}