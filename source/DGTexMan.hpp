#ifndef INCLUDE_DGTEXMAN_HPP
#define INCLUDE_DGTEXMAN_HPP

#pragma inline_depth(smart)

#include <dolphin.h>

#include "DUMacro.hpp"
#include "DGTexture.hpp"

class DGTexMan
{
    public:

    u16 mNumTextures;
    u16 mReferCount;
    u16 mUnk0004;
    char * mNames;
    DGTexture ** mTextures;
    GXBool mIsMipMap;
    GXBool mIsExpMipMap;

    
    DGTexMan(u16 unk);
    ~DGTexMan();

    void LoadTexture(char * texture);
    u16 AttachTexture(u16 handle);
    void DetachTexture(u16 handle);
    u16 GetWidth(u16 handle);
    u16 GetHeight(u16 handle);
    GXBool InitTexObj(GXTexObj * texObj, u16 handle, GXTexWrapMode wrapS, GXTexWrapMode wrapT);
    inline DGTexture * GetTexture(u16 handle);
    inline void DeleteTexture(u16 handle);
    void EnableMipMap(GXBool flag);
    void EnableExpensiveMipMap(GXBool flag);
};

#endif