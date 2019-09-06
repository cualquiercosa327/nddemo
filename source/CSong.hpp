#ifndef INCLUDE_CSONG_HPP
#define INCLUDE_CSONG_HPP

#include <dolphin.h>
#include <dolphin/musyx.h>

#include "DUMacro.hpp"

class CSong
{
private:
	int mSongId;
	int mSeqId;
	char *mBuffer;
	int mDelayMode;

public:
	CSong();

	void DelayDeleteBuffer();
	void DeleteBuffer();
	bool PlaySong(SND_GROUPID sgId);
	bool ReadBuffer(SND_SEQID seqId, char *fileName);
};

#endif