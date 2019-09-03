
#include <dolphin.h>
#include "DTPad.hpp"

DTPad::DTPad()
{
    PADRead(&mStatus);
    mUnk00 = 0;
    mUnk04 = 0;
}

DTPad::~DTPad(){};

void DTPad::Read(){};