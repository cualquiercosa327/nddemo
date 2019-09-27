#ifndef INCLUDE_DGPOSITION_HPP
#define INCLUDE_DGPOSITION_HPP

#include <dolphin.h>

#include "DUMacro.hpp"

class DGPosition
{
public:
	Vec mPosition;
	Vec mRotation;
	Vec mTransMtx;
	Mtx mMtx;
	bool mIsProcessed;
	
	DGPosition();
	~DGPosition();
	
	void AddPosition(const Vec &position);
	void AddRotation(const Vec &rotation);
	void GetDirectionalVec(Vec &a, Vec &b);
	Vec GetPosition();
	Vec GetRotation();
	void GetTransMtx(Mtx &mtx);
	void LimitRotation();
	void SetPosition(const Vec &position);
	void SetRotation(const Vec &rotation);
};

#endif