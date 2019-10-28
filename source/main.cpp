#include <dolphin.h>
#include "DAudio.hpp"

static DAudio audio;

void iMakeMainHeap();

void main()
{
	OSInit();

	iMakeMainHeap();

	DVDInit();
	VIInit();
	PADInit();

	audio.Initialize();
	audio.ReadPoolData("audio/nddemo.pol");
	audio.ReadProjData("audio/nddemo.prj");
	audio.ReadSdirData("audio/nddemo.sdr");
	audio.ReadSampData("audio/nddemo.smp");

	OSReport("Read Audio data\n");

	audio.PushGroupData(GRPGM_Set);
	audio.PushGroupData(GRPSFXgroup);

	audio.FreeSampBuffer();

	/*
	CSong song;
	song.ReadBuffer(0, "audio/entrance.sng");
	audio.PlaySong(&song);
	*/

	while (TRUE)
	{
		VIWaitForRetrace();
	}
}

void iMakeMainHeap()
{
	void* arenaLo;
	void* arenaHi;
	void* newArenaLo;
	void* newArenaHi;

	arenaLo = OSGetArenaLo();
	OSGetArenaHi();
	OSSetArenaLo((void*)OSRoundUp32B(arenaLo));

	newArenaLo = OSGetArenaLo();
	newArenaHi = OSGetArenaHi();

	arenaLo = OSInitAlloc(newArenaLo, newArenaHi, 1);
	OSSetArenaLo(arenaLo);

	arenaLo = (void*)OSRoundUp32B(arenaLo);
	newArenaHi = (void*)OSRoundDown32B(newArenaHi);

	OSSetCurrentHeap(OSCreateHeap(arenaLo, newArenaHi));

	OSReport("iMakeMainHeap>start=%x / end=%x\n", arenaLo, newArenaHi);

	OSSetArenaLo(newArenaHi);

}