#ifndef INCLUDE_DGTEXMAN_HPP
#define INCLUDE_DGTEXMAN_HPP

#include <dolphin.h>

#include "DUMacro.hpp"
#include "DGTexture.hpp"

class DGTexMan
{
    public:

    u16 mNumTextures;
    u16 mReferCount;
    u16 mUnk0004;
    char ** mNames;
    DGTexture ** mTextures;
    u8 mIsMipMap;
    u8 mIsExpMipMap;

    
    DGTexMan(u16 unk);
    ~DGTexMan();

    void LoadTexture(char * texture);
    void EnableMipMap(u8 flag);
    void EnableExpensiveMipMap(u8 flag);
};

#endif