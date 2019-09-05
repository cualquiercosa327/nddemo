#ifndef INCLUDE_DUMACRO_HPP
#define INCLUDE_DUMACRO_HPP

#include <dolphin.h>

#define ALIGN(size, alignment) \
	(((size) + ((alignment) - 1)) & ~((alignment) - 1))

void *mAlloc(u32 size);
void mFree(void *ptr);

inline void operator delete(void *block)
{
	mFree(block);
}

inline void *operator new(u32 size)
{
	return mAlloc(size);
}

inline void *operator new[](u32 size)
{
	return mAlloc(size);
}

#endif