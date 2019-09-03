#include <dolphin.h>
#include "DTPad.hpp"

void iMakeMainHeap();

void main()
{
    OSInit();
    
    iMakeMainHeap();

    DVDInit();
    VIInit();
    PADInit();

    while(TRUE)
    {
    }
}

void iMakeMainHeap()
{
    void * arenaLo;
    void * arenaHi;
    void * newArenaLo;
    void * newArenaHi;

    arenaLo = OSGetArenaLo();
    OSGetArenaHi();
    OSSetArenaLo((void *)OSRoundUp32B(arenaLo));

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

/*
void operator delete(void * block)
{
    mFree(block);
}
*/