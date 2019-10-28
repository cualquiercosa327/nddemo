#ifndef INCLUDE_DGTEXTURE_HPP
#define INCLUDE_DGTEXTURE_HPP

#include <dolphin.h>

#include "DUDvd.hpp"
#include "DUMacro.hpp"

struct DTX
{
	u8 version;
	u8 format;
	u8 width;
	u8 height;
	u32 length;
	u8 mipLevel;
	u8 padding[23];
};

class DGTexture
{
private:
	short mReferCount;
	void* mImagePtr;
	u16 mWidth;
	u16 mHeight;
	GXTexFmt mFormat;
	u8 mMipLevel;

public:
	DGTexture();
	~DGTexture();

	short DecRefer();
	short IncRefer();

	GXTexFmt GetFormat();
	u16 GetHeight();
	u16 GetWidth();
	u8 GetMipLevel();

	void* GetImagePtr();

	bool LoadDTX(char* fileName);
};

#endif