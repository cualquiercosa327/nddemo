
// equivelant: OK
// exact: NO
int mAlloc(int size)
{
    OSThread * currThread;
    OSPriority threadPrior;
    void * heapPtr;

    currThread = (OSThread *)OSGetCurrentThread();
    threadPrior = OSGetThreadPriority(currThread);

    OSSetThreadPriority(currThread, 15);

    heapPtr = (void *)OSAllocFromHeap(NULL, size);

    if (heapPtr == NULL)
    {
        long heapSanity = OSCheckHeap(NULL);
        OSReport("Heap free %d blocksize %d\n", heapSanity, size);
        OSPanic("DUMacro.cpp", 45, "No memory\n");
    }
    OSSetThreadPriority(currThread, threadPrior);
    return (int)heapPtr;
}