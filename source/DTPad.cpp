
#include <dolphin.h>
#include "DTPad.hpp"
#include "DUMacro.hpp"

static u32 PadChanMask[PAD_MAX_CONTROLLERS] = {
    PAD_CHAN0_BIT,
    PAD_CHAN1_BIT,
    PAD_CHAN2_BIT,
    PAD_CHAN3_BIT
};

DTPad::DTPad()
{
    PADRead(mPreviousStatus);
    mMask = 0;
    mUnused = 0;
}

DTPad::~DTPad()
{
}

void DTPad::Read()
{
    mMask = 0;
    
    memcpy(mPreviousStatus, mCurrentStatus, sizeof(PADStatus) * PAD_MAX_CONTROLLERS);
    PADRead(mCurrentStatus);
    PADClamp(mCurrentStatus);

    for (int i = 0; i < PAD_MAX_CONTROLLERS; i++)
    {
        
        /* ...

        check each controller error status:
        PAD_ERROR_NONE, PAD_ERR_TRANSFER, and PAD_ERR_NO_CONTROLLER

        if an error is raised, the loop reiterates

        ... */

        mMask |= PadChanMask[i];
    }

    if (mMask == NULL) PADReset(mMask);
}

PADStatus * DTPad::GetPadStatus(u8 num)
{
    return &mCurrentStatus[num];
}

s8 DTPad::StickX(u16 num)
{
    return mCurrentStatus[num].stickX;
}

s8 DTPad::StickY(u16 num)
{
    return mCurrentStatus[num].stickY;
}

bool DTPad::IsTrg(u16 num, u16 button)
{
    if ((mCurrentStatus[num].button & button) != 0)
    {
        if ((mPreviousStatus[num].button & button) == 0)
        {
            return true;
        }
    }
    return false;
}

bool DTPad::IsPush(u16 num, u16 button)
{
    return (mCurrentStatus[num].button & button) == button;
}

