#ifndef INCLUDE_DTPAD_HPP
#define INCLUDE_DTPAD_HPP

#include <dolphin.h>

class DTPad
{
    public:

    int mMask;
    int mUnused;
    PADStatus mPreviousStatus[PAD_MAX_CONTROLLERS];
    PADStatus mCurrentStatus[PAD_MAX_CONTROLLERS];
    
    DTPad();
    ~DTPad();

    void Read();
    PADStatus * GetPadStatus(u8 num);
    s8 StickX(u16 num);
    s8 StickY(u16 num);
    bool IsTrg(u16 num, u16 button);
    bool IsPush(u16 num, u16 button);
};

#endif