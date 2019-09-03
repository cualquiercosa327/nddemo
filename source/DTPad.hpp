

#ifndef INCLUDE_DTPAD_HPP
#define INCLUDE_DTPAD_HPP

#include <dolphin.h>

class DTPad
{
    public:

    int mUnk00;
    int mUnk04;
    PADStatus mStatus;
    
    DTPad();
    ~DTPad();

    void Read();
};

#endif