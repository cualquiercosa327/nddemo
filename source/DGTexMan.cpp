
#include "DGTexMan.hpp"

DGTexMan::DGTexMan(u16 amount)
{
    mNumTextures = amount;
    mReferCount = 0;
    mUnk0004 = 0;       // unused?
    
    mNames = (char **)mAlloc(mNumTextures * 16);
    memset(mNames, 0, (u16)(mNumTextures * 16));

    mTextures = new DGTexture * [mNumTextures];
    memset(mTextures, 0, (u16)(mNumTextures * 4));

    EnableMipMap(1);
    EnableExpensiveMipMap(1);
}

DGTexMan::~DGTexMan()
{
}

void DGTexMan::LoadTexture(char * texture)
{
    for (int i = 0; i < mNumTextures; i++)
    {
        
    }
}

void DGTexMan::EnableMipMap(u8 flag)
{
    mIsMipMap = flag;
}

void DGTexMan::EnableExpensiveMipMap(u8 flag)
{
    mIsExpMipMap = flag;
}