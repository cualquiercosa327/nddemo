#include "DGPosition.hpp"

DGPosition::DGPosition()
{
	mPosition.x = 0;
	mPosition.y = 0;
	mPosition.z = 0;

	mRotation.x = 0;
	mRotation.y = 0;
	mRotation.z = 0;
	
	mTransMtx.x = 1.f;
	mTransMtx.y = 1.f;
	mTransMtx.z = 1.f;

	MTXIdentity(mMtx);
	
	mIsProcessed = false;
}

DGPosition::~DGPosition()
{
}

void DGPosition::AddPosition(const Vec &position)
{
	mIsProcessed = false;
	
	mPosition.x += position.x;
	mPosition.y += position.y;
	mPosition.z += position.z;
}

void DGPosition::AddRotation(const Vec &rotation)
{
	mIsProcessed = false;
		
	mRotation.x += rotation.x;
	mRotation.y += rotation.y;
	mRotation.z += rotation.z;
	
	LimitRotation();
}

void DGPosition::GetDirectionalVec(Vec &a, Vec &b)
{
	Mtx x, y;
	
	MTXRotDeg(x, 88, mRotation.x);
	MTXRotDeg(y, 89, mRotation.y);
	MTXConcat(y, x, x);
	MTXRotDeg(y, 90, mRotation.z);
	MTXConcat(y, x, x);
	MTXMultVecSR(x, &a, &b);
}

Vec DGPosition::GetPosition()
{
	return mPosition;
}

Vec DGPosition::GetRotation()
{
	return mRotation;
}

void DGPosition::GetTransMtx(Mtx &mtx)
{
	Mtx x, y;
	
	if (!mIsProcessed)
	{
		MTXRotDeg(x, 88, mRotation.x);
		MTXRotDeg(mMtx, 89, mRotation.y);
		MTXConcat(mMtx, x, y);
		MTXRotDeg(mMtx, 90, mRotation.z);
		MTXConcat(mMtx, y, x);
		MTXTrans(mMtx, mPosition.x, mPosition.y, mPosition.z);
		MTXConcat(mMtx, x, y);
		MTXScale(x, mTransMtx.x, mTransMtx.y, mTransMtx.z);
		MTXConcat(y, x, mMtx);
		
		mIsProcessed = true;
	}
	
	MTXCopy(mMtx, mtx);
}

void DGPosition::LimitRotation()
{
	while (mRotation.x >= 360.f)
		mRotation.x -= 360.f;
	
	while (mRotation.x <= -360.f)
		mRotation.x += 360.f;
	
	while (mRotation.y >= 360.f)
		mRotation.y -= 360.f;
	
	while (mRotation.y <= -360.f)
		mRotation.y += 360.f;
	
	while (mRotation.z >= 360.f)
		mRotation.z -= 360.f;
	
	while (mRotation.z <= -360.f)
		mRotation.z += 360.f;
}

void DGPosition::SetPosition(const Vec &position)
{	
	mIsProcessed = false;	
	mPosition    = position;
}

void DGPosition::SetRotation(const Vec &rotation)
{
	mIsProcessed = false;
	mRotation    = rotation;
	
	LimitRotation();
}