#include "DGTexPro.hpp"

DGTexPro::DGTexPro(DGTexMan* texMan)
{
	mTexMan = texMan;
	mTexHandle = 0xffff;
	mWrapS = GX_CLAMP;
	mWrapT = GX_CLAMP;
	mCamera = NULL;
	mImagePtr = NULL;
	mWidth = 0;
	mHeight = 0;
	mFormat = GX_TF_RGBA8;
	mMipLevel = 0;
}

DGTexPro::DGTexPro(DGTexMan* texMan, char* fileName)
{
	mTexMan = texMan;
	mTexHandle = mTexMan->LoadTexture(fileName);

	if (mTexHandle == 0xffff)
		OSReport("DGTexPro::DGTexPro>\n");

	mTexMan->AttachTexture(mTexHandle);

	mWrapS = GX_CLAMP;
	mWrapT = GX_CLAMP;
	mCamera = NULL;
	mImagePtr = NULL;
	mWidth = 0;
	mHeight = 0;
	mFormat = GX_TF_RGBA8;
	mMipLevel = 0;
}

DGTexPro::~DGTexPro()
{
	mTexMan->DetachTexture(mTexHandle);
}

void DGTexPro::GetLightMtx(Mtx& mtx)
{
	if (mCamera)
	{
		if (mImagePtr == NULL)
			mCamera->GetLightMtx(mtx);
		else
			mCamera->GetLightMtxYInverse(mtx);
	}
	else
	{
		MTXIdentity(mtx);
	}
}

GXBool DGTexPro::InitTexObj(GXTexObj* obj)
{
	if (mImagePtr)
	{
		GXBool mip = mMipLevel != 0;
		GXInitTexObj(obj, mImagePtr, mWidth, mHeight, mFormat, mWrapS, mWrapT, mip);
		return mip;
	}
	else
	{
		return mTexMan->InitTexObj(obj, mTexHandle, mWrapS, mWrapT);
	}
}

void DGTexPro::SetCamera(DGCamera* camera)
{
	mCamera = camera;
}

void DGTexPro::SetDirectTex(void* ptr, u16 width, u16 height, GXTexFmt format, u8 mipLevel)
{
	mImagePtr = ptr;
	mWidth = width;
	mHeight = height;
	mFormat = format;
	mMipLevel = mipLevel;
}