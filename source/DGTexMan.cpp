
#include "DGTexMan.hpp"

DGTexMan::DGTexMan(u16 amount)
{
    mMaxNumTextures = amount;
    mNumTextures = 0;
    mUnk0004 = 0;       // unused?
    
    mNames = new char[mMaxNumTextures * 16];
    memset(mNames, 0, (u16)(mMaxNumTextures * 16));

    mTextures = new DGTexture * [mMaxNumTextures];
    memset(mTextures, 0, (u16)(mMaxNumTextures * 4));

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
    delete mTextures;
    mTextures = NULL;

    delete mNames;
    mNames = NULL;
}

u16 DGTexMan::LoadTexture(
  char const * name
) {

  DGTexture * texture;
  u16 textures = 0; // r27
  u16 i; // r28

  for (i = 0;; ++i) {
    if (i >= mMaxNumTextures || textures >= mNumTextures) {
      i = (u16)-1;
      break;
    }

    if (mNames[i * 16] != '\0') {
      ++textures;

      if (strncmp(name, (&mNames[i * 16]), 16) == 0) {
        break;
      }
    }
  }

  if (i == (u16)-1) {
    
    char directory[20];

    strcpy(directory, "tex/");
    memcpy(&directory[4], name, 16);
  
    directory[20] = 0;
  
    strcpy(&directory[strlen(directory)], ".dtx");
  
    // this is inlined
    texture = new DGTexture();
    if (texture->LoadDTX(directory) == TRUE)
    {
        for (textures = 0; ; ++textures) {
            if (textures > mMaxNumTextures) {
                OSReport("Error DGTexMan::AddTexture> Full\n");
                textures = (u16)-1;
                break;
            }
            if (mNames[textures * 16] == '\0') {
                memcpy(&mNames[textures * 16], name, 16);
                mTextures[textures] = texture;
                ++mNumTextures;
                break;
            }
        }
        return textures;
    } else {
      OSReport("Error DGTexMan::LoadTexture> Load Failed\n");
      if (texture != NULL) delete texture;
      return (u16)-1;
    }
  } else {
      OSReport("Already Exist Texture [%s]\n", name);
    return i;
  }
}

u16 DGTexMan::AttachTexture(u16 handle)
{
    DGTexture * texture = GetTexture(handle);
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
    DGTexture * texture = GetTexture(handle);
    
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
    DGTexture * texture = GetTexture(handle);
    return texture->GetWidth();
}

u16 DGTexMan::GetHeight(u16 handle)
{
    DGTexture * texture = GetTexture(handle);
    return texture->GetHeight();
}

GXBool DGTexMan::InitTexObj(GXTexObj * texObj, u16 handle, GXTexWrapMode wrapS, GXTexWrapMode wrapT)
{
    DGTexture * texture = GetTexture(handle);

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

inline DGTexture * DGTexMan::GetTexture(u16 handle)
{
    if (handle < mMaxNumTextures)
        return mTextures[handle];
    OSReport("Error DGTexMan::GetTexture> Invalid Handle\n");
    
    return NULL;
}

inline void DGTexMan::DeleteTexture(u16 handle)
{
    if (handle < mMaxNumTextures)
    {
        if (mNames[handle * 16] != 0)
        {
            memset((void *)mNames[handle * 16], 0, 16);
            
            if (mTextures[handle] != NULL)
            {
                delete mTextures[handle];
                mTextures[handle] = NULL;
            }
            --mNumTextures;
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