#include "CSong.hpp"

CSong::CSong()
{
	mBuffer    = NULL;
	mSeqId     = SND_SEQ_ERROR_ID;
	mSongId	   = SND_ID_ERROR;
	mDelayMode = 0;
}

void CSong::DelayDeleteBuffer()
{	
	if (mDelayMode == 3 && mBuffer)
	{
		if (sndSeqGetValid(mSongId))
			mDelayMode = 3;
		else
		{
			mFree(mBuffer);
			mDelayMode = 0;
			mBuffer	= 0;
		}
	}
}

void CSong::DeleteBuffer()
{	
	if (mBuffer)
	{
		if (sndSeqGetValid(mSongId))
			mDelayMode = 3;
		else
		{
			mFree(mBuffer);
			mDelayMode = 0;
			mBuffer	= 0;
		}
	}
}

bool CSong::PlaySong(SND_GROUPID sgId)
{
	if (mBuffer == NULL)
		return false;
	
	if (mSongId >= 0)
	{
		mSeqId = sndSeqPlay(sgId, mSongId, mBuffer, NULL);
	
		if (mSeqId == SND_SEQ_ERROR_ID)
		{
			OSReport("Play song error %d\n", mSongId);		 
			return false;
		}
	
		sndSeqVolume(127, 0, mSeqId, SND_SEQVOL_CONTINUE);
	
		OSReport("Play song %d\n", mSongId);
	}
	
	return true;
}

bool CSong::ReadBuffer(SND_SEQID seqId, char *fileName)
{
	DVDFileInfo fileInfo;
	u32 length;
		
	if (mBuffer != NULL) 
		return true;

	if (!DVDOpen(fileName, &fileInfo))
	{
		OSReport("ERROR: Unable to opne '%s'\n", fileName);
		return false;
	}

	length  = ALIGN(fileInfo.length, 0x20);
	mBuffer = mAlloc(length);

	if (mBuffer == NULL)
	{
		OSReport("ERROR: Unable to allocate buffer\n");
		return false;
	}

	if (DVDRead(&fileInfo, mBuffer, length, 0) <= 0)
	{
		OSReport("ERROR: Read data failed '%s'\n", fileName);

		mFree(mBuffer);
		mBuffer = NULL;

		return false;
	}

	DVDClose(&fileInfo);

	mSongId	= seqId;
	mDelayMode = 1;

	return true;
}