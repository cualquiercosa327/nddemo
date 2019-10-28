#ifndef INCLUDE_DGOBJMAN_HPP
#define INCLUDE_DGOBJMAN_HPP

#include <dolphin.h>

#include "DUMacro.hpp"
#include "DGObject.hpp"

class DGObjMan
{
private:
	u16 mNumObjectsAllocated;
	u16 mNumObjectsAdded;
	DGObject** mObjects;

public:
	DGObjMan(u16 amount);
	~DGObjMan();

	u16 AddObject(DGObject* obj);
	u16 AttachObject(u16 handle);
	void DetachObject(u16 handle);
	DGObject* GetObject(u16 handle);
};

#endif