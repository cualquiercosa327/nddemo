#include "DUMacro.hpp"

void* mAlloc(u32 size)
{
	OSThread* thread;
	OSPriority priority;
	void* ptr;

	thread = OSGetCurrentThread();
	priority = OSGetThreadPriority(thread);

	OSSetThreadPriority(thread, 15);
	ptr = OSAllocFromHeap(0, size);

	if (ptr == NULL)
	{
		OSReport("Heap free %d blocksize %d\n", OSCheckHeap(0), size);
		OSPanic("DUMacro.cpp", 45, "No memory\n");
	}

	OSSetThreadPriority(thread, priority);

	return ptr;
}

void mFree(void* ptr)
{
	OSThread* thread;
	OSPriority priority;

	thread = OSGetCurrentThread();
	priority = OSGetThreadPriority(thread);

	OSSetThreadPriority(thread, 15);
	OSFreeToHeap(0, ptr);
	OSSetThreadPriority(thread, priority);
}