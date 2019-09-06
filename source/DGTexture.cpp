#include "DGTexture.hpp"

DGTexture::DGTexture()
{
	this->mReferCount = 0;
	this->mImagePtr   = NULL;
	this->mWidth      = 0;
	this->mHeight     = 0;
	this->mFormat     = 5;
	this->mMipLevel   = 0;
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

int DGTexture::DecRefer()
{	
	if (mReferCount != 0)
		return --mReferCount;
	
	OSReport("Error DGTexture::DecRefer  ReferCount<0\n");
	return 0;	
}

int DGTexture::IncRefer()
{
	return ++mReferCount;
}

int DGTexture::GetFormat()
{
	return mFormat;
}

short DGTexture::GetHeight()
{
	return mHeight;
}

short DGTexture::GetWidth()
{
	return mWidth;
}

char DGTexture::GetMipLevel()
{
	return mMipLevel;
}

char *DGTexture::GetImagePtr()
{
	return mImagePtr;
}

bool DGTexture::LoadDTX(char *fileName)
{
	DTX *dtx;
	
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
	
	dtx = new DTX;
	
	dvd.Read(dtx, sizeof(DTX), 0);
	
	if (dtx->version != 0)
	{
		OSReport("DGTexture::LoadDTX>DTX_VERSION\n");
		
		dvd.Close();
		
		if (dtx)
			delete dtx;
		
		return false;
	}
	
	mFormat   = dtx->format;
	mWidth    = 1 << dtx->width;
	mHeight   = 1 << dtx->height;
	mMipLevel = dtx->mipLevel;
	
	mImagePtr = new char[dtx->length];
	
	dvd.Read(mImagePtr, dtx->length, 0);
	
	DCFlushRange(mImagePtr, dtx->length);
	
	dvd.Close();
	
	if (dtx)
		delete dtx;
	
	return true;
}