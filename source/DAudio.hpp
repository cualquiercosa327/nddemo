#ifndef INCLUDE_DAUDO_HPP
#define INCLUDE_DAUDO_HPP

#include <dolphin.h>

#include "CSong.hpp"
#include "DUMacro.hpp"
#include "nddemo.h"

#define NUM_ARAM_BLOCKS 2
#define MAX_ARAM_SIZE (8*1024*1024) // 8MB

static SND_HOOKS m_sndHooks = { mAlloc, mFree };

class DAudio
{
private:
    u32 mAramBlocks[NUM_ARAM_BLOCKS];
    char *mPoolData;
    char *mProjData;
    char *mSampData;
    char *mSdirData;
    CSong *mSong;
    u16 mSgId;
    u8 mIsSeqMuted;
    u8 mIsSeMuted;
    u8 mVolume;
    SND_AUX_REVERBHI mReverb;
    SND_AUX_CHORUS mChorus;
    long mAutoDemo;
	
public:
	DAudio();
	~DAudio();

	void Coin();
	void DoorKnock();
	void DoorOpen();
	void Fall();
	void FreeSampBuffer();
	void Initialize();
	void Jump();
	void MuteAll(int dipVolume);
	int PlaySong(CSong *song);
	int PlaySongFadeOut();
	bool PushGroupData(SND_GROUPID gId);
	void Quit();
	char *ReadDataAlloc(char *fileName);
	int ReadPoolData(char *fileName);
	int ReadProjData(char *fileName);
	int ReadSampData(char *fileName);
	int ReadSdirData(char *fileName);
	void ResetFade();
	void SetAutoDemo(int demo);
	void SetMuteSe(int mute);
	void SetMuteSequence(int mute);
	int SongStop();
};

#endif