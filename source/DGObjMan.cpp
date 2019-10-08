#include "DGObjMan.hpp"

DGObjMan::DGObjMan(u16 amount)
{	
	mNumObjectsAllocated = amount;
	mNumObjectsAdded = 0;
	mObjects = new DGObject *[mNumObjectsAllocated];
	memset(mObjects, 0, mNumObjectsAllocated * sizeof(DGObject *));
}

DGObjMan::~DGObjMan()
{
	if (mObjects != NULL)
	{
		for (int i = 0; i < mNumObjectsAllocated; i++)
		{
			if (mObjects[i] != NULL)
			{
				delete mObjects[i];
				mObjects[i] = NULL;
			}
		}
	}
	
	if (mObjects != NULL)
	{
		delete mObjects;
		mObjects = NULL;
	}
}

u16 DGObjMan::AddObject(DGObject *obj)
{	
	for (u16 handle = 0; ; handle++)
	{
		if (handle < mNumObjectsAllocated)
		{
			if (mObjects[handle])
				continue;
			else
			{
				mObjects[handle] = obj;
				mNumObjectsAdded++;
				return handle;
			}
		}
		else
		{
			OSReport("Error DGObjMan::AddObject Faluse\n");
			return 0xffff;
		}
	}
}


u16 DGObjMan::AttachObject(u16 handle)
{
	DGObject *object;
		
	if (handle < mNumObjectsAllocated)
		object = mObjects[handle];
	else
		object = NULL;
	
	if (object)
	{
		object->IncRefer();
		return handle;
	}
	else
	{
		OSReport("Error DGObjMan::AttachObject\n");
		return 0xffff;
	}
}


void DGObjMan::DetachObject(u16 handle)
{
	DGObject *object;

	if (handle < mNumObjectsAllocated)
		object = mObjects[handle];
	else
		object = NULL;
		
	if (object)
	{
		if (object->DecRefer() == 0 &&
			handle < mNumObjectsAllocated)
		{
			if (mObjects[handle])
			{
				if (mObjects[handle])
				{
					delete mObjects[handle];
					mObjects[handle] = NULL;
				}
				
				mNumObjectsAdded--;
			}
		}
	}
	else
	{
		OSReport("Error DGObjMan::DetachObject\n");
	}
}

DGObject *DGObjMan::GetObject(u16 handle)
{
	if (handle < mNumObjectsAllocated)
		return mObjects[handle];
	
	return NULL;
}
