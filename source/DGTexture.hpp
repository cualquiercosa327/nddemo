#ifndef INCLUDE_DGTEXTURE_HPP
#define INCLUDE_DGTEXTURE_HPP

#include <dolphin.h>

#include "DUDvd.hpp"
#include "DUMacro.hpp"

struct DTX
{
    char version;
    char format;
    char width;
    char height;
    int  length;
    char mipLevel;
    char padding[23];
};

class DGTexture
{
private:
	short mReferCount;
	char *mImagePtr;
	short mWidth;
	short mHeight;
	int mFormat;
	char mMipLevel;

public:
	DGTexture();
	~DGTexture();
	
	int DecRefer();
	int IncRefer();
	
	int GetFormat();
	short GetHeight();
	short GetWidth();
	char GetMipLevel();
	
	char *GetImagePtr();
	
	bool LoadDTX(char *fileName);
};

#endif