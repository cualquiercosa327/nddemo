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
};

#endif