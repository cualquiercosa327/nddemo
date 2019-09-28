#ifndef INCLUDE_DGRSTATE_HPP
#define INCLUDE_DGRSTATE_HPP

#include <dolphin.h>

class DGRendState
{
    public:

    Mtx mMtx1;
    Mtx mMtx2;
    int mUnk0060;
    int mUnk0064;
    int mUnk0068;

    GXColor mAmbColor;      // 006C
    GXColor mMatColor;      // 0070
    GXColor mAmb2Color;     // 0074
    GXColor mMat2Color;     // 0078

    u8 mNumColorChans;      // 007C
    
    u8 mUnk007D;
    u8 mUnk007E;
    u8 mUnk007F;

    int mUnk0080;
    int mUnk0084;
    int mUnk0088;
    int mUnk008C;
    int mUnk0090;
    int mUnk0094;
    int mUnk0098;
    int mUnk009C;

    DGRendState();
    ~DGRendState();
};

#endif