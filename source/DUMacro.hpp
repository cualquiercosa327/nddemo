#include <dolphin.h>

#define ALIGN(size, alignment) \
	(((size) + ((alignment) - 1)) & ~((alignment) - 1))

void *mAlloc(u32 size);
void mFree(void *ptr);