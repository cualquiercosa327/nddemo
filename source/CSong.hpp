#ifndef INCLUDE_CSONG_HPP
#define INCLUDE_CSONG_HPP

#include <dolphin.h>
#include <dolphin/musyx.h>

#include "DUMacro.hpp"

class CSong
{
public:
	int mSongId;
	int mSeqId;
	char *mBuffer;
	int mDelayMode;

	CSong();

	void DelayDeleteBuffer();
	void DeleteBuffer();
	int PlaySong(SND_GROUPID sgId);
	int ReadBuffer(SND_SEQID seqId, char *fileName);
};

#endif