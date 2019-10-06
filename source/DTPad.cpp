#include "DTPad.hpp"

static u32 PadChanMask[PAD_MAX_CONTROLLERS] = {
    PAD_CHAN0_BIT,
    PAD_CHAN1_BIT,
    PAD_CHAN2_BIT,
    PAD_CHAN3_BIT
};

DTPad::DTPad()
{
    PADRead(mPreviousStatus);
	
    mMask   = 0;
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

    for (s8 i = 0; i < PAD_MAX_CONTROLLERS; i++)
    {
		s8 err = mCurrentStatus[i].err;
		
		if (err != PAD_ERR_NONE && 
			err != PAD_ERR_TRANSFER)
		{
			if (err == PAD_ERR_NO_CONTROLLER)
				mMask |= PadChanMask[i];
		}
    }

    if (mMask)
		PADReset(mMask);
}

PADStatus *DTPad::GetPadStatus(u8 num)
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
    if ((mCurrentStatus[num].button  & button) != 0 &&
		(mPreviousStatus[num].button & button) == 0)
    {
		return true;
    }
	else
	{
		return false;
	}
}

bool DTPad::IsPush(u16 num, u16 button)
{
    return (mCurrentStatus[num].button & button) == button;
}