#ifndef INCLUDE_DGCAMERA_HPP
#define INCLUDE_DGCAMERA_HPP

#include <dolphin.h>

#include "DUMacro.hpp"
#include "DGPosition.hpp"

class DGCamera
	: private DGPosition
{
public:
	enum enumDG_RENDMAN_TARGET_MODE
	{
		DGR_TARGET_POSITION,
		DGR_TARGET_UNK_1
	};

	Mtx44 mCamMtx;
	Mtx mLightMtx;
	Mtx mLight2Mtx;
	float mNearDistance;
	float mFarDistance;
	Vec mCamUp;
	Vec mTargetPos;
	enumDG_RENDMAN_TARGET_MODE mMode;
	GXColor mFogColor;
	GXFogType mFogType;
	float mFogStartZ;
	float mFogEndZ;

	DGCamera();
	~DGCamera();

	void GetLightMtx(Mtx &mtx);
	void GetLightMtxYInverse(Mtx &mtx);
	Vec  GetTargetPos();
	void GetViewMtx(Mtx &mtx);
	void SetCamUp(Vec up);
	void SetCamera(Mtx &mtx);
	void SetCameraFrustum(float topEdge, float leftEdge, float nearDistance, float farDistance);
	void SetCameraFrustumLower(float topEdge, float leftEdge, float nearDistance, float farDistance, float range);
	void SetCameraFrustumUpper(float topEdge, float leftEdge, float nearDistance, float farDistance);
	void SetFogColor(GXColor const &color);
	void SetFogRange(float start, float end);
	void SetFogRangeRatio(float start, float end);
	void SetFogType(GXFogType type);
	void SetLightFrustrum(float height, float width, float nearZ);
	void SetProjectionMtx();
	void SetTargetMode(enumDG_RENDMAN_TARGET_MODE mode);
	void SetTargetPos(Vec position);
};

#endif