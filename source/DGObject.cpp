#include "DGObject.hpp"

DGObject::DGObject(DGTexMan* tex)
{
	mReferCount = 0;
	mTex = tex;

	mPosAttr = GX_NONE;
	mNormAttr = GX_NONE;
	mColorAttr = GX_NONE;
	mTexAttr = GX_NONE;

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
	mObjStream = NULL;
	mDispList = NULL;

	mHandleArray[0] = 0;
	mHandleArray[1] = 0;
	mHandleArray[2] = 0;
	mHandleArray[3] = 0;
	mHandleArray[4] = 0;
	mHandleArray[5] = 0;
	mHandleArray[6] = 0;
	mHandleArray[7] = 0;

	mTexWrapS = 0;
	mTexWrapT = 0;

	mPartsBlock = NULL;
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

	if (mObjStream != NULL)
	{
		delete mObjStream;
		mObjStream = NULL;
	}

	if (mDispList != NULL)
	{
		delete mDispList;
		mDispList = NULL;
	}

	if (mPartsBlock != NULL)
	{
		delete mPartsBlock;
		mPartsBlock = NULL;
	}
}

void DGObject::Draw()
{
	if (mPosAttr != GX_NONE)
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

	if (mNormAttr != GX_NONE)
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

	if (mColorAttr != GX_NONE)
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

	if (mTexAttr != GX_NONE)
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

	for (u8 i = 0; i < GX_MAX_TEXMAP; ++i)
	{
		if (mHandleArray[i] == 0xFFFF) continue;

		GXTexWrapMode wrapS = GX_CLAMP;

		if (mTexWrapS & (1 << (i * 2)))
		{
			wrapS = GX_REPEAT;
		}
		else if (mTexWrapS & (2 << (i * 2))) {
			wrapS = GX_MIRROR;
		}

		GXTexWrapMode wrapT = GX_CLAMP;

		if (mTexWrapT & (1 << (i * 2)))
		{
			wrapT = GX_REPEAT;
		}
		else if (mTexWrapT & (2 << (i * 2))) {
			wrapT = GX_MIRROR;
		}

		GXTexObj texObj;
		mTex->InitTexObj(&texObj, mHandleArray[i], wrapS, wrapT);
		GXLoadTexObj(&texObj, GXTEXMAP_TABLE[i]);
	}
}

void DGObject::SetArrayFormat(u16 vCompType, u16 nCompType, u16 cCompType, u16 tCompType)
{
	if (mNormAttr != GX_NONE)
	{
		switch (vCompType & 0xE000)
		{
		case 0x0000: {
			mVATTable[VAT_POS].mCompType = GX_U8;
			break;
		}
		case 0x2000: {
			mVATTable[VAT_POS].mCompType = GX_U16;
			break;
		}
		case 0x8000: {
			mVATTable[VAT_POS].mCompType = GX_S8;
			break;
		}
		case 0xA000: {
			mVATTable[VAT_POS].mCompType = GX_S16;
			break;
		}
		case 0xE000: {
			mVATTable[VAT_POS].mCompType = GX_F32;
			break;
		}
		default: {
			OSReport("Error:SetArrayFormat(m_VCompType)\n");
			break;
		}
		}
		mVATTable[VAT_POS].mNumComp = ((vCompType & 0x1000) ? GX_POS_XYZ : GX_POS_XY);
		mVATTable[VAT_POS].mFractional = (vCompType >> 8) & 15;
		mVATTable[VAT_POS].mStride = (((vCompType >> 13) & 3) + 1)* (((vCompType >> 12) & 1) + 2);
	}
	if (mNormAttr != GX_NONE)
	{
		switch (nCompType & 0xE000)
		{
		case 0x8000: {
			mVATTable[VAT_NORMAL].mCompType = GX_S8;
			break;
		}
		case 0xA000: {
			mVATTable[VAT_NORMAL].mCompType = GX_S16;
			break;
		}
		case 0xE000: {
			mVATTable[VAT_NORMAL].mCompType = GX_F32;
			break;
		}
		default: {
			OSReport("Error:SetArrayFormat(m_NCompType)\n");
			break;
		}
		}
		mVATTable[VAT_NORMAL].mNumComp = ((nCompType & 0x1000) ? GX_NRM_NBT : GX_NRM_XYZ);
		mVATTable[VAT_NORMAL].mFractional = (nCompType >> 8) & 15;
		mVATTable[VAT_NORMAL].mStride = (((nCompType >> 13) & 3) + 1) * 3;
	}
	if (mColorAttr != GX_NONE)
	{
		switch (cCompType & 0xE000)
		{
		case 0x2000: {
			mVATTable[VAT_COLOR].mCompType = GX_RGB565;
			break;
		}
		case 0x4000: {
			mVATTable[VAT_COLOR].mCompType = GX_RGB8;
			break;
		}
		case 0x6000: {
			mVATTable[VAT_COLOR].mCompType = GX_RGBX8;
			break;
		}
		case 0xA000: {
			mVATTable[VAT_COLOR].mCompType = GX_RGBA4;
			break;
		}
		case 0xC000: {
			mVATTable[VAT_COLOR].mCompType = GX_RGBA6;
			break;
		}
		case 0xE000: {
			mVATTable[VAT_COLOR].mCompType = GX_RGBA8;
			break;
		}
		default: {
			OSReport("Error:SetArrayFormat(m_CCompType)\n");
			break;
		}
		}
		mVATTable[VAT_COLOR].mNumComp = ((cCompType & 0x1000) ? GX_CLR_RGBA : GX_CLR_RGB);
		mVATTable[VAT_COLOR].mFractional = ((cCompType >> 13) & 3) + 1;
	}

	if (mTexAttr != GX_NONE)
	{
		switch (tCompType & 0xE000)
		{
		case 0x0000: {
			mVATTable[VAT_TEXCOORD].mCompType = GX_U8;
			break;
		}
		case 0x2000: {
			mVATTable[VAT_TEXCOORD].mCompType = GX_U16;
			break;
		}
		case 0x8000: {
			mVATTable[VAT_TEXCOORD].mCompType = GX_S8;
			break;
		}
		case 0xA000: {
			mVATTable[VAT_TEXCOORD].mCompType = GX_S16;
			break;
		}
		case 0xE000: {
			mVATTable[VAT_TEXCOORD].mCompType = GX_F32;
			break;
		}
		default: {
			OSReport("Error:SetArrayFormat(m_TCompType)\n");
			break;
		}
		}
		mVATTable[VAT_TEXCOORD].mNumComp = ((tCompType & 0x1000) ? GX_TEX_ST : GX_TEX_S);
		mVATTable[VAT_TEXCOORD].mFractional = (vCompType >> 8) & 15;
		mVATTable[VAT_TEXCOORD].mStride = (((vCompType >> 13) & 3) + 1)* (((vCompType >> 12) & 1) + 1);
	}
}

void DGObject::LoadNDMPartsBlock(DUDvd& dvd)
{
	if (mPartsBlock != NULL)
	{
		OSReport("DGObject::LoadNDMPartsBlock >McrFree(m_PartsBlock);\n");
	}

	if (mPartsBlock != NULL)
	{
		delete mPartsBlock;
		mPartsBlock = NULL;
	}

	mPartsBlock = new u8[64];

	if (mPartsBlock == NULL)
	{
		OSReport("DGObject::LoadNDMPartsBlock >m_PartsBlock==NULL\n");
	}

	dvd.Read(mPartsBlock, 64, 0);

	NDMObjBlock* ndmObjectBlock = new NDMObjBlock;

	if (ndmObjectBlock == NULL)
	{
		OSReport("DGObject::LoadNDMPartsBlock >ndmObjectBlock==NULL\n");
	}

	dvd.Read(ndmObjectBlock, 32, 0);
	memcpy(mHandleArray, ndmObjectBlock, 16);

	mTexWrapS = ndmObjectBlock->texWrapS;
	mTexWrapT = ndmObjectBlock->texWrapT;

	NDMBlock* ndmArrayBlock = new NDMBlock;

	if (ndmArrayBlock == NULL)
	{
		OSReport("DGObject::LoadNDMPartsBlock >ndmArrayBlock==NULL\n");
	}

	dvd.Read(ndmArrayBlock, 32, 0);

	const GXAttrType attrArray[4] =
	{
	GX_NONE,
	GX_DIRECT,
	GX_INDEX8,
	GX_INDEX16
	};

	mPosAttr = attrArray[(ndmArrayBlock->cmptField >> 6) & 3];
	mNormAttr = attrArray[(ndmArrayBlock->cmptField >> 4) & 3];
	mColorAttr = attrArray[(ndmArrayBlock->cmptField >> 2) & 3];
	mTexAttr = attrArray[ndmArrayBlock->cmptField & 3];

	SetArrayFormat
	(
		ndmArrayBlock->vCompType,
		ndmArrayBlock->nCompType,
		ndmArrayBlock->cCompType,
		ndmArrayBlock->tCompType
	);

	if (mArrayImg != NULL)
	{
		delete mArrayImg;
		mArrayImg = NULL;
	}

	mImgLen = ndmArrayBlock->imgLen;
	if (mImgLen != 0)
	{
		mArrayImg = new u8[mImgLen];
		if (mArrayImg == NULL) OSReport("DGObject::LoadNDMPartsBlock >m_ArrayImg==NULL\n");

		dvd.Read(mArrayImg, mImgLen, 0);
		DCFlushRange(mArrayImg, mImgLen);

		mNormArray = &mArrayImg[ndmArrayBlock->normOff];
		mColorArray = &mArrayImg[ndmArrayBlock->colorOff];
		mTexCordArray = &mArrayImg[ndmArrayBlock->texCordOff];
	}

	if (mObjStream != NULL) OSReport("DGObject::LoadNDMPartsBlock >McrFree(m_ObjSteram);\n");
	if (mObjStream != NULL)
	{
		delete mObjStream;
		mObjStream = NULL;
	}

	if (ndmObjectBlock->streamLen != 0)
	{
		mObjStream = new u8[ndmObjectBlock->streamLen];
		if (mObjStream == NULL) OSReport("DGObject::LoadNDMPartsBlock >m_ObjSteram==NULL\n");

		dvd.Read(mObjStream, ndmObjectBlock->streamLen, 0);
	}

	if (mDispList != NULL) OSReport("DGObject::LoadNDMPartsBlock >McrFree(m_DispList);\n");
	if (mDispList != NULL)
	{
		delete mDispList;
		mDispList = NULL;
	}

	if (ndmObjectBlock->dispLen != 0)
	{
		mDispList = new u8[ndmObjectBlock->dispLen];
		if (mDispList == NULL) OSReport("DGObject::LoadNDMPartsBlock >m_DispList==NULL\n");

		dvd.Read(mDispList, ndmObjectBlock->dispLen, 0);
		DCFlushRange(mDispList, ndmObjectBlock->dispLen);
	}

	if (ndmObjectBlock != NULL) delete ndmObjectBlock;
	if (ndmArrayBlock != NULL) delete ndmArrayBlock;
}

void DGObject::oscmdExtend0(u8*& command)
{
	switch (*command & 0x0F)
	{
	case 0: {
		++command;
		break;
	}
	default: {
		OSReport("Error DGObject::oscmdExtend0>");
		++command;
		break;
	}
	}
}

void DGObject::oscmdVtxDesc(u8*& command)
{
	if ((*command & 0x01) == 0)
	{
		GXSetVtxDesc(GX_VA_POS, GX_NONE);
	}
	else
	{
		GXSetVtxDesc(GX_VA_POS, mPosAttr);
	}

	if ((*command & 0x02) == 0)
	{
		GXSetVtxDesc(GX_VA_NRM, GX_NONE);
	}
	else
	{
		GXSetVtxDesc(GX_VA_NRM, mNormAttr);
	}

	if ((*command & 0x04) == 0)
	{
		GXSetVtxDesc(GX_VA_CLR0, GX_NONE);
	}
	else
	{
		GXSetVtxDesc(GX_VA_CLR0, mColorAttr);
	}

	if ((*command & 0x08) == 0)
	{
		GXSetVtxDesc(GX_VA_CLR1, GX_NONE);
	}
	else
	{
		GXSetVtxDesc(GX_VA_CLR1, mColorAttr);
	}

	u8 texIndx;
	for (texIndx = 0; texIndx < command[1]; texIndx++)
	{
		GXSetVtxDesc(TexAttrBlock[texIndx], mTexAttr);
	}

	for (int i = texIndx; i < 8; i++)
	{
		GXSetVtxDesc(TexAttrBlock[i], GX_NONE);
	}

	command += 2;
}

void DGObject::IncRefer()
{
	for (u8 i = 0; i < 8; i++)
	{
		if (mHandleArray[i] == 0xFFFF) continue;
		mTex->AttachTexture(mHandleArray[i]);
	}
	++mReferCount;
}

u16 DGObject::DecRefer()
{
	if (!mReferCount)
	{
		OSReport("Error DGObject::DecRefer  ReferCount<0\n");
		return 0;
	}

	for (u8 i = 0; i < 8; i++)
	{
		if (mHandleArray[i] == 0xFFFF) continue;
		mTex->DetachTexture(mHandleArray[i]);
	}
	return --mReferCount;
}

// needs double checking
void DGObject::MakeTexTransTable(u16* trans)
{
	for (u8 i = 0; i < 8; i++)
	{
		if (mHandleArray[i] != 0xFFFF)
		{
			mHandleArray[i] = trans[1 << i];
		}
	}
}

void* DGObject::GetPartsBlock()
{
	return &mPartsBlock;
}

BOOL DGObject::IsNull()
{
	return (mPosAttr == GX_NONE) ? true : false;
}