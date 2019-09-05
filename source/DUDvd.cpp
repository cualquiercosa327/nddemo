#include "DUDvd.hpp"

bool DUDvd::m_InitDVD = false;

DUDvd::DUDvd()
{
	Init();
}

DUDvd::~DUDvd()
{	
	Close();
}

void DUDvd::Close()
{
	if (mFileInfo)
	{
		DVDClose(mFileInfo);
		
		if (mFileInfo)
		{
			delete mFileInfo;
			mFileInfo = NULL;
		}
	}
	
	if (mBuffer)
	{
		delete mBuffer;
		mBuffer = NULL;
	}
	
	mLength        = 0;
	mAlignedLength = 0;
	mOffset        = 0;
	mMode          = MODE_0;
}

void DUDvd::Init()
{
	mFileInfo      = NULL;
	mBuffer        = NULL;
	mLength        = 0;
	mAlignedLength = 0;
	mOffset        = 0;
	mMode          = MODE_0;
	
	InitDVD();
}

void DUDvd::InitDVD()
{
	if (!m_InitDVD)
	{
		DVDInit();
		m_InitDVD = true;
	}
}

bool DUDvd::Open(char *fileName, enumDU_DVD_OPEN_MODE mode)
{	
	if (mFileInfo)
	{
		DVDClose(mFileInfo);
		
		if (mFileInfo)
		{
			delete mFileInfo;
			mFileInfo = NULL;
		}
	}
	
	if (mBuffer)
	{
		delete mBuffer;
		mBuffer = NULL;
	}
	
	mLength        = 0;
	mAlignedLength = 0;
	mOffset        = 0;
	mMode          = MODE_0;
	
	mMode     = mode;
	mFileInfo = new DVDFileInfo;
		
	if (DVDOpen(fileName, mFileInfo) == 1)
	{
		mLength = mFileInfo->length;
	
		if (mMode == MODE_2 || mMode == MODE_3)
		{
			mAlignedLength = mLength & ~0x20;
				
			if (mAlignedLength < mLength)
				mAlignedLength += 0x20;
				
			mBuffer = new char[mAlignedLength];
			
			DVDRead(mFileInfo, mBuffer, mLength, 0);
		}
		
		return true;
	}

	if (mFileInfo)
	{
		delete mFileInfo;
		mFileInfo = NULL;
	}
	
	OSReport("DVD Open False\n");
	
	return false;
}

void DUDvd::Read(void *out, u32 len, int off)
{
	int priority;
	
	if (mMode == MODE_2 || mMode == MODE_3)
		memcpy(out, mBuffer + mOffset + off, len);
	else
	{
		priority = DVDRead(mFileInfo, out, len, mOffset + off);
		
		if (priority != len)
		{
			OSReport("Error DUDvd::Read>len=%d,off=%d,ret=%d\n", len, off, priority);
			OSReport("Error DUDvd::Read>fptr=%d\n", mOffset);
		}
	}
	
	if (mMode == MODE_0 || mMode == MODE_2)
		mOffset += off + len;
}
