
#include "DGTexMan.hpp"

DGTexMan::DGTexMan(u16 amount)
{
	mNumTextures = amount;
	mReferCount = 0;
	mUnk0004 = 0;       // unused?

	mNames = new char[mNumTextures * 16];
	memset(mNames, 0, (u16)(mNumTextures * 16));

	mTextures = new DGTexture * [mNumTextures];
	memset(mTextures, 0, (u16)(mNumTextures * 4));

	EnableMipMap(GX_TRUE);
	EnableExpensiveMipMap(GX_TRUE);
}

DGTexMan::~DGTexMan()
{
	for (int i = 0; i < mNumTextures; i++)
	{
		DeleteTexture(i);
	}
	// both mNames and mTextures are then freed
}

void DGTexMan::LoadTexture(char* texture)
{
	for (int i = 0; i < mNumTextures; i++)
	{

	}
}

u16 DGTexMan::AttachTexture(u16 handle)
{
	DGTexture* texture = GetTexture(handle);
	if (texture == NULL)
	{
		OSReport("Error DGTexMan::AttachTexture> Failed\n");
		return -1;
	}
	return texture->IncRefer();
}

// fix branch paths
void DGTexMan::DetachTexture(u16 handle)
{
	DGTexture* texture = GetTexture(handle);

	if (texture == NULL)
	{
		OSReport("Error DGTexMan::DetachTexture> Invalid Handle\n");
		return;
	}

	if (texture->DecRefer() == 0)
	{
		return;
	}

	DeleteTexture(handle);
}

u16 DGTexMan::GetWidth(u16 handle)
{
	DGTexture* texture = GetTexture(handle);
	return texture->GetWidth();
}

u16 DGTexMan::GetHeight(u16 handle)
{
	DGTexture* texture = GetTexture(handle);
	return texture->GetHeight();
}

GXBool DGTexMan::InitTexObj(GXTexObj* texObj, u16 handle, GXTexWrapMode wrapS, GXTexWrapMode wrapT)
{
	DGTexture* texture = GetTexture(handle);

	GXBool isMip = GX_FALSE;
	if (texture->GetMipLevel() != 0) isMip = mIsMipMap;

	GXInitTexObj(texObj, texture->GetImagePtr(), texture->GetWidth(),
		texture->GetHeight(), texture->GetFormat(), wrapS, wrapT, isMip);

	if (isMip == GX_TRUE)
	{
		if (mIsExpMipMap == GX_FALSE)
		{
			GXInitTexObjLOD(
				texObj,
				GX_LIN_MIP_LIN,
				GX_LINEAR,
				0.0F,
				(f32)texture->GetMipLevel(),
				-3.5F,
				GX_TRUE,
				GX_TRUE,
				GX_ANISO_4
			);
		}
		else
		{
			GXInitTexObjLOD(
				texObj,
				GX_LIN_MIP_LIN,
				GX_NEAR,
				0.0F,
				(f32)texture->GetMipLevel(),
				0.0F,
				GX_FALSE,
				GX_FALSE,
				GX_ANISO_1
			);
		}
	}
	return isMip;
}

inline DGTexture* DGTexMan::GetTexture(u16 handle)
{
	if (handle < mNumTextures)
		return mTextures[handle];
	OSReport("Error DGTexMan::GetTexture> Invalid Handle\n");

	return NULL;
}

inline void DGTexMan::DeleteTexture(u16 handle)
{
	if (handle < mNumTextures)
	{
		if (mNames[handle * 16] != 0)
		{
			memset((void*)mNames[handle * 16], 0, 16);

			if (mTextures[handle] != NULL)
			{
				delete mTextures[handle];
				mTextures[handle] = NULL;
			}
			--mReferCount;
		}
		else
		{
			OSReport("Error DGTexMan::DeleteTexture> Invalid Handle\n");
		}
	}
	else
	{
		OSReport("Error DGTexMan::DeleteTexture> Invalid Handle\n");
	}
}

void DGTexMan::EnableMipMap(GXBool flag)
{
	mIsMipMap = flag;
}

void DGTexMan::EnableExpensiveMipMap(GXBool flag)
{
	mIsExpMipMap = flag;
}