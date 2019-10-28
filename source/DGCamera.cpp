#include "DGCamera.hpp"

DGCamera::DGCamera()
	: DGPosition()
{
	SetCameraFrustum(24.0f, 32.0f, 16.0f, 1024.0f);
	SetLightFrustrum(24.0f, 32.0f, 16.0f);

	Vec position = { 0.0f, 0.0f, 512.0f };
	SetPosition(position);

	Vec camUp = { 0.0f, 1.0f, 0.0f };
	SetCamUp(camUp);

	Vec targetPos = { 0.0f, 0.0f, 0.0f };
	SetTargetPos(targetPos);

	SetTargetMode(DGR_TARGET_POSITION);

	const GXColor black = { 0, 0, 0, 0 };
	SetFogColor(black);

	/* Useless resetting of mFogColor */
	mFogColor.r = 0;
	mFogColor.g = 0;
	mFogColor.b = 0;
	mFogColor.a = 0;

	mFogType = GX_FOG_NONE;

	SetFogRangeRatio(0.0, 0.1);
}

void DGCamera::GetLightMtx(Mtx& mtx)
{
	Vec camUp, targetPos;

	if (mMode == DGR_TARGET_UNK_1)
	{
		Mtx x, y;

		MTXRotDeg(x, 88, mRotation.x);
		MTXRotDeg(y, 89, mRotation.y);
		MTXConcat(y, x, x);
		MTXRotDeg(y, 90, mRotation.z);
		MTXConcat(y, x, x);

		Vec z = { 0.0f, 0.0f, -1.0f };

		MTXMultVecSR(x, &z, &z);
		VECAdd(&z, &mPosition, &targetPos);
		MTXMultVecSR(x, &mCamUp, &camUp);
		MTXLookAt(mtx, &mPosition, &camUp, &targetPos);
	}
	else
	{
		MTXLookAt(mtx, &mPosition, &mCamUp, &mTargetPos);
	}

	MTXConcat(mLightMtx, mtx, mtx);
}

void DGCamera::GetLightMtxYInverse(Mtx& mtx)
{
	Vec camUp, targetPos;

	if (mMode == DGR_TARGET_UNK_1)
	{
		Mtx x, y;

		MTXRotDeg(x, 88, mRotation.x);
		MTXRotDeg(y, 89, mRotation.y);
		MTXConcat(y, x, x);
		MTXRotDeg(y, 90, mRotation.z);
		MTXConcat(y, x, x);

		Vec z = { 0.0f, 0.0f, -1.0f };

		MTXMultVecSR(x, &z, &z);
		VECAdd(&z, &mPosition, &targetPos);
		MTXMultVecSR(x, &mCamUp, &camUp);
		MTXLookAt(mtx, &mPosition, &camUp, &targetPos);
	}
	else
	{
		MTXLookAt(mtx, &mPosition, &mCamUp, &mTargetPos);
	}

	MTXConcat(mLight2Mtx, mtx, mtx);
}

Vec DGCamera::GetTargetPos()
{
	return mTargetPos;
}

void DGCamera::GetViewMtx(Mtx& mtx)
{
	Vec camUp, targetPos;

	if (mMode == DGR_TARGET_UNK_1)
	{
		Mtx x, y;

		MTXRotDeg(x, 88, mRotation.x);
		MTXRotDeg(y, 89, mRotation.y);
		MTXConcat(y, x, x);
		MTXRotDeg(y, 90, mRotation.z);
		MTXConcat(y, x, x);

		Vec z = { 0.0f, 0.0f, -1.0f };

		MTXMultVecSR(x, &z, &z);
		VECAdd(&z, &mPosition, &targetPos);
		MTXMultVecSR(x, &mCamUp, &camUp);
		MTXLookAt(mtx, &mPosition, &camUp, &targetPos);
	}
	else
	{
		MTXLookAt(mtx, &mPosition, &mCamUp, &mTargetPos);
	}
}

void DGCamera::SetCamUp(Vec up)
{
	mCamUp = up;
}

void DGCamera::SetCamera(Mtx& mtx)
{
	SetProjectionMtx();
	GetViewMtx(mtx);
	GXSetFog(mFogType, mFogStartZ, mFogEndZ, mNearDistance, mFarDistance, mFogColor);
}

void DGCamera::SetCameraFrustum(float topEdge, float leftEdge, float nearDistance, float farDistance)
{
	mNearDistance = nearDistance;
	mFarDistance = farDistance;

	GXSetCopyClamp((GXFBClamp)(GX_CLAMP_TOP | GX_CLAMP_BOTTOM));

	float scale = 0.5f;

	MTXFrustum
	(
		mCamMtx,
		topEdge * scale,
		-topEdge * scale,
		-leftEdge * scale,
		leftEdge * scale,
		nearDistance,
		farDistance
	);
}

void DGCamera::SetCameraFrustumLower(float topEdge, float leftEdge, float nearDistance, float farDistance, float range)
{
	mNearDistance = nearDistance;
	mFarDistance = farDistance;

	float topScale = 2.0f / range;
	float leftScale = leftEdge * 0.5f;

	MTXFrustum
	(
		mCamMtx,
		topScale * topEdge,
		-topEdge + topScale * topEdge,
		-leftScale,
		leftScale,
		nearDistance,
		farDistance
	);
}

void DGCamera::SetCameraFrustumUpper(float topEdge, float leftEdge, float nearDistance, float farDistance)
{

	mNearDistance = nearDistance;
	mFarDistance = farDistance;

	float scale = 0.5f;

	MTXFrustum
	(
		mCamMtx,
		topEdge * scale,
		-topEdge * scale,
		-leftEdge * scale,
		leftEdge * scale,
		nearDistance,
		farDistance
	);
}

void DGCamera::SetFogColor(GXColor const& color)
{
	mFogColor = color;
}

void DGCamera::SetFogRange(float start, float end)
{
	mFogStartZ = start;
	mFogEndZ = end;
}

void DGCamera::SetFogRangeRatio(float start, float end)
{
	mFogStartZ = mNearDistance + (start * (mFarDistance - mNearDistance));
	mFogEndZ = mNearDistance + (end * (mFarDistance - mNearDistance));
}

void DGCamera::SetFogType(GXFogType type)
{
	mFogType = type;
}

void DGCamera::SetLightFrustrum(float height, float width, float nearZ)
{
	float scale = 0.5f;

	MTXLightFrustum
	(
		mLightMtx,
		(height * scale), (-height * scale),
		(-width * scale), (width * scale),
		nearZ, 0.5f, 0.5f, 0.5f, 0.5f
	);

	MTXLightFrustum
	(
		mLight2Mtx,
		(height * scale), (-height * scale),
		(-width * scale), (width * scale),
		nearZ, 0.5f, -0.5F, 0.5f, 0.5f
	);
}

void DGCamera::SetProjectionMtx()
{
	GXSetProjection(mCamMtx, GX_PERSPECTIVE);
}

void DGCamera::SetTargetMode(enumDG_RENDMAN_TARGET_MODE mode)
{
	mMode = mode;
}

void DGCamera::SetTargetPos(Vec position)
{
	mTargetPos = position;
}