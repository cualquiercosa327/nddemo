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
	u8 * mImagePtr;
	u16 mWidth;
	u16 mHeight;
	GXTexFmt mFormat;
	u8 mMipLevel;

public:
	DGTexture();
	~DGTexture();
	
	int DecRefer();
	int IncRefer();
	
	GXTexFmt GetFormat();
	u16 GetHeight();
	u16 GetWidth();
	u8 GetMipLevel();
	
	void * GetImagePtr();
	
	bool LoadDTX(char *fileName);
};

#endif