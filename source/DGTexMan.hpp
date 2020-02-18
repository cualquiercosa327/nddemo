#ifndef INCLUDE_DGTEXMAN_HPP
#define INCLUDE_DGTEXMAN_HPP

#pragma inline_depth(smart)

#include <dolphin.h>

#include "DUMacro.hpp"
#include "DGTexture.hpp"

class DGTexMan
{
    public:

    u16 mMaxNumTextures;    // 0000
    u16 mNumTextures;       // 0002
    u16 mUnk0004;           // 0004
    char * mNames;          // 0008
    DGTexture ** mTextures; // 000C
    GXBool mIsMipMap;       // 0010
    GXBool mIsExpMipMap;    // 0011

    
    DGTexMan(u16 unk);
    ~DGTexMan();

    u16 LoadTexture(char const * name);
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