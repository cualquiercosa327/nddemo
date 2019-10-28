#include "DGTexture.hpp"

DGTexture::DGTexture()
{
	this->mReferCount = 0;
	this->mImagePtr = NULL;
	this->mWidth = 0;
	this->mHeight = 0;
	this->mFormat = GX_TF_RGB5A3;
	this->mMipLevel = 0;
}

DGTexture::~DGTexture()
{
	if (mReferCount != 0)
		OSReport("Error DGTexture::~DGTexture  ReferCount>0\n");

	if (mImagePtr)
	{
		delete mImagePtr;
		mImagePtr = NULL;
	}
}

short DGTexture::DecRefer()
{
	if (mReferCount != 0)
	{
		return --mReferCount;
	}
	else
	{
		OSReport("Error DGTexture::DecRefer  ReferCount<0\n");
		return 0;
	}
}

short DGTexture::IncRefer()
{
	return ++mReferCount;
}

GXTexFmt DGTexture::GetFormat()
{
	return mFormat;
}

u16 DGTexture::GetHeight()
{
	return mHeight;
}

u16 DGTexture::GetWidth()
{
	return mWidth;
}

u8 DGTexture::GetMipLevel()
{
	return mMipLevel;
}

void* DGTexture::GetImagePtr()
{
	return mImagePtr;
}

bool DGTexture::LoadDTX(char* fileName)
{
	if (mImagePtr)
	{
		delete mImagePtr;
		mImagePtr = NULL;
	}

	DUDvd dvd;

	if (!dvd.Open(fileName, MODE_0))
	{
		OSReport("DGTexture::LoadDTX>dvd.Open\n");
		return false;
	}

	DTX* dtx = new DTX;

	dvd.Read(dtx, sizeof(DTX), 0);

	if (dtx->version != 0)
	{
		OSReport("DGTexture::LoadDTX>DTX_VERSION\n");

		dvd.Close();

		if (dtx)
			delete dtx;

		return false;
	}

	mFormat = (GXTexFmt)dtx->format;
	mWidth = 1 << dtx->width;
	mHeight = 1 << dtx->height;
	mMipLevel = dtx->mipLevel;
	mImagePtr = mAlloc(dtx->length);

	dvd.Read(mImagePtr, dtx->length, 0);
	DCFlushRange(mImagePtr, dtx->length);
	dvd.Close();

	if (dtx)
		delete dtx;

	return true;
}