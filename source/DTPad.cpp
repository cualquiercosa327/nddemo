
#include <dolphin.h>
#include "DUMacro.hpp"

#include "DTPad.hpp"

DTPad::DTPad()
{
    PADRead(mPreviousStatus);
    mMask = 0;
    mUnused = 0;
}

DTPad::~DTPad(){};

void DTPad::Read()
{
    mMask = 0;
    memcpy(mPreviousStatus, mCurrentStatus, sizeof(PADStatus) * PAD_MAX_CONTROLLERS);
    PADRead(mCurrentStatus);
    PADClamp(mCurrentStatus);

    // ...
}