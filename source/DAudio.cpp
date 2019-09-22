#include <dolphin.h>
#include <dolphin/musyx.h>

#include "DAudio.hpp"
#include "DUMacro.hpp"

DAudio::DAudio()
{
	mPoolData = NULL;
	mProjData = NULL;
	mSdirData = NULL;
	mSampData = NULL;
	mSong     = NULL;
	
	mAutoDemo = 0;
	
	mIsSeqMuted = false;
	mIsSeMuted  = false;
	
	mVolume = 127;
}

DAudio::~DAudio()
{   
}

void DAudio::Coin()
{
	sndFXStart(SFXcoin_oneshot, SND_FX_DEFVOL, SND_FX_DEFPAN);
}

void DAudio::DoorKnock()
{
	sndFXStart(SFXknock_oneshot, SND_FX_DEFVOL, SND_FX_DEFPAN);
}

void DAudio::DoorOpen()
{
	sndFXStart(SFXdoor_oneshot, SND_FX_DEFVOL, SND_FX_DEFPAN);
}

void DAudio::Fall()
{
	SND_VOICEID vId;
	
	vId = sndFXStart(SFXjump_oneshot, SND_FX_DEFVOL, SND_FX_DEFPAN);
	
	sndFXDoppler(vId, 0x1000);
	sndFXPitchBend(vId, 0x1000);
}

void DAudio::FreeSampBuffer()
{
	delete mSampData;
}

void DAudio::Initialize()
{   
	AIInit(NULL);
	ARInit(mAramBlocks, NUM_ARAM_BLOCKS);
	ARQInit();

	sndSetHooks(&m_sndHooks);

	if (!sndInit(48, 40, 8, SND_FLAGS_DEFAULT, MAX_ARAM_SIZE)) 
		OSReport("Audio Manager initialized success!!\n");
	else
		OSReport("Audio Manager initialized failed!!\n");

	sndVolume(127, 0, SND_ALL_VOLGROUPS);

	mReverb.tempDisableFX = false;
	mReverb.time          = 5.0;
	mReverb.preDelay      = 0.1;
	mReverb.damping       = 0.6;
	mReverb.coloration    = 0.9;
	mReverb.crosstalk     = 0.0;
	mReverb.mix           = 0.5;
	
	mChorus.baseDelay = 15;
	mChorus.variation = 0;
	mChorus.period    = 500;
	
	sndAuxCallbackPrepareReverbHI(&mReverb);
	sndAuxCallbackPrepareChorus(&mChorus);
	
	sndSetAuxProcessingCallbacks(0, sndAuxCallbackReverbHI, &mReverb, 255, 0, sndAuxCallbackChorus, &mChorus, 255, 0);
}

void DAudio::Jump()
{
	sndFXStart(SFXjump_oneshot, SND_FX_DEFVOL, SND_FX_DEFPAN);	
}

/* I cannot get this one matching. */
void DAudio::MuteAll(int dipVolume)
{
	if (dipVolume == true)
		mVolume = 64;
	else
		mVolume = 127;

	sndMasterVolume(mVolume, 1000, !mIsSeqMuted, !mIsSeMuted);
}

int DAudio::PlaySong(CSong *song)
{
	if (song == mSong)
		return true;
	
	if (song->PlaySong(mSgId) != true)
		return false;
	
	mSong = song;
	
	return true;
}

int DAudio::PlaySongFadeOut()
{
	int seqId = mSong->mSeqId;
	
	if (mSong && seqId != SND_SEQ_ERROR_ID)
	{
		sndSeqVolume(0, 3000, seqId, SND_SEQVOL_STOP);
		OSReport("Stop song %d\n", seqId);
		mSong = NULL;
	}
	
	return true;
}

bool DAudio::PushGroupData(SND_GROUPID gId)
{
	return sndPushGroup(mProjData, gId, mSampData, mSdirData, mPoolData);
}

void DAudio::Quit()
{
	sndQuit();
}

char *DAudio::ReadDataAlloc(char *fileName)
{
	char *data;
	DVDFileInfo fileInfo;
	u32 length;
	
	if (!DVDOpen(fileName, &fileInfo))
	{
		OSReport("ERROR: Unable to opne '%s'\n", fileName);
		data = NULL;
		return data;
	}

	length = ALIGN(fileInfo.length, 0x20);
	data   = new char[length];

	if (data == NULL)
	{
		OSReport("ERROR: Unable to allocate buffer\n");
		return data;
	}

	if (DVDRead(&fileInfo, data, length, 0) <= 0)
	{
		OSReport("ERROR: Read data failed '%s'\n", fileName);

		delete data;
		data = NULL;

		return data;
	}

	DVDClose(&fileInfo);

	return data;
}

int DAudio::ReadPoolData(char *fileName)
{
	if (mPoolData != NULL)
	{
		delete mPoolData;
		mPoolData = NULL;
	}
	
	mPoolData = ReadDataAlloc(fileName);
	
	if (mPoolData == NULL)
		return false;
	
	return true;
}

int DAudio::ReadProjData(char *fileName)
{
	if (mProjData != NULL)
	{
		delete mProjData;
		mProjData = NULL;
	}
	
	mProjData = ReadDataAlloc(fileName);
	
	if (mProjData == NULL)
		return false;
	
	return true;
}

int DAudio::ReadSampData(char *fileName)
{
	if (mSampData != NULL)
	{
		delete mSampData;
		mSampData = NULL;
	}
	
	mSampData = ReadDataAlloc(fileName);
	
	if (mSampData == NULL)
		return false;
	
	return true;
}

int DAudio::ReadSdirData(char *fileName)
{
	if (mSdirData != NULL)
	{
		delete mSdirData;
		mSdirData = NULL;
	}
	
	mSdirData = ReadDataAlloc(fileName);
	
	if (mSdirData == NULL)
		return false;
	
	return true;
}

void DAudio::ResetFade()
{
	sndMasterVolume(0, 400, true, true);
}

/* Nintendo, what the fuck is this? */
void DAudio::SetAutoDemo(int demo)
{
	mAutoDemo = demo;
	
	if (mAutoDemo == true)
	{
		mIsSeMuted = true;
		
		if (mIsSeMuted == true)
			sndMasterVolume(0, 1000, false, true);
		else
			sndMasterVolume(mVolume, 1000, false, true);
	}
	else
	{
		mIsSeMuted = false;
		
		if (mIsSeMuted == true)
			sndMasterVolume(0, 1000, false, true);
		else
			sndMasterVolume(mVolume, 1000, false, true);
	}
}

void DAudio::SetMuteSe(int mute)
{
	mIsSeMuted = mute;
	
	if (mIsSeMuted == true)
		sndMasterVolume(0, 1000, false, true);
	else
		sndMasterVolume(mVolume, 1000, false, true);
}

void DAudio::SetMuteSequence(int mute)
{
	mIsSeqMuted = mute;
	
	if (mIsSeqMuted == true)
		sndMasterVolume(0, 1000, false, true);
	else
		sndMasterVolume(mVolume, 1000, false, true);
}

int DAudio::SongStop()
{
	int seqId = mSong->mSeqId;
	
	if (mSong && seqId != SND_SEQ_ERROR_ID)
	{
		sndSeqVolume(0, 3000, seqId, SND_SEQVOL_STOP);
		OSReport("Stop song %d\n", seqId);
		mSong = NULL;
	}
	
	return true;
}