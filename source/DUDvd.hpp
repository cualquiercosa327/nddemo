#ifndef INCLUDE_DUDVD_HPP
#define INCLUDE_DUDVD_HPP

#include <dolphin.h>

#include "DUMacro.hpp"

enum enumDU_DVD_OPEN_MODE
{
	MODE_0,
	MODE_1,
	MODE_2,
	MODE_3
};

class DUDvd
{
private:
	DVDFileInfo *mFileInfo;
    u32 mLength;
    u32 mAlignedLength;
    int mOffset;
    char *mBuffer;
    enumDU_DVD_OPEN_MODE mMode;
	
public:
	DUDvd();
	~DUDvd();

	void Close();
	void Init();
	void InitDVD();
	bool Open(char *fileName, enumDU_DVD_OPEN_MODE mode);
	void Read(void *out, u32 len, int off);
	
	static bool m_InitDVD;
};

#endif