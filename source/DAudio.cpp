#include <dolphin.h>
#include <dolphin/musyx.h>

#include "DAudio.hpp"
#include "DUMacro.hpp"

#define MAX_ARAM_BLOCKS 2

static SND_HOOKS hooks = { mAlloc, mFree };

DAudio::DAudio()
{

}

DAudio::~DAudio()
{   
}

void DAudio::Initialize()
{   
    AIInit(NULL);
    ARInit(NULL, MAX_ARAM_BLOCKS);
    ARQInit();

    sndSetHooks(&hooks);

    if (sndInit(48, 40, 8, SND_FLAGS_DEFAULT, 8*1024*1024) == 0) 
        OSReport("Audio Manager initialized success!!\n");
    else OSReport("Audio Manager initialized failed!!\n");

    sndVolume(127, 0, SND_ALL_VOLGROUPS);

    /*
    mUnk01F4 = 5.0f;

    sndAuxCallbackPrepareReverbHI(&mReverb);
    sndAuxCallbackPrepareChorus(&mChorus);
    sndSetAuxProcessingCallbacks
        (0, &sndAuxCallbackReverbHI, &mReverb, 255, 0, &sndAuxCallbackChorus, &mChorus, 255, 0);
    */
}